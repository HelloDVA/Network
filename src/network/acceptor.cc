

#include <string>

#include "acceptor.h"
#include "sockets.h"
#include "inetaddress.h"



Acceptor::Acceptor(EventLoop* loop)
    : loop_(loop), accept_channel_(nullptr), listen_addr_(nullptr) {
    // Initialize accept_channel_ here, e.g., create a Channel for the listening socket
    std::string ip = "127.0.0.1";
    int port = 8081;
    listen_addr_ = std::make_unique<InetAddress>(ip, port); 
    accept_socket_fd_ = sockets::CreateNonblockingOrDie();
    sockets::Bind(accept_socket_fd_, *listen_addr_);
    sockets::Listen(accept_socket_fd_);
}

Acceptor::~Acceptor() {
    // Clean up resources if necessary
}

void Acceptor::AcceptConnection() {
    InetAddress* peer_addr = new InetAddress();
    sockets::Accept(accept_socket_fd_, peer_addr);
    if (newconnectioncallback_) {
        newconnectioncallback_(*peer_addr);
    }
}
