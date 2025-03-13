#include"Epoll.h"
#include"utils.h"
#include"Channel.h"
#include<iostream>
#include<unistd.h>

#define MAX_EVENTS 100
Epoll::Epoll(){
   epollfd = epoll_create1(0);
   errif(epollfd == -1, "epoll create error");
   events = new epoll_event[MAX_EVENTS];
   memset(events, 0, sizeof(events) * MAX_EVENTS);
}

Epoll::~Epoll(){
    if(epollfd == -1)
        close(epollfd);
    delete []events;
}

void Epoll::UpdateChannel(Channel *ch){
    int fd = ch->getfd();
    struct epoll_event ev{};

    ev.events = ch->getevents();
    ev.data.ptr = ch;

    if(!ch->getinepoll()){
        errif((epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev)) == -1, "epoll add event error");
        ch -> setinepoll();
    }
    else{
        errif((epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev)) == -1, "epoll add event error");
    }
}

std::vector<Channel*> Epoll::Poll(){
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, 1); 
    errif(nfds == -1, "epoll wait error");
    std::vector<Channel*> channel_active;
    for(int i = 0; i < nfds; i ++){
        Channel *ch = (Channel*) events[i].data.ptr;
        ch->setrevents(events[i].events);
        channel_active.push_back(ch);
    }
    return channel_active;
}
