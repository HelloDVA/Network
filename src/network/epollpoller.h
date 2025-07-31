#pragma once

#include <vector>

#include <sys/epoll.h>

#include "poller.h"

class Channel;

class EpollPoller : public Poller {

    public:
        EpollPoller();
        ~EpollPoller() override;

        virtual void Poll(int timeout_ms, std::vector<std::shared_ptr<Channel>>& activate_channels) override;
        virtual void RemoveChannel(Channel* channel) override;
        virtual void UpdateChannel(Channel* channel) override;

    private:
        static const int MAX_EVENTS = 1024;
        int epollfd_;
        std::vector<epoll_event> events_;   // keep the active events
};