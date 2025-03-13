#include<sys/socket.h> 
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>

#include"InetAddress.h"
#include"utils.h" 
#include"Socket.h" 

using namespace std;

Socket::Socket(){
	fd = 0;
}

Socket::Socket(int _fd) : fd(_fd) {}

Socket::~Socket(){
    if(fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

RC Socket::Create(){
    assert(fd != -1);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("Failde to create socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::SetNonBlocking(){
    int state = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK);
	if(state == -1){
		perror("Socket set NonBlock error");
		return RC_SOCKET_ERROR;
	}
	else
		return RC_SUCCESS;
}

RC Socket::Bind(const char *ip, uint16_t port) const{

    assert(fd != -1);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int bind_state = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(bind_state == -1){
        perror("Create Socket Error");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::Listen(){
    assert(fd != -1);
    int listen_state = listen(fd, SOMAXCONN);
    if(listen_state == -1){
        perror("Listen Socket Error");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::Accept(int &clientfd){
    assert(fd != -1);
    clientfd = accept(fd, NULL, NULL);
    if(clientfd == -1){
        perror("Failed to accept socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

int Socket::getfd() const {
    return fd;
}

RC Socket::Connect(const char *ip, uint16_t port)
{
    assert(fd != -1);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int connect_state = connect(fd, (sockaddr*)&addr, sizeof(addr));
    if(connect_state == -1){
        perror("Failed to Connect socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

