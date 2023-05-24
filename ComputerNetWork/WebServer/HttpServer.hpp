
#ifndef __Yufc_HttpServer
#define __Yufc_HttpServer

#include "Sock.hpp"
#include <functional>
#include "MyThreadPool/threadPool.hpp"

using func_t = std::function<void(int)>;

struct Task
{
public:
    func_t func__;
    int sock__;

public:
    Task() {}
    Task(func_t func, int sock) : func__(func), sock__(sock) {}
    void operator()()
    {
        func__(sock__);
    }
};

class HttpServer
{
private:
    int __listen_sock;
    uint16_t __port;
    Sock __sock;
    func_t __func;
    yufc_thread_pool::ThreadPool<Task> *__thread_pool = yufc_thread_pool::ThreadPool<Task>::getThreadPool();
public:
    HttpServer(const uint16_t &port, func_t func) : __port(port), __func(func)
    {
        __listen_sock = __sock.Socket();
        __sock.Bind(__listen_sock, __port);
        __sock.Listen(__listen_sock);
    }
    ~HttpServer()
    {
        if (__listen_sock >= 0)
            close(__listen_sock);
    }
    void Start()
    {
        signal(SIGCHLD, SIG_IGN); // 忽略进程退出
        __thread_pool->run();
        for (;;)
        {
            std::string client_ip;
            uint16_t client_port = 0;
            int sockfd = __sock.Accept(__listen_sock, &client_ip, &client_port);
            if (sockfd < 0)
                continue;
            // if(fork() == 0)
            // {
            //     close(__listen_sock);
            //     __func(sockfd);
            //     exit(0);
            // }
            Task t(__func, sockfd);
            __thread_pool->pushTask(t);
            //close(sockfd);
        }
    }
};

// HttpServer::__thread_pool = yufc_thread_pool::ThreadPool<func_t>::getThreadPool();

#endif
