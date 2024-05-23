#include "web_server.h"

WebServer::WebServer() {

}

WebServer::~WebServer() {
    close(m_listenfd);
    close(m_epollfd);
    close(m_pipefd[0]);
    close(m_pipefd[1]);
}

void WebServer::init(int port) {
    m_port = port;
}

void WebServer::event_listen() {
    int ret; // 检查返回值
    struct sockaddr_in addr;    // 监听地址结构

    // 初始化监听描述符
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(m_listenfd, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret == 0);

    ret = listen(m_listenfd, 20);
    assert(ret == 0);

    // epoll部分
    struct epoll_event ev;  // 用于设置lfd的属性
    m_epollfd = epoll_create(1024);
    assert(m_epollfd != -1);

    ev.events = EPOLLIN;
    ev.data.fd = m_listenfd;
    ret = epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_listenfd, &ev); // 将lfd挂上监听树
    assert(ret != -1);

    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, m_pipefd);    // 同一台机器上的两个进程之间建立全双工的通信管道
    assert(ret != -1);

}

void WebServer::event_loop() {
    bool stop_server = false;

    while(!stop_server) {
        int number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        assert(number != -1);

        for(int i = 0; i < number; i++) {
            int sockfd = events[i].data.fd;

            // 对处于就绪状态的fd进行处理
            if(sockfd == m_listenfd) {  
                // 有客户端的连接请求
                bool flag  = deal_with_conn();
                if(flag == false)
                    continue;
            }
            else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                // 服务器端关闭连接
            }
            else if((sockfd == m_pipefd[0]) && (events[i].events & EPOLLIN)) {
                // 处理信号
                bool flag = deal_with_signal();
                if(flag == false)
                    break;  // 报错一下
            }
            else if(events[i].events & EPOLLIN) {
                // 处理客户端发来的数据
                deal_with_read(sockfd);
            }
            else if(events[i].events & EPOLLOUT) {
                // 向客户端发送数据
                deal_with_write(sockfd);
            }
        }
    }
}

bool WebServer::deal_with_conn() {

}

bool WebServer::deal_with_signal() {

}

void WebServer::deal_with_read(int sockfd) {

}

void WebServer::deal_with_write(int sockfd) {

}