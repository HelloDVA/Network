#include"EventLoop.h"
#include"Channel.h"
#include"Epoll.h"

#include<iostream>
#include<vector>

EventLoop::EventLoop(){
    epoll = std::make_unique<Epoll>();
}

EventLoop::~EventLoop(){}

void EventLoop::Loop(){
    while(true){
        std::vector<Channel*> channel_active = epoll->Poll();
        int length = channel_active.size();
        
        //use channel to add the task to ThreadPool
        //ThreadPool is running and waiting for process tasks
        for(int i = 0; i < length; i ++)
                channel_active[i] -> HandleEvent();
    }
}

void EventLoop::UpdateChannel(Channel *ch){
   epoll->UpdateChannel(ch); 
}

void EventLoop::DeleteChannel(Channel *ch){
	epoll -> DeleteChannel(ch);
}
