server : ThreadPool.o Buffer.o Connection.o Acceptor.o InetAddress.o Socket.o utils.o Epoll.o Channel.o EventLoop.o Server.o server.o
	g++ -o server ThreadPool.o Buffer.o Connection.o Acceptor.o InetAddress.o Socket.o utils.o Epoll.o Channel.o EventLoop.o Server.o server.o -pthread	

ThreadPool.o : src/ThreadPool.cpp
	g++ -c src/ThreadPool.cpp -std=c++11
Buffer.o : src/Buffer.cpp	
	g++ -std=c++11 -c src/Buffer.cpp
Connection.o : src/Connection.cpp
	g++ -std=c++11 -c src/Connection.cpp 
Acceptor.o : src/Acceptor.cpp
	g++ -std=c++11 -c src/Acceptor.cpp 
InetAddress.o: src/InetAddress.cpp
	g++ -std=c++11 -c src/InetAddress.cpp 
Socket.o : src/Socket.cpp
	g++ -std=c++11 -c src/Socket.cpp 
utils.o : src/utils.cpp
	g++ -std=c++11 -c src/utils.cpp 
Epoll.o : src/Epoll.cpp
	g++ -c src/Epoll.cpp -std=c++11 
Channel.o : src/Channel.cpp
	g++ -c src/Channel.cpp -std=c++11 
EventLoop.o : src/EventLoop.cpp
	g++ -std=c++11 -c src/EventLoop.cpp 
Server.o : src/Server.cpp
	g++ -std=c++11 -c src/Server.cpp 
server.o : server.cpp
	g++ -std=c++11 -c server.cpp 
	
clean :
	rm -f ./*.o
