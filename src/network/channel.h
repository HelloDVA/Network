#pragma once
#include <functional>
#include <iostream>

#include "eventloop.h"

class Channel {
public:
    using EventCallback = std::function<void()>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void HandleEvent();
    void EnableReading() { events_ |= kReadEvent; Update(); }
    void DisableReading() { events_ &= ~kReadEvent; Update(); }
    void EnableWriting() { events_ |= kWriteEvent; Update(); }
    void DisableWriting() { events_ &= ~kWriteEvent; Update(); }
    void DisableAll() { events_ = 0; Update(); }
    void RemoveChannel() { Remove(); }

    bool IsReading() const { return events_ & kReadEvent; }
    bool IsWriting() const { return events_ & kWriteEvent; }

    void setreadcallback(EventCallback cb) { read_callback_ = std::move(cb); }
    void setwritecallback(EventCallback cb) { write_callback_ = std::move(cb); }
    void setclosecallback(EventCallback cb) { close_callback_ = std::move(cb); }
    void setrevents(int events) { revents_ = events; }
    void setstate(int state) { state_ = state; }

    int getstate() const { return state_; }
    int getfd() const { return fd_; }
    int getevents() const { return events_; }

private:
    void Update();
    void Remove();

private:
    EventLoop* loop_;
    int fd_;
    int events_;
    int revents_;
    int state_; // 0 exist -1 not exist

    EventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;

    static const int kReadEvent;
    static const int kWriteEvent;
    static const int kCloseEvent;
    static const int kErrorEvent;
};
