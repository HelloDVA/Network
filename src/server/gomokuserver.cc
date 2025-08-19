#include "../network/tcpserver.h"
#include "../network/eventloop.h"
#include "../network/inetaddress.h"

#include <boost/asio/io_context.hpp>
#include <memory>

#include "gomokuserver.h"
#include "httpprocess.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "websocket.h"

GomokuServer::GomokuServer(EventLoop* loop, const InetAddress& addr)
    : server_(std::make_unique<TcpServer>(loop, addr)) {
    server_->setmessagecallback([this](const TcpConnectionPtr& conn, Buffer* buffer) {OnMessage(conn, buffer);});
    server_->setconnectioncallback([this](const TcpConnectionPtr& conn) {OnConnection(conn);});
}

GomokuServer::~GomokuServer() {

}

void GomokuServer::OnMessage(const TcpConnectionPtr& conn, Buffer* buffer) {
    HttpRequest request;
    HttpResponse response;
    HttpProcess process;
    std::string message(buffer->Peek(), buffer->ReadableBytes());

    request.Parse(message);

    std::cout << "gomokuserver.cc 32 message: " << message << std::endl;

    if (request.getpath() == "/websocket") {
        std::cout << "gomokuserver.cc 33 websocket connected\n";
        
        // move connection fd epollevents from epoll 
        conn->UpgradeWebscoket();

        // use WebSocket
        int sockfd = conn->getsockfd();
        auto io_context = std::make_shared<net::io_context>();
        //net::io_context io_context;
        tcp::socket socket(*io_context);
        socket.assign(tcp::v4(), sockfd);
        std::shared_ptr<WebSocketSession> websocket = std::make_shared<WebSocketSession>(std::move(socket));    
        websocket->Start(message); 
        std::thread([io_context]() {
            io_context->run();
        }).detach();
        
    } else {
        // Http
        response = process.Process(request);
        conn->Send(response.ToString());
        buffer->RetrieveAll();
    }
}

void GomokuServer::OnConnection(const TcpConnectionPtr&) {

}

void GomokuServer::Start() {
    server_->Start();
}


