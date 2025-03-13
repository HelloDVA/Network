#include<iostream>
#include"Server.h"
using namespace std;


int main()
{
    //epoll is in EventLoop
    //create EventLoop and epoll
    Server *server = new Server();
	server -> Start();
    return 0;
}
