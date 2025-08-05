
#include <sys/epoll.h>

#include <iostream>

#include "channel.h"
#include "epollpoller.h"


const int Channel::kReadEvent = EPOLLIN;
const int Channel::kWriteEvent = EPOLLOUT;
const int Channel::kCloseEvent = EPOLLHUP;
const int Channel::kErrorEvent = EPOLLERR;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      state_(-1) {}

Channel::~Channel() {}

void Channel::HandleEvent() { 
    // priority from high to low
    if (revents_ & kErrorEvent && error_callback_) 
        error_callback_();
    if (revents_ & kCloseEvent && close_callback_) 
        close_callback_();
    if (revents_ & kReadEvent && read_callback_) 
        read_callback_();
    if (revents_ & kWriteEvent && write_callback_) 
        write_callback_();
}

void Channel::Update() {
  std::cout << "Channel::Update() called for fd=" << fd_ << std::endl;
  loop_->UpdateChannel(this);
}

void Channel::Remove() {
    loop_->RemoveChannel(this);
}



