
#pragma once

#include <functional>
#include <memory>
#include <unordered_map>


#include "EventLoop.h"
#include "connection.h"
#include "inetaddress.h"


class TcpServer {
public:
    using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using MessageCallback = std::function<void(const TcpConnectionPtr&, std::string*)>;

    TcpServer(EventLoop* loop, const InetAddress& addr);
    ~TcpServer();

    void SetConnectionCallback(ConnectionCallback cb) { connection_callback_ = std::move(cb); }
    void SetMessageCallback(MessageCallback cb) { message_callback_ = std::move(cb); }
    void SetThreadNum(int numThreads);

    void Start();

private:
    void NewConnection(int sockfd, const InetAddress& peerAddr);
    void RemoveConnection(const TcpConnectionPtr& conn);
    void RemoveConnectionInLoop(const TcpConnectionPtr& conn);

    EventLoop* loop_;
    std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::unordered_map<std::string, TcpConnectionPtr> connections_;
    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    EventLoopThreadPool thread_pool_;
    bool started_;
};