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
}

TcpConnection::~TcpConnection() {
    int sockfd = channel_->getfd();
    std::cout << "TcpConnection::~TcpConnection [" << name_ << "] at fd=" 
              << sockfd << std::endl;
    sockets::Close(sockfd);
}

void TcpConnection::ConnectEstablished() {
    loop_->AssertInLoopThread();
    assert(state_ == kConnecting);
    setstate(kConnected);
    channel_->EnableReading();  
    channel_->EnableET();
}

void TcpConnection::ConnectDestroyed() {
    loop_->AssertInLoopThread();
    if (state_ == kConnected) {
        setstate(kDisconnected);
    }
    channel_->RemoveChannel();
}

void TcpConnection::HandleRead() {
    loop_->AssertInLoopThread();
    
    // Use buffer to make sure the http request is completed.
    int saved_errno;

    while (true) {
        std::cout << "+++++++++++++++++++++++++++++++++" << std::endl;
        ssize_t n = input_buffer_.ReadFd(channel_->getfd(), &saved_errno);
        std::cout << "read bytes " << n << std::endl;
        if (n > 0) {
            std::cout << "read_callback_ message " << std::endl;
            if (read_callback_) {
                read_callback_(shared_from_this(), &input_buffer_);
            }
        } else if (n == 0) {
            std::cout << "close handle" << std::endl;
            HandleClose();
            break;
        } else if (saved_errno == EAGAIN || saved_errno == EWOULDBLOCK) {
            break;
        } else {
            std::cerr << "TcpConnection::HandleRead error" << std::endl;
            HandleError(saved_errno);
            break;
        }
    }

    /* ssize_t n = input_buffer_.ReadFd(channel_->getfd(), &saved_errno); */
    /* std::cout << "tcpconnection 58 read bytes:  " << n <<std::endl; */
    /* if (n > 0) { */
    /*     if (read_callback_) { */
    /*         read_callback_(shared_from_this(), &input_buffer_); */
    /*     } */
    /* } else if (n == 0) { */
    /*     // Client close the connection. */
    /*     HandleClose(); */
    /* } else if (saved_errno == EAGAIN || saved_errno == EWOULDBLOCK) { */
    /* } else { */
    /*     std::cerr << "TcpConnection::HandleRead error" << std::endl; */
    /*     HandleError(saved_errno); */
    /* } */
}

void TcpConnection::HandleWrite() {
    loop_->AssertInLoopThread();

    if (channel_->IsWriting()) {
        ssize_t n = sockets::Write(channel_->getfd(), 
                                  output_buffer_.Peek(), 
                                  output_buffer_.ReadableBytes());
        if (n > 0) {
            output_buffer_.Retrieve(n);
            
            // All data has been send, close write.
            if (output_buffer_.ReadableBytes() == 0) {
                channel_->DisableWriting();
                
                // If the client has closed the connection, close after the send.
                if (state_ == kDisconnecting) 
                    ShutdownInLoop();
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
    channel_->DisableAll();
    setstate(kDisconnected);

    // Protect the connection close safely.
    TcpConnectionPtr guardThis(shared_from_this());
    if (close_callback_) {
        close_callback_(guardThis);
    }
}

void TcpConnection::HandleError(int err) {
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
    // Make sure the connection is ok.
    if (state_ != kConnected) 
        return;

    ssize_t nwrote = 0;
    size_t remaining = message.size();
    bool fault_error = false;
        
    // When there is no data waiting to send, send directly.
    if (!channel_->IsWriting() && output_buffer_.ReadableBytes() == 0) {
        nwrote = ::write(channel_->getfd(), message.data(), message.size());
        if (nwrote >= 0) {
            remaining -= nwrote;
            if (remaining == 0) {
                std::cerr << "Send ok" << std::endl;
            }
        }
        else {
            // Serious error when write data.
            if (errno != EAGAIN || errno != EWOULDBLOCK) {
                    fault_error = true;
            }
        }
    }
    
    // Register write.
    if (!fault_error && remaining > 0) {
        output_buffer_.Append(message.data() + nwrote, message.size() - nwrote);
        if (!channel_->IsWriting())
            channel_->EnableWriting();
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

void TcpConnection::UpgradeWebSocket() {
    channel_->DisableAll();
}

