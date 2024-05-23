// 类WebServer的文件头
#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cassert>
#include <sys/epoll.h>
#include <unistd.h>

const int MAX_EVENT_NUMBER = 10000; // 最大事件数

class WebServer {
public:
    WebServer();
    ~WebServer();

    void init(int port);    // 初始化
    void event_listen();    // 进行监听
    void event_loop();      // 启动服务器
    bool deal_with_conn();    // 处理客户端连接请求
    bool deal_with_signal();    // 处理信号
    void deal_with_read(int sockfd);    // 处理读事件
    void deal_with_write(int sockfd);    // 处理写事件
private:
    int m_port; // 监听端口
    int m_listenfd; // 监听fd
    int m_epollfd;  // epoll监听树fd
    int m_pipefd[2];    // 一对相互连接的套接字描述符
    struct epoll_event events[MAX_EVENT_NUMBER];    // 作为epoll_wait的传出参数
};

#endif

