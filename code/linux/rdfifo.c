#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];
    mode_t mode = 0666;

    /*创建fifo*/
    if (mkfifo("fifo1", mode) < 0)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    /*打开fifo*/
    if ((fd = open("fifo1", O_RDONLY)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while ((len = read(fd, buf, PIPE_BUF - 1)) > 0)
    {
        printf("rdfifo read: %s\n", buf);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}