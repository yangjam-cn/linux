#include <sys/types.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int cDec;
    sockaddr_in cAddr;
    socklen_t cInLen;
    char ip[] = "192.168.0.100";
    unsigned short portNum = 10051;

    char buf[1024] = {__FILE__};
    int  recBytes;

    /* 创建套接字 */
    if ((cDec = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        err_quit("socket");

    /* 设置服务器ip和端口 */
    bzero(&cAddr, sizeof(cAddr));
    cAddr.sin_family = AF_INET;
    cAddr.sin_addr.s_addr = inet_addr(ip);
    cAddr.sin_port = htons(portNum);
    /* 请求连接 */
    if (connect(cDec, (sockaddr *)&cAddr, sizeof(sockaddr)) == -1)
        err_quit("connect");
    
    /* 读取数据 */
    if ((recBytes = read(cDec, buf, 1024)) == -1)
        err_quit("read");
    
    buf[recBytes] = '\0';
    printf("%s\n", buf);
    getchar();

    /* 关闭套接字 */
    close(cDec);

    return 0;
}