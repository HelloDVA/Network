#include <cerrno>
#include <cstddef>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include <iostream>

#include "tcpconnection.h"
#include "sockets.h"

TcpConnection::TcpConnection(EventLoop* loop,
                             const std::string& name,
                             int sockfd,
                             const InetAddress& local_addr,
                             const InetAddress& peer_addr)
    : loop_(loop),
      name_(name),
      state_(kConnecting),
      channel_(std::make_unique<Channel>(loop, sockfd)),
      local_addr_(local_addr),
      peer_addr_(peer_addr) {
    
    // 注册各种事件回调
    channel_->setreadcallback([this]() { this->HandleRead(); });
    channel_->setwritecallback([this]() { this->HandleWrite(); });
    channel_->setclosecallback([this]() { this->HandleClose(); });
    channel_->seterrorcallback([this]() { this->HandleError(); });
}

TcpConnection::~TcpConnection() {
    std::cout << "TcpConnection::~TcpConnection [" << name_ << "] at fd=" 
              << channel_->getfd() << std::endl;
}

void TcpConnection::ConnectEstablished() {
    loop_->AssertInLoopThread();
    assert(state_ == kConnecting);
    setstate(kConnected);
    channel_->EnableReading();  // 开始监听可读事件
    std::cout << "connection 44 connection started" << std::endl;
}

void TcpConnection::ConnectDestroyed() {
    loop_->AssertInLoopThread();
    if (state_ == kConnected) {
        setstate(kDisconnected);
        channel_->DisableAll();
    }
    channel_->RemoveChannel();
}

void TcpConnection::HandleRead() {
    loop_->AssertInLoopThread();
    std::cout << "message in" << std::endl;
    int savedErrno = 0;
    ssize_t n = input_buffer_.ReadFd(channel_->getfd(), &savedErrno);
    std::cout << n << std::endl;
    
    if (n > 0) {
        if (read_callback_)
            read_callback_(shared_from_this(), &input_buffer_);

        // 有数据可读，调用消息回调
        std::cout << "message in" << std::endl;

    } else if (n == 0) {
        // 客户端关闭连接
        HandleClose();
    } else {
        // 读取错误
        errno = savedErrno;
        std::cerr << "TcpConnection::HandleRead error" << std::endl;
        HandleError();
    }
}

void TcpConnection::HandleWrite() {
    loop_->AssertInLoopThread();
    
    // test whether the channel can do write
    if (channel_->IsWriting()) {
        ssize_t n = sockets::Write(channel_->getfd(), 
                                  output_buffer_.Peek(), 
                                  output_buffer_.ReadableBytes());
        if (n > 0) {
            output_buffer_.Retrieve(n);
            if (output_buffer_.ReadableBytes() == 0) {
                channel_->DisableWriting();
                if (state_ == kDisconnecting) {
                    ShutdownInLoop();
                }
            }
        } else {
            std::cerr << "TcpConnection::HandleWrite error" << std::endl;
        }
    }
}

void TcpConnection::HandleClose() {
    loop_->AssertInLoopThread();
    std::cout << "TcpConnection::HandleClose state = " << state_ << std::endl;
    assert(state_ == kConnected || state_ == kDisconnecting);

    setstate(kDisconnected);
    channel_->DisableAll();
    
    // protect the connection close safely
    TcpConnectionPtr guardThis(shared_from_this());
    if (close_callback_) {
        close_callback_(guardThis);
    }
}

void TcpConnection::HandleError() {
    int err = sockets::GetError(channel_->getfd());
    std::cerr << "TcpConnection::HandleError [" << name_ 
              << "] - SO_ERROR = " << err << std::endl;
}

void TcpConnection::Send(const std::string& message) {
    if (state_ == kConnected) {
        if (loop_->IsInLoopThread()) 
            SendInLoop(message);
        else 
            loop_->RunInLoop([this, msg = message]() {
                    SendInLoop(msg);
            });
    }
}

void TcpConnection::SendInLoop(const std::string& message) {
   ssize_t nwrote = 0;
   size_t remaining = message.size();
    
   // buffer is full and the channel is not write
   // use write to send message
   if (!channel_->IsWriting() && output_buffer_.ReadableBytes() == 0) {
        nwrote = ::write(channel_->getfd(), message.data(), message.size());
        if (nwrote > 0)
            remaining -= nwrote;
        else if (errno != EWOULDBLOCK) {
            return;
        }
   }
    
   // append data to buffer
   if (remaining > 0) {
        output_buffer_.Append(message.data() + nwrote, remaining);
        if (!channel_->IsWriting())
            channel_->EnableWriting();
   }
}

void TcpConnection::Shutdown() {
    if (state_ == kConnected) {
        setstate(kDisconnecting);
        loop_->RunInLoop([this]() {
                ShutdownInLoop();
        });
    }
}

void TcpConnection::ShutdownInLoop() {
    loop_->AssertInLoopThread();
    if (!channel_->IsWriting()) {
       ::shutdown(channel_->getfd(), SHUT_WR); 
    }
}
