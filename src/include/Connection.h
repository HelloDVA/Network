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
		int fd;
        //use and possess
        std::unique_ptr<Channel> connection_channel;
        std::unique_ptr<Buffer> buffer;
        std::function<void(int fd)> deletecallback;
		
		std::unique_ptr<HttpRequest> request_;
		std::unique_ptr<HttpResponse> response_;
		
		
	public:
        Connection(EventLoop *_loop, int _fd);
        ~Connection();
        void setdeletecallback(std::function<void(int fd)> callback);
		
        //void Echo(int fd);

		void HttpConnection(int fd);
};
