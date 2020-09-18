#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*输出错误信息并退出程序*/
void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}


int main()
{
    int sDec, tDec;              /*sDec:监听套接字描述符；tDec:传输套接字描述符*/
    sockaddr_in sAddr, tAddr;    /*套接字协议地址*/
    socklen_t   sInLen;          /*协议长度*/
    unsigned short portNum = 10051;   /*端口号*/
    // char ip[] = "192.168.0.100";

    printf("I am server, welcome!\n");

    /* 创建套接字 */
    if ((sDec = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        err_quit("socket");
 
    /* 设置ip地址允许立即重用 */
    int on = 1;
    setsockopt(sDec, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    
    /* 绑定ip和端口 */
    bzero(&sAddr, sizeof(sAddr));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sAddr.sin_port = htons(portNum);
    if (bind(sDec, (sockaddr *)(&sAddr), sizeof(sockaddr)) == -1)
        err_quit("bind");

    /* 设置监听模式 */
    if (listen(sDec, 5) == -1)
        err_quit("listen");
    
    /* 等待连接 */
    while (1)
    {
        /* 接受连接 */
        sInLen = sizeof(sockaddr_in);
        if ((tDec = accept(sDec, (sockaddr *)&sAddr, &sInLen)) == -1)
            err_quit("accept");
        printf("accept ok!\n");
        printf("server start get connect from ip = %s, port = %d\n",
            inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));
        
        /* 写数据 */
        if (write(tDec, "welcome, client!\n", 32) == -1)
            err_quit("write");
        
        /* 关闭套接字 */
        close(tDec);

        puts("continue to listen?(y/n)");
        char ch[2];
        scanf("%s", ch);
        if (ch[0] != 'y')
            break;
    }

    /* 关闭监听套接字 */
    close(sDec);

    return 0;
}