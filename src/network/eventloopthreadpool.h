#pragma once

#include <memory>
#include <vector>
#include <atomic>
#include <string>
#include <functional>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool {
    public:
        using ThreadInitCallback = std::function<void(EventLoop*)>;

        EventLoopThreadPool(EventLoop* base_loop, const std::string& name, int num_thread);
        ~EventLoopThreadPool();

        void Start(const ThreadInitCallback& cb = ThreadInitCallback());
        
        EventLoop* GetNextLoop();  

        void setnumthread(int num_thread) {num_thread_ = num_thread;}

    private:
        EventLoop* base_loop_;
        std::string name_;
        bool started_;
        int num_thread_;
        std::atomic<int> next_;
        std::vector<std::unique_ptr<EventLoopThread>> threads_;
        std::vector<EventLoop*> loops_;
};




