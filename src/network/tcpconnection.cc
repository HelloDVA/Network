

#include "tcpconnection.h"
#include "sockets.h"
#include <errno.h>
#include <unistd.h>
#include <iostream>

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
}

void TcpConnection::ConnectDestroyed() {
    loop_->AssertInLoopThread();
    if (state_ == kConnected) {
        setstate(kDisconnected);
        channel_->DisableAll();
    }
    channel_->Remove();
}


void TcpConnection::HandleRead() {
    loop_->AssertInLoopThread();
    int savedErrno = 0;
    ssize_t n = input_buffer_.ReadFd(channel_->getfd(), &savedErrno);
    
    if (n > 0) {
        // 有数据可读，调用消息回调
        if (message_callback_) {
            message_callback_(shared_from_this(), &input_buffer_);
        }
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

    TcpConnectionPtr guardThis(shared_from_this());
    if (close_callback_) {
        close_callback_(guardThis);
    }
}

void TcpConnection::HandleError() {
    int err = sockets::GetSocketError(channel_->getfd());
    std::cerr << "TcpConnection::HandleError [" << name_ 
              << "] - SO_ERROR = " << err << std::endl;
}