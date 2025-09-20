#include "tcpserver.h"
#include "eventloop.h"
#include "inetaddress.h"
#include "tcpconnection.h"
#include "buffer.h"
#include "globallogger.h"

#include <string>
#include <iostream>

void Test(const TcpConnectionPtr& conn, Buffer* buffer) {
    // Process the received data
    std::string message(buffer->Peek(), buffer->ReadableBytes());

    std::cout << "Received message: " << message << std::endl;

    std::string http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 12\r\n"
        "Connection: Keep-Alive\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello World!";

    // Echo back to client
    conn->Send(http_response);

    // Clear the buffer
    buffer->RetrieveAll();
}

int main() 
{
    // Initialize globallogger system
    GlobalLogger::Initialize("server");
    
    // Create server address.
    std::string ip = "127.0.0.1";
    int port = 8081;
    InetAddress addr(ip.c_str(), port);
    //LOG_INFO("server addr ok");

    // Initialize gomoku server through address and main-loop.
    EventLoop loop;

    // bench test code
    TcpServer server(&loop, addr);
    server.setmessagecallback(Test);
    server.Start();
    //LOG_INFO("server started");
    
    // Start main-loop.
    loop.Loop();

    return 0;
}

