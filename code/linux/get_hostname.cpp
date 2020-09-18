#include <iostream>
#include <cstring>
#include <unistd.h>

int main(void)
{
    char hostname[30];
    int flag = 0;

    memset(hostname, 0x00, sizeof(hostname));

    if ((flag = gethostname(hostname, sizeof(hostname))) < 0)
    {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }
    printf("hostname = %s\n", hostname);
    exit(EXIT_SUCCESS);
}