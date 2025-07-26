#pragma once


class InetAddress;

namespace sockets {
    int CreateNonblockingOrDie();
    void Bind(int sockfd, const InetAddress& addr);
    void Connect(const InetAddress& addr);
    void Listen(int sockfd);
    int Accept(int sockfd, InetAddress* addr);
    void Close(int sockfd);
    void Write(int sockfd);
}