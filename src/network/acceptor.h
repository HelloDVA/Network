#pragma once

#include <memory>
#include <functional>

#include "inetaddress.h"

class EventLoop;
class Channel;
class InetAddress;

class Acceptor {
    public:
        using NewConnectionCallback = std::function<void(int sockfd, const InetAddress& peer_addr)>;

        Acceptor(EventLoop* loop, const InetAddress& addr);
        ~Acceptor();

        void setnewconnectionCallback(std::function<void(int sockfd, const InetAddress& peer_addr)> callback) {
            newconnectioncallback_ = std::move(callback);
        }

        void Listen();

    private:
        void HandleRead();

    private:
        EventLoop *loop_;
        InetAddress listen_addr_;
        std::unique_ptr<Channel> accept_channel_;
        int accept_socket_fd_;
        NewConnectionCallback newconnectioncallback_;
};
