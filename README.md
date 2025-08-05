# Network

### tcpserver

1、利用base loop，创建acceptor。

2、利用base loop，创建线程池。

3、Connection建立，回调函数。

4、Connection关闭，回调函数。

5、Connection业务回调函数。

6、关闭所有connection。

### acceptor

1、创建服务器addr，创建非阻塞socket。

2、利用base loop，bind、listen，服务器socket。

3、创建channel，注册读事件，HandleRead处理，接受连接，调用tcpserver：：回调函数。

4、使用channel，关闭事件，申请从epoll中移除自己。

5、关闭socket。

### connection

1、利用thread loop，acceptor提供的连接sockfd，创建channel。

2、注册Read，Write，Close，Error事件，并建立对应的处理函数。

3、配备读写缓冲区，读取，发送数据。

4、根据不同事件处理，调用不同的tcpserver：：回调函数。

6、服务器配备主动操作：发送数据，断开连接。

### 主体架构

![主体架构](https://github.com/HelloDVA/Network/blob/main/network.png)

