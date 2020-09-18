/*阻塞套接字，服务器端*/
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>

using namespace std;

void err_quit(const char *msg)
{
    perror(msg);
    cout << strerror(errno) << endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    int            sfp, nfp;        /*sfp,服务器套接字；nfp，连接套接字*/
    sockaddr_in    sAddr, cAddr;    /*套接字网络协议地址*/
    socklen_t      sinSize;         /*套接字协议地址长度*/
    unsigned short portNum = 10051; /*端口号*/

    cout << "Hello, I am server, Welcome to commect me!" << endl;

    /*s1.创建套接字*/
    if ((sfp = socket(AF_INET, SOCK_STREAM, 0))  == -1)
        err_quit("socket.");
    cout << "socket ok!" << endl;

    /*设置允许地址立即重用*/
    int on = 1;
    setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    /*s2.绑定地址*/
    bzero(&sAddr, sizeof(sAddr));
    sAddr.sin_family = AF_INET;    /*设置IPv4协议*/
    sAddr.sin_addr.s_addr = htons(INADDR_ANY);
    sAddr.sin_port = htons(portNum);
    if (bind(sfp, (sockaddr *)&sAddr, sizeof(sockaddr)) == -1)
        err_quit("bind");
    cout << "bink ok!" << endl;

    /*s3.设置监听套接字*/
    if (listen(sfp, 5) == -1)
        err_quit("listen");
    cout << "listen ok!" << endl;

    /*s4.等待客户端连接*/
    while (1)
    {
        sinSize = sizeof(sockaddr_in);

        /*s4-1.接受客户端连接*/
        if ((nfp = accept(sfp, (sockaddr *)(&cAddr), &sinSize)) == -1)
            err_quit("accept");
        cout << "accept ok!\n" 
             << "server start get connect from ip=" 
             << inet_ntoa(cAddr.sin_addr)
             << " port="
             << ntohs(cAddr.sin_port) << endl;

        /*s4-2.项客户端写数据*/
        if (write(nfp, "hello, client, you are welcome!\n", 32) == -1)
            err_quit("write");
        cout << "write ok!" << endl;
        
        /*s4-3.通讯结束关闭连接套接字*/
        close(nfp);

        puts("continue to listen(y/n)?");
        char ch[2];
        scanf("%s",ch);
        if (ch[0] != 'y')
            break;
    }

    cout << "bye" << endl;
    close(sfp);
    exit(EXIT_SUCCESS);
}
