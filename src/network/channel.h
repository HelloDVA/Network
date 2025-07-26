#pragma once
#include <functional>
#include "EventLoop.h"

class Channel : public std::enable_shared_from_this<Channel> {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void()>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void HandleEvent();
    void setreadcallback(ReadEventCallback cb) { read_callback_ = std::move(cb); }
    void setwritecallback(EventCallback cb) { write_callback_ = std::move(cb); }
    void setclosecallback(EventCallback cb) { close_callback_ = std::move(cb); }
    void seterrorcallback(EventCallback cb) { error_callback_ = std::move(cb); }
    void setrevents(int events) { revents_ = events; }
    void setstate(int state) { state_ = state; }
    int getstate() const { return state_; }
    int getfd() const { return fd_; }
    int getevents() const { return events_; }
    void EnableReading() { events_ |= kReadEvent; Update(); }
    void DisableAll() { events_ = 0; Update(); }

private:
    void Update();

    static const int kReadEvent;
    static const int kWriteEvent;
    static const int kCloseEvent;
    static const int kErrorEvent;

    EventLoop* loop_;
    int fd_;
    int events_;
    int revents_;
    int state_; // 0 exist -1 not exist

    ReadEventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;
    EventCallback error_callback_;
};