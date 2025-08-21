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
        
        // process network io things and other things
        void Loop();
        void Quit();

        // if the task is mine call cb
        // else add cb to pending_functors_ waiting its master
        void RunInLoop(Functor cb);
        void QueueInLoop(Functor cb);

        // test the current thread whether is the loop thread
        bool IsInLoopThread() const;
        // make sure the action is running in the loop thread
        void AssertInLoopThread();

        void UpdateChannel(Channel* channel);
        void RemoveChannel(Channel* channel);

        void Wakeup();  
        
    private:
        void DoPendingFunctors();

        // handle wake up 
        void HnadleRead();
    
        // get active channels from poller
        std::unique_ptr<EpollPoller> poller_;
        std::vector<Channel*> activate_channels_;
        
        // get functor 
        std::mutex mutex_;
        std::vector<Functor> pending_functors_;
        
        // use for wake up loop
        int wakeup_fd_;
        std::unique_ptr<Channel> wakeup_channel_;

        // event loop state
        std::thread::id thread_id_;
        bool looping_;
        bool quiting_;
};
