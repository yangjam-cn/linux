#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>

#define BUFSIZE 80

void err_quit(const char *msg);

int main(void)
{
    int fds[2];
    char buf[BUFSIZE];
    int i, rc, maxFd;
    fd_set watchSet;
    fd_set inSet;

    if ((fds[0] = open("pipe1", O_RDONLY | O_NONBLOCK)) < 0)
    {
        err_quit("open pipe1");
    }
    if ((fds[1] = open("pipe2", O_RDONLY | O_NONBLOCK)) < 0)
    {
        err_quit("open pipe2");
    }

    FD_ZERO(&watchSet);
    FD_SET(fds[0], &watchSet);
    FD_SET(fds[1], &watchSet);

    maxFd = fds[0] > fds[1] ? fds[0] : fds[1];

    while (FD_ISSET(fds[0], &watchSet) || FD_ISSET(fds[1], &watchSet))
    {
        inSet = watchSet;
        if (select(maxFd + 1, &inSet, NULL, NULL, NULL) < 0)
        {
            err_quit("select");
        }
        for (i = 0; i < 2; ++i)
        {
            rc = read(fds[i], buf, BUFSIZE - 1);
            if (rc > 0)
            {
                buf[rc] = '\0';
                printf("read: %s", buf);
            }
            else if (0 == rc)
            {
                close(fds[i]);
                FD_CLR(fds[i], &watchSet);
            }
            else
            {
                err_quit("read");
            }
        }
    }
    exit(EXIT_SUCCESS);
}

void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}