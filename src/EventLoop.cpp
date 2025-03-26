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
        //use channel to add the task to ThreadPool
        //ThreadPool is running and waiting for process tasks
        std::vector<Channel*> channel_active = epoll->Poll();
        int length = channel_active.size();
        for(int i = 0; i < length; i ++){
            int revents_active = channel_active[i]->getrevents();
			if(revents_active & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
				continue;	
			}
			channel_active[i] -> HandleEvent();
		}
    }
}

void EventLoop::UpdateChannel(Channel *ch){
   epoll->UpdateChannel(ch); 
}

void EventLoop::DeleteChannel(Channel *ch){
	epoll -> DeleteChannel(ch);
}
