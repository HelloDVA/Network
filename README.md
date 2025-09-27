### 1、架构设计

主从Reactor架构、epoll IO复用、线程池、异步日志。

### 2、核心封装

IO复用相关：Channel	EpollPoller	

网络处理相关：sockets	InetAddress	Acceptor	Connection

架构相关：EventLoop	EventLoopThread		EventLoopThreadPoll

工具：AsyncLogger	Buffer	

### 3、线程运行

##### 主线程

1.创建线程池。

2.利用主Reactor，创建Acceptor，负责处理连接。

##### 线程池：

1.每个线程绑定一个Reactor

2.处理当前Reactor中Connection的事件。

##### 日志线程：

异步日志。

![线程运行](https://github.com/HelloDVA/Network/blob/main/Thread%20flow.png)

#### 4、并发测试（1000连接 30s）

##### wrk测试

![wrk测试](https://github.com/HelloDVA/Network/blob/main/1000-30s-wrk.png)

##### 内存泄漏测试

![内存泄漏测试](https://github.com/HelloDVA/Network/blob/main/1000-30s-valgrind.png)

##### 项目瓶颈测试

![项目瓶颈测试](https://github.com/HelloDVA/Network/blob/main/1000-30s-flame.svg)
