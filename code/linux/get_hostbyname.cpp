#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    using namespace std;
    hostent *h;

    if (argc != 2)
    {
        fprintf(stderr, "usage: getip address.\n");
        exit(EXIT_FAILURE);
    }

    if ((h = gethostbyname(argv[1])) == NULL)
    {
        herror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    cout << "host name : " << h->h_name << endl;
    cout << "IP address : " << inet_ntoa(*((in_addr *)h->h_addr_list)) 
        << endl;
    exit(EXIT_SUCCESS);   
}