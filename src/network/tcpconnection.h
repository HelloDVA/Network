#pragma once

#include <memory>
#include <string>
#include <functional>

#include "eventloop.h"
#include "channel.h"
#include "inetaddress.h"
#include "buffer.h"

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

    // 连接操作
    void ConnectEstablished();   // 连接建立完成
    void ConnectDestroyed();     // 连接销毁

    // 数据发送
    void Send(const std::string& message);
    void Send(Buffer* message);
    
    // 关闭连接
    void Shutdown();             // 关闭写端

    EventLoop* getloop() const { return loop_; }
    const std::string& getname() const { return name_; }
    const InetAddress& getlocaladdr() const { return local_addr_; }
    const InetAddress& getpeeraddr() const { return peer_addr_; }
    bool state() const { return state_ == kConnected; }
    // 设置回调函数
    void setreadcallback(ReadCallback cb) { read_callback_ = std::move(cb); }
    void setwritecallback(WriteCallback cb) { write_callback_ = std::move(cb); }
    void setclosecallback(CloseCallback cb) { close_callback_ = std::move(cb); }
    void seterrorcallback(ErrorCallback cb) { error_callback_ = std::move(cb); }

private:
    enum State { kDisconnected, kConnecting, kConnected, kDisconnecting };

    void HandleRead();
    void HandleWrite();
    void HandleClose();
    void HandleError();

    void setstate(State s) { state_ = s; }
    void SendInLoop(const std::string& message);
    void ShutdownInLoop();

private:
    EventLoop* loop_;
    std::string name_;
    State state_;
    
    std::unique_ptr<Channel> channel_;
    InetAddress local_addr_;
    InetAddress peer_addr_;

    ReadCallback read_callback_;
    WriteCallback write_callback_;
    CloseCallback close_callback_;
    ErrorCallback error_callback_;

    Buffer input_buffer_;        // 接收缓冲区
    Buffer output_buffer_;       // 发送缓冲区
};

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;