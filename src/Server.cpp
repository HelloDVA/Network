#include"Channel.h"
#include"Server.h"
#include"Socket.h"
#include"EventLoop.h"
#include"Acceptor.h"
#include"Connection.h"
#include"ThreadPool.h"
#include"Log.h"

#include<iostream>
#include<functional>

Server::Server(){
    // create main_reactor subreactors, Acceptor and ThreadPool 
    // use main_reactor create Acceptor. Acceptor will let server get new connections

	main_reactor = std::make_unique<EventLoop>();
    Log::getlog()->WriteLog(LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, "main reactor is created");

    for(int i = 0; i < size; i ++){
		std::unique_ptr<EventLoop> subreactor = std::make_unique<EventLoop>();
		reactors.push_back(std::move(subreactor));
	}
    Log::getlog() -> WriteLog(LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, "subreactors ready");

    acceptor = std::make_unique<Acceptor>(main_reactor.get());
    Log::getlog() -> WriteLog(LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, "Acceptor ready");
    std::function<void(int)> cb = std::bind(&Server::ConnectNew, this, std::placeholders::_1);
    acceptor -> setnewconnectioncallback(cb);

    int size = 10; 
    threadpool = std::make_unique<ThreadPool>(size);
    Log::getlog() -> WriteLog(LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, "ThreadPool ready");
}

Server::~Server(){

}

void Server::Start(){
    // one loop one thread
	int size = 10;
    for(int i = 0; i < size; i ++){
        std::function<void()> func = std::bind(&EventLoop::Loop, reactors[i].get());
        threadpool -> Add(std::move(func));
    }

    Log::getlog()->WriteLog(LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, "server start");
	main_reactor->Loop();
}

void Server::ConnectNew(int client_fd){
     //use random strategy to get subreactor  
     int number = client_fd % reactors.size(); 
	
	 std::unique_ptr<Connection> connection = std::make_unique<Connection>(reactors[number].get(), client_fd);

     std::function<void(int client_fd)> callback = std::bind(&Server::DeleteConnection, this, std::placeholders::_1);

      connection -> setdeletecallback(callback);

	  connections[client_fd] = std::move(connection);
}

void Server::DeleteConnection(int fd)
{
    connections.erase(fd);
}
