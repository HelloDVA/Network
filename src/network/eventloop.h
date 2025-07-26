#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <mutex>

class Epoll;
class Channel;

class EventLoop
{
    public:
        using Functor = std::function<void()>;

        EventLoop();
        ~EventLoop();

        void Loop();
        void Quit();

        // if the task is mine call cb
        // else add cb to pending_functors_ waiting its master
        void RunInLoop(Functor cb);
        void QueueInLoop(Functor cb);

        void Wakeup();  
        bool IsInLoopThread() const;

        // make sure the action is running in the loop thread
        void AssertInLoopThread();
        
    private:
        void DoPendingFunctors();

        std::unique_ptr<Epoll> poller_;
        vector<Channel*> activate_channels_;

        // event loop state
        bool looping_;
        bool quit_;

        int wakeup_fd_;

        std::thread::id thread_id_;

        std::mutex mutex_;
        std::vector<Functor> pending_functors_;
};
