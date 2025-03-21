#pragma once
#include<functional>
#include<memory>

class EventLoop;
class Socket;
class Channel;
class Buffer;
class HttpRequest;
class HttpResponse;

class Connection{
    private:
        //just use
        EventLoop *loop;
        //use and possess
		std::unique_ptr<Socket> client_socket;
        std::unique_ptr<Channel> connection_channel;
        std::unique_ptr<Buffer> buffer;
		
		std::unique_ptr<HttpRequest> request_;
		std::unique_ptr<HttpResponse> response_;
		
        std::function<void(int fd)> deletecallback;
		
	public:
        Connection(EventLoop *_loop, int _fd);
        ~Connection();
        void setdeletecallback(std::function<void(int fd)> callback);
		
        //void Echo(int fd);

		void HttpConnection();
};
