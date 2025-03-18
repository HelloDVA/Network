#include<unistd.h>
#include<iostream>
#include<string.h>

#include"Connection.h"
#include"EventLoop.h"
#include"Channel.h"
#include"Buffer.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"Log.h"


Connection::Connection(EventLoop *_loop, int _fd){
    loop = _loop;
	fd = _fd;
    buffer = std::make_unique<Buffer>();
	request_ = std::make_unique<HttpRequest>();
	response_ = std::make_unique<HttpResponse>();
    
    connection_channel = std::make_unique<Channel>(loop, fd, true);
    std::function<void()> cb = std::bind(&Connection::HttpConnection, this, fd); 
    connection_channel -> setfunction(cb);
    connection_channel -> EnableRead();
    connection_channel -> EnableET();
    Log::getlog() -> WriteLog(LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, "New Connection ready");
}

Connection::~Connection(){}

void Connection::HttpConnection(int fd){
	if(fd == -1){
   	     return;
    }

    // read request
    while(true){
        char read_buffer[1024];
        bzero(&read_buffer, sizeof(read_buffer));
        int read_state = read(fd, &read_buffer, sizeof(read_buffer));
        if(read_state > 0)
                buffer -> Append(read_buffer, read_state); 
        if(read_state == 0){
                std::cout << "the client out\n";
                close(fd);
                return;
        }else{
			break;
		}
    }

 	// prase request
    request_ -> Parse(std::move(buffer));

    // create response
    response_ -> MakeResponse(request_->getpath(), request_ -> getversion());
    
    // send response
    std::string response_message = response_ -> ToString();
	std::cout << response_message;
    write(fd, response_message.c_str(), response_message.size());
    close(fd);	
}

//void Connection::Echo(int fd){
		//while(true){
				//char read_buffer[1024];
				//bzero(&read_buffer, sizeof(read_buffer));
				//int read_state = read(fd, &read_buffer, sizeof(read_buffer));
				//if (read_state > 0)
						//buffer -> Append(read_buffer, read_state); 
				//if(read_state == 0){
						//std::cout << "the client out\n";
						//close(fd);
						//break;
				//}
				//if(read_state == -1 && (errno == EAGAIN) || (errno == EWOULDBLOCK)){
						//std::cout << fd << buffer -> Cstr() << std::endl;
						//errif(write(fd, buffer -> Cstr(), buffer -> Size() == -1), "socket write error");
						//buffer -> Clean();
						//break;
				//}
		//}
//}

void Connection::setdeletecallback(std::function<void(int fd)> callback){
		deletecallback = callback;
}
