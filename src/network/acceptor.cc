

#include <memory>

#include "acceptor.h"
#include "sockets.h"
#include "inetaddress.h"
#include "channel.h"

Acceptor::Acceptor(EventLoop* loop, const InetAddress& addr) 
    : loop_(loop), 
      accept_channel_(nullptr), 
      listen_addr_(addr) {
    // Initialize accept_channel_ here, e.g., create a Channel for the listening socket

    accept_socket_fd_ = sockets::CreateNonblockingOrDie();
    sockets::Bind(accept_socket_fd_, listen_addr_);

    accept_channel_ = std::make_unique<Channel>(loop_, accept_socket_fd_);
    accept_channel_->setreadcallback([this]() {HandleRead();});

    loop_->AssertInLoopThread();
    accept_channel_->EnableReading();
}

Acceptor::~Acceptor() {
    loop_->AssertInLoopThread();
    accept_channel_->DisableAll();
    sockets::Close(accept_socket_fd_);
}

void Acceptor::Listen() {
    sockets::Listen(accept_socket_fd_);
}

void Acceptor::HandleRead() {
    InetAddress* peer_addr = new InetAddress();
    sockets::Accept(accept_socket_fd_, peer_addr);
    if (newconnectioncallback_) {
        newconnectioncallback_(accept_socket_fd_, *peer_addr);
    }
}
