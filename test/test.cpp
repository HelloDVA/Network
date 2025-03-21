#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		std::cout << "create sock error\n";
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8080);

	int connect_result = connect(sock, (sockaddr*)&server_addr, sizeof(server_addr));
	if(connect_result == -1)
		std::cout << "connect error\n";
	
	while(true){
		char buffer[1024];
		memset(&buffer, 0, sizeof(buffer));
		std::cin >> buffer;
		ssize_t write_bytes = write(sock, buffer, sizeof(buffer));
		if(write_bytes == -1)
			std::cout << "write error\n";
		memset(&buffer, 0, sizeof(buffer));
		ssize_t read_bytes = read(sock, buffer, sizeof(buffer));		

	}
}
