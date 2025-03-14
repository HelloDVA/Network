#include"Acceptor.h"
#include"EventLoop.h"
#include"Socket.h"
#include"Channel.h"
#include"Log.h"

#include<fcntl.h>
#include<iostream>

Acceptor::Acceptor(EventLoop *_loop){
    loop = _loop;
    //initial server_sock. register server_channel

    //addr = new InetAddress("127.0.0.1", 8888); 
    socket = std::make_unique<Socket>();
    socket -> Create();
    socket -> Bind("127.0.0.1", 8080);
    socket -> Listen();

    //accept not use ThreadPoll and do not use ET
    accept_channel = std::make_unique<Channel>(loop, socket -> getfd(), false);

    std::function<void()> _callback = std::bind(&Acceptor::AcceptConnection,this);
    accept_channel -> setfunction(_callback);
    accept_channel -> EnableRead();
}

Acceptor::~Acceptor(){}

void Acceptor::AcceptConnection(){
    // accept client_sock. use server::connection to create connection.
    int client_fd = -1;
    socket -> Accept(client_fd);
    fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL) | O_NONBLOCK);
    newconnectioncallback(client_fd);
}

void Acceptor::setnewconnectioncallback(std::function<void(int)> _cb){
    newconnectioncallback = _cb;
}

