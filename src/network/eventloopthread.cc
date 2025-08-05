

#include "eventloopthread.h"
#include "eventloop.h"
#include <cassert>
#include <mutex>


EventLoopThread::EventLoopThread(const ThreadInitCallback& cb , const std::string &name) 
    : loop_(nullptr),
      exiting_(false),
      callback_(cb),
      name_(name) {
}

EventLoopThread::~EventLoopThread() {
  exiting_ = true;
  if (loop_ != nullptr) 
    loop_->Quit();
  if (thread_.joinable())
    thread_.join();
}

EventLoop* EventLoopThread::StartLoop() {
  assert(!thread_.joinable()); 

  thread_ = std::thread([this] () {ThreadFunc();});

  EventLoop* loop;
  // waitting the loop_ created
  {
    std::unique_lock<std::mutex> lock(mutex_);
    while (loop_ == nullptr)
      cv_.wait(lock);
    loop = loop_;
  }
  return loop;
}

void EventLoopThread::ThreadFunc() {
  EventLoop loop;
  if (callback_)
    callback_(&loop);

  {
    std::lock_guard<std::mutex> lock(mutex_); 
    loop_ = &loop;
    cv_.notify_one();
  }

  loop.Loop(); 

  std::lock_guard<std::mutex> lock(mutex_);
  loop_ = nullptr;
}

