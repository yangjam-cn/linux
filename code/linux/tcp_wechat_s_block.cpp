/*模拟聊天服务器，与树莓派进行通信*/

#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>

void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
const int MaxLength = 64;

int main(void)
{
    int sfp, nfp;
    sockaddr_in sAddr, nAddr;
    socklen_t inLen;
    unsigned short port = 10051;

    char buf[MaxLength] = {0};
    int recBytes = 0;

    using namespace std;
    cout << "Hello, I am server!" << endl;

    if ((sfp = socket(AF_INET, SOCK_STREAM, 0)) == 1)
        err_quit("socket");

    int on = 1;
    setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&sAddr, sizeof(sAddr));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sAddr.sin_port = htons(port);
    if (bind(sfp, (sockaddr *)&sAddr, sizeof(sockaddr)) == -1)
        err_quit("bind");
    
    if (listen(sfp, 5) == -1)
        err_quit("listen");

    while (1)
    {
        inLen = sizeof(sockaddr_in);
        if ((nfp = accept(sfp, (sockaddr *)&nAddr, &inLen)) == -1)
            err_quit("accept");
        cout << "server start get connect from \nip: "
             << inet_ntoa(nAddr.sin_addr) << " port: " 
             << ntohs(nAddr.sin_port) << endl;

        char flag = '\0';
        cout << "r: recive; w: write; q: quit" << endl;
        while (flag != 'q')
        {
            flag = getchar();
            getchar();
            if (flag == 'r')
            {
                if ((recBytes = read(nfp, buf, MaxLength)) == -1)
                    err_quit("read");
                buf[recBytes] = '\0';
                cout << "recive: " << buf << endl;
                flag = '\0';
            }
            if (flag == 'w')
            {
                cin >> buf;
                if (write(nfp, buf, MaxLength) == -1)
                    err_quit("write");
                flag = '\0';
            }
        }
        close(nfp);

        cout << "continue listen?(y/n)";
        if (getchar() == 'n')
            break;
    }
    close(sfp);
    return 0;
}