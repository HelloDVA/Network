#pragma once

#include <memory>
#include <functional>

class EventLoop;
class Channel;
class InetAddress;

class Acceptor {
    public:
        using NewConnectionCallback = std::function<void(int sockfd, const InetAddress& peer_addr)>;

        Acceptor(EventLoop* loop);
        ~Acceptor();

        void AcceptConnection();
        void setnewconnectionCallback(std::function<void(int sockfd, const InetAddress& peer_addr)> callback) {
            newconnectioncallback_ = std::move(callback);
        }


    private:
        int accept_socket_fd_;
        EventLoop *loop_;
        std::unique_ptr<Channel> accept_channel_;
        std::unique_ptr<InetAddress> listen_addr_;
        NewConnectionCallback newconnectioncallback_;
};