#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <string>

#include "inetaddress.h"
#include "tcpconnection.h"

class Acceptor;
class EventLoop;
class InetAddress;
class EventLoopThreadPool;
class TcpConnection;

class TcpServer {
public:
    using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*)>;
    using ThreadInitCallback = std::function<void(EventLoop*)>;

public:
    TcpServer(EventLoop* loop, const InetAddress& addr);
    ~TcpServer();

    void Start();

    void setconnectioncallback(const ConnectionCallback& cb) { connection_callback_ = cb; }
    void setmessagecallback(const MessageCallback& cb) { message_callback_ = cb; }
    void setthreadinitcallback(const ThreadInitCallback& cb) { thread_init_callback_ = cb; }

private:
    // process new connection
    void NewConnection(int sockfd, const InetAddress& peer_addr);
    void CloseConnection(const TcpConnection::TcpConnectionPtr& conn);
    void CloseConnectionInLoop(const TcpConnection::TcpConnectionPtr& conn);

private:
    EventLoop* loop_;
    InetAddress local_addr_;
    std::string name_;
    bool started_;
    std::unique_ptr<Acceptor> acceptor_;
    std::unordered_map<std::string, TcpConnection::TcpConnectionPtr> connections_;
    std::unique_ptr<EventLoopThreadPool> thread_pool_;
    
    // server callback function for server service
    // pass to connection and use
    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    ThreadInitCallback thread_init_callback_;
};
