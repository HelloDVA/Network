#pragma once

#include "../utils/buffer.h"

#include <memory>
#include <string>
#include <functional>

#include "eventloop.h"
#include "channel.h"
#include "inetaddress.h"



class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

    using ReadCallback = std::function<void(const TcpConnectionPtr&, Buffer*)>;
    using WriteCallback = std::function<void(const TcpConnectionPtr&, Buffer*)>;
    using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
    using ErrorCallback = std::function<void(const TcpConnectionPtr&)>;

    TcpConnection(EventLoop* loop,
                  const std::string& name,
                  int sockfd,
                  const InetAddress& localAddr,
                  const InetAddress& peerAddr);
    ~TcpConnection();
    
    // when create and close do in loop
    void ConnectEstablished();   // 连接建立完成 after tcpserver::NewConnection run
    void ConnectDestroyed();     // 连接销毁 after tcpserver::CloseConnection run
    
    // server initivative methods
    void Send(const std::string& message); // send message and activate EPOLLWRITE 
    void Send(Buffer* message);
    void Shutdown();             // 关闭写端

    EventLoop* getloop() const { return loop_; }
    const std::string& getname() const { return name_; }
    const InetAddress& getlocaladdr() const { return local_addr_; }
    const InetAddress& getpeeraddr() const { return peer_addr_; }
    bool state() const { return state_ == kConnected; }
    void setreadcallback(ReadCallback cb) { read_callback_ = std::move(cb); }
    void setwritecallback(WriteCallback cb) { write_callback_ = std::move(cb); }
    void setclosecallback(CloseCallback cb) { close_callback_ = std::move(cb); }
    void seterrorcallback(ErrorCallback cb) { error_callback_ = std::move(cb); }

private:
    enum State { kDisconnected, kConnecting, kConnected, kDisconnecting };
    void setstate(State s) { state_ = s; }
    
    // callback for epoll events 
    void HandleRead();
    void HandleWrite();
    void HandleClose();
    void HandleError(int err);
    
    // do action in loop
    void SendInLoop(const std::string& message);
    void ShutdownInLoop();

private:
    EventLoop* loop_;
    std::string name_;
    State state_;
    
    std::unique_ptr<Channel> channel_;
    InetAddress local_addr_;
    InetAddress peer_addr_;
    
    // callback for service events such as GameServer, LogServer.
    ReadCallback read_callback_;
    WriteCallback write_callback_;
    CloseCallback close_callback_;
    ErrorCallback error_callback_;

    Buffer input_buffer_;        // 接收缓冲区
    Buffer output_buffer_;       // 发送缓冲区
};

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
