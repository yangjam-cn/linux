#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <sys/unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

void err_quit(const char *msg)
{
    perror(msg);
    cout << strerror(errno) << endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    int  cfp;
    int  recBytes;
    int  sinSize;
    char buffer[1024] = {0};
    sockaddr_in    sAddr, cAddr;
    unsigned short portNum = 10051;
    char ip[] = "192.168.1.119";

    cout << "this is client\n";

    if ((cfp = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        err_quit("socket");
    cout << "socket ok!\n";

    bzero(&sAddr, sizeof(sAddr));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = inet_addr(ip);
    sAddr.sin_port = htons(portNum);
    if (connect(cfp, (sockaddr *)(&sAddr), sizeof(sAddr)) == -1)
        err_quit("connect");
    
    if ((recBytes = read(cfp, buffer, 1024)) == -1)
        err_quit("read");
    cout << "read ok!\n";

    buffer[recBytes] = '\0';
    cout << buffer << endl;

    cout << "enter any key to quit..." << endl;
    getchar();
    close(cfp);

    exit(EXIT_SUCCESS);
}