

#include "./network/tcpserver.h"
#include "./network/eventloop.h"
#include "./network/inetaddress.h"
#include "./network/tcpconnection.h"
#include "./utils/buffer.h"

#include <string>

void Test(const TcpConnectionPtr& conn, Buffer* buffer) {
    
}



int main() 
{
    std::string ip = "127.0.0.1";
    int port = 8081;
    InetAddress addr(ip.c_str(), port);
    EventLoop loop;
    TcpServer server(&loop, addr);
    server.setmessagecallback(Test);
    server.Start();
    loop.Loop();
    return 0;
}
