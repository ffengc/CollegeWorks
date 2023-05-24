

#include <iostream>
#include "HttpServer.hpp"
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Usage.hpp"
#include "ulity.hpp"
#include <fstream>


/* 一般http都要有自己的web根目录 */
#define ROOT "./wwwroot"
/* 如果客户端只请求了一个/ ，一般返回默认首页 */
#define HOME_PAGE "index.html"

void HandlerHttpRequest(int sockfd)
{
    char buffer[10240];

    // while (1)
    // {
    // 1. 读取请求
    ssize_t s = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    // std::cerr << s << std::endl;
    if (s > 0)
    {
        buffer[s] = 0;
        std::cerr << buffer << "-----------\n"
                  << std::endl;
    }
    // else continue;
    /* 现在我们要来分析http的请求报文 */
    std::vector<std::string> vline;
    Util::cutString(buffer, "\r\n", &vline);
    // std::cerr << "HandlerHttpRequest()" << std::endl;
    // std::cerr << "vblock:   " << vline[0] << std::endl;
#define debug 0
#if debug
    // for debug -- 看看cutString有没有把http的报文每一行切出来
    for (auto &iter : v)
    {
        std::cout << iter << "\n"
                  << std::endl;
    }
#endif
    std::vector<std::string> vblock;
    Util::cutString(vline[0], " ", &vblock); // 因为我们要提取到底这个请求要什么资源
    /* http的报文 第一行就告诉了我们到底这个请求需要什么资源 所以把第一行再分一下就行 */
    std::string file = vblock[1]; // 按照报文的格式，第一行第二个字符串，就是资源路径
    std::string target = ROOT;
    if (file == "/")
        file = "/index.html";
    target += file;

    std::string content;
    std::ifstream in(target);
    if (in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            content += line;
        }
        in.close();
    }
    // 2. 构建一个Http构建一个响应
    std::string HttpResponse;
    if (content.empty())
    {
        HttpResponse = "HTTP/1.1 200 OK\r\n";
        std::string content_404;
        std::string target_temp;
        target_temp += "./wwwroot/error/404.html";
        std::ifstream in(target_temp);
        if (in.is_open())
        {
            std::string line;
            while (std::getline(in, line))
            {
                content_404 += line;
            }
            in.close();
        }
        content = content_404;
    }

    else
        HttpResponse = "HTTP/1.1 200 OK\r\n";
    assert(!content.empty());
    HttpResponse += "\r\n";
    HttpResponse += content;
    send(sockfd, HttpResponse.c_str(), HttpResponse.size(), 0);
    // }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::unique_ptr<HttpServer> httpserver(new HttpServer(atoi(argv[1]), HandlerHttpRequest));
    httpserver->Start();
    return 0;
}
