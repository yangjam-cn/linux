#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <errno.h>

int main(void)
{
    int sfp;
    struct sockaddr_in sAddr;
    socklen_t sinSize;
    unsigned short portNum = 10051;
    struct sockaddr_in serv;
    socklen_t servLen = sizeof(serv);

    /*以IPv4协议通过TCP来创建套接字*/
    sfp = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfp)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("socket ok!\n");
    printf("ip = %s, port = %d\n", inet_ntoa(serv.sin_addr),
        ntohs(serv.sin_port));
    
    printf("pid = %d\n", getpid());

    /*允许套接字地址立即重用*/
    int on = 1;
    setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&sAddr, sizeof(struct sockaddr_in));    /*用0初始化地址*/
    sAddr.sin_family = AF_INET;    /*设置为IPv4*/
    /*将网络主机ip转为二进制数据*/
    sAddr.sin_addr.s_addr = inet_addr("192.168.0.101");
    sAddr.sin_port = htons(portNum);    /*设置端口*/
    if (-1 == bind(sfp, (struct sockaddr *)(&sAddr), 
        sizeof(struct sockaddr)))       /*将地址与套接字绑定*/
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind ok!\n");
    /*获取套接字地址*/
    getsockname(sfp, (struct sockaddr *)(&serv), &servLen);
    printf("ip = %s, port = %d\n", inet_ntoa(serv.sin_addr), 
        ntohs(serv.sin_port));
    
    exit(EXIT_SUCCESS);
}