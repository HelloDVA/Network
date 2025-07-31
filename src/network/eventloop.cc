#include <unistd.h>

#include <memory>
#include <stdexcept>

#include"eventloop.h"
#include"epollpoller.h"

#include "channel.h"

EventLoop::EventLoop() 
    : poller_(std::make_unique<EpollPoller>()), 
    wakeup_fd_(-1),
    thread_id_(std::this_thread::get_id()),
    looping_(false),
    quiting_(false)
    {
}

EventLoop::~EventLoop(){}

void EventLoop::Loop() {
    AssertInLoopThread();
    looping_ = true;
    quiting_ = false;

    while (!quiting_) {
        activate_channels_.clear();
        // Poll events from the poller
        poller_->Poll(-1, activate_channels_);

        // network events first
        for (Channel* channel : activate_channels_) {
            channel->HandleEvent();
        }

        // pending functors second
        DoPendingFunctors();
    }
    looping_ = false;
}

void EventLoop::UpdateChannel(Channel* channel) {
    AssertInLoopThread();
    poller_->UpdateChannel(channel);
}

void EventLoop::RemoveChannel(Channel* channel) {
    AssertInLoopThread();
    poller_->RemoveChannel(channel);
}

void EventLoop::DoPendingFunctors() {
    std::vector<Functor> functors;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        functors.swap(pending_functors_);
    }
    
    for (const auto& functor : functors) {
        functor();
    }
}

void EventLoop::Quit() {
    quiting_ = true;
    if (!IsInLoopThread()) {
        Wakeup();  
    }
}

void EventLoop::RunInLoop(Functor cb) {
    // If we're already in the loop thread, run the callback immediately
    // Otherwise, queue it to be run later
    if (IsInLoopThread()) 
        cb();
    else 
        QueueInLoop(std::move(cb));
}

void EventLoop::QueueInLoop(Functor cb) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pending_functors_.emplace_back(cb);
    }
    if (!IsInLoopThread() || quiting_) {
        Wakeup();
    }
}

bool EventLoop::IsInLoopThread() const {
    return thread_id_ == std::this_thread::get_id();
}

void EventLoop::AssertInLoopThread() {
    if (!IsInLoopThread()) {
        throw std::runtime_error("EventLoop::AssertInLoopThread - not in loop thread");
    }
}

void EventLoop::Wakeup() {
    uint64_t one = 1;
    ssize_t n = ::write(wakeup_fd_, &one, sizeof(one));
    if (n != sizeof one) {
        throw std::runtime_error("EventLoop::Wakeup - write wakeup failed");
    }
}
