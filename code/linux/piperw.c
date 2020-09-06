#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * 每个进程对管道的写入数据必须小与PIPE_BUF个字节，以确保原子写操作
 * 防止多个进程同时写入数据时数据相混合
 */
#define BUFSZ PIPE_BUF

void err_quit(const char *msg)
{
    perror(msg);
    printf("\n%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}


int main(int argc, char* argv[])
{
    int  fd[2];
    int  fdIn;
    char buf[BUFSZ];
    int  pid, len;

    /*创建管道*/
    if (pipe(fd) < 0)
        err_quit("pipe");
    
    /*创建子进程*/
    if ((pid = fork()) < 0)
        err_quit("fork");
    
    /*子进程*/
    if (0 == pid)
    {
        close(fd[1]);    /*关闭写通道*/
        /*从读出端读取数据到buf，然后输出到标准输出*/
        while ((len = read(fd[0], buf, BUFSZ)) > 0)
        {
            write(STDOUT_FILENO, buf, len);
        }
        close(fd[0]);
    }
    /*父进程*/
    else
    {
        close(fd[0]);    /*关闭读通道*/
        /*以只读打开指定文件*/
        if ((fdIn = open(argv[1], O_RDONLY)) < 0)
        {
            perror("open");
            write(fd[1], "123\n", 4);
        }
        else
        {
            /*将打开文件的数据读入到buf，然后输出到管道写入端*/
            while ((len = read(fdIn, buf, BUFSZ)) > 0)
            {
                write(fd[1], buf, len);
            }
            close(fdIn);
        }
        close(fd[1]);
    }
    /*文件数据写入管道后，等待子进程结束后，返回父进程*/
    waitpid(pid, NULL, 0);

    exit(EXIT_FAILURE);
}
