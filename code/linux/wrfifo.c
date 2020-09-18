#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];
    time_t tp;

    printf("I am %d\n", getpid());

    if ((fd = open("fifo1", O_WRONLY)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        time(&tp);

        len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));

        if (write(fd, buf, len + 1) < 0)
        {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        sleep(3);
    }

    close(fd);
    exit(EXIT_FAILURE);
}
