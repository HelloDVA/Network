#include<iostream>
#include<unistd.h>
#include<string.h>
#include<functional>

#include"src/utils.h"
#include"src/Socket.h"
#include"src/Buffer.h"
#include"src/ThreadPool.h"


void oneClient(int msgs, int wait)
{
    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    Socket *serv_socket = new Socket();
    serv_socket -> connect_s(serv_addr);
    int serv_fd = serv_socket -> getFd();

    Buffer *readBuffer = new Buffer();
    Buffer *writeBuffer = new Buffer();
    sleep(wait);
    int count = 0;
    const char *message = "I am client";
    writeBuffer -> append(message, sizeof(message));
    while(count < msgs)
    {
       ssize_t write_bytes = write(serv_fd, writeBuffer -> c_str(), writeBuffer -> size());            
       if (write_bytes == -1)
       {
           std::cout << "server is disconnected\n";
           break;
       }
       char temp_buff[1024];
       while (true)
       {
           bzero(&temp_buff, sizeof(temp_buff));
           int read_state = read(serv_fd, temp_buff, 1024);
           if (read_state > 0)
               readBuffer -> append(temp_buff, sizeof(temp_buff));
           if (read_state == 0)
            {
               std::cout << "read from server over\n";
               exit(EXIT_SUCCESS);
            }
       }
       std::cout << readBuffer -> c_str() << std::endl;
       readBuffer -> clean();
    }
    delete readBuffer;
    delete writeBuffer;
    delete serv_addr;
    delete serv_socket;
}

int main(int argc, char *args[])
{
    int thread_number = 0;
    int msgs = 0;
    int wait = 0;
    int o;
    const char  *optstr = "t:m:w:";

    while((o = getopt(argc, args, optstr)) != -1)
    {
        switch(o)
        {
            case 't':
                thread_number = std::stoi(optarg);
                break;
            case 'm':
                msgs = std::stoi(optarg);
                break;
            case 'w':
                wait = std::stoi(optarg);
                break;
            case '?':
                std::cout << "error: " <<  opterr << std::endl;
                break;
        }
    }

    ThreadPool *pool = new ThreadPool(thread_number);
    std::function<void()> func = std::bind(oneClient, msgs, wait);
    for(int i = 0; i < thread_number; i ++)
    {
        pool -> add(func);
    }
    delete pool;
    return 0;
}
