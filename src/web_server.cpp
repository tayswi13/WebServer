#include "web_server.h"

WebServer::WebServer() {

}

WebServer::~WebServer() {

}

void WebServer::init(int port) {
    m_port = port;
}

void WebServer::event_listen() {
    int ret; // 检查返回值
    struct sockaddr_in addr;    // 监听地址结构

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
}