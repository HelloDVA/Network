#pragma once


#include <condition_variable>
#include <functional>
#include <thread>
#include <string>

class EventLoop;

class EventLoopThread {
    public:
        using ThreadInitCallback = std::function<void(EventLoop*)>;
       
        EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(), 
                const std::string &name = std::string());
        ~EventLoopThread();
        
        // create thread and return loop
        EventLoop* StartLoop();

        const std::string& getname() const {return name_;}

    private:
        void ThreadFunc();

    private:
        EventLoop* loop_;
        bool exiting_;
        std::thread thread_;
        std::mutex mutex_;
        std::condition_variable cv_;
        ThreadInitCallback callback_;  // initivate the loop before the thread start
        std::string name_;
};
