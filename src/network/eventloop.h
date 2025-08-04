#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <mutex>
#include <thread>


class EpollPoller;
class Channel;

class EventLoop
{
    public:
        using Functor = std::function<void()>;

        EventLoop();
        ~EventLoop();
        
        // process network io and other things
        void Loop();
        // if the task is mine call cb
        // else add cb to pending_functors_ waiting its master
        void RunInLoop(Functor cb);
        void QueueInLoop(Functor cb);

        void UpdateChannel(Channel* channel);
        void RemoveChannel(Channel* channel);

        void Quit();
        void Wakeup();  
        // test the current thread whether is the loop thread
        bool IsInLoopThread() const;
        // make sure the action is running in the loop thread
        void AssertInLoopThread();

        
    private:
        void DoPendingFunctors();
    
    private:
        std::unique_ptr<EpollPoller> poller_;
        std::vector<Channel*> activate_channels_;
        
        std::mutex mutex_;
        std::vector<Functor> pending_functors_;
        int wakeup_fd_;
        std::thread::id thread_id_;

        // event loop state
        bool looping_;
        bool quiting_;
};
