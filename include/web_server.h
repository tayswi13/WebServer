// 类WebServer的文件头
#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <cassert>

class WebServer {
public:
    WebServer();
    ~WebServer();

    void init(int port);
    void event_listen();    // 进行监听
private:
    int m_port; // 监听端口
    int m_listenfd; // 监听fd
};

#endif

