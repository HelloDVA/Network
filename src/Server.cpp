#include"Channel.h"
#include"Server.h"
#include"Socket.h"
#include"EventLoop.h"
#include"Acceptor.h"
#include"Connection.h"
#include"ThreadPool.h"

#include<iostream>
#include<functional>

Server::Server(){
    // use main_reactor create acceptor.
    // acceptor will let server get new connections
	main_reactor = std::make_unique<EventLoop>();
    acceptor = std::make_unique<Acceptor>(main_reactor.get());
	
	// bind connection process function to acceptor
    std::function<void(int)> cb = std::bind(&Server::ConnectNew, this, std::placeholders::_1);
    acceptor -> setnewconnectioncallback(cb);

    //one loop one thread
    int size = 10; 
    threadpool = std::make_unique<ThreadPool>(size);
    for(int i = 0; i < size; i ++){
		std::unique_ptr<EventLoop> subreactor = std::make_unique<EventLoop>();
		reactors.push_back(std::move(subreactor));
	}
	
}

Server::~Server(){}

void Server::Start(){
	int size = 10;
    for(int i = 0; i < size; i ++){
        std::function<void()> func = std::bind(&EventLoop::Loop, reactors[i].get());
        threadpool -> Add(std::move(func));
    }

	// ready to start the server
	main_reactor->Loop();
	
	std::cout << "server start\n";
}

void Server::ConnectNew(int client_fd){
     //use random strategy to get subreactor  
     int number = client_fd % reactors.size(); 
	
	 //use subreactor to create new connection
	 std::unique_ptr<Connection> connection = std::make_unique<Connection>(reactors[number].get(), client_fd);

     std::function<void(int client_fd)> callback = std::bind(&Server::DeleteConnection, this, std::placeholders::_1);

      connection -> setdeletecallback(callback);

	  connections[client_fd] = std::move(connection);
}

void Server::DeleteConnection(int fd)
{
    connections.erase(fd);
}
