#include<iostream>
#include"Server.h"
using namespace std;


int main()
{
    //epoll is in EventLoop
    //create EventLoop and epoll
    Server server;
	server.Start();
    return 0;
}
