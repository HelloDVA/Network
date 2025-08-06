

#include "./network/tcpserver.h"
#include "./network/eventloop.h"
#include "./network/inetaddress.h"
#include "./network/tcpconnection.h"
#include "./utils/buffer.h"
#include "./utils/asynclogger.h"

#include <string>
#include <memory>
#include <iostream>


void Test(const TcpConnectionPtr& conn, Buffer* buffer) {
    // Process the received data
    std::string message(buffer->Peek(), buffer->ReadableBytes());
    std::cout << "Received message: " << message << std::endl;
    
     std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 15\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello, WebBench!";

    // Echo back to client
    conn->Send(response);

    // Clear the buffer
    buffer->RetrieveAll();
}

std::unique_ptr<AsyncLogger> logger;

int main() 
{
    /* logger = std::make_unique<AsyncLogger>("TcpServerLogger"); */
    /* logger->Start(); */

    std::string ip = "127.0.0.1";
    int port = 8081;
    InetAddress addr(ip.c_str(), port);
    //logger->Append("Server addr ok", sizeof("Server addr ok"));
    
    EventLoop loop;
    TcpServer server(&loop, addr);
    server.setmessagecallback(Test);
    server.Start();
    std::cout << "main 33 server start\n";

    loop.Loop();
    return 0;
}
