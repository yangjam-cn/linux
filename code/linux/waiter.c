#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
    pid_t child;
    int status;

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0)
    {
        printf("in child:\n");
        printf("child pid = %d\n", getpid());
        printf("parent ppid = %d\n", getppid());
    }
    else
    {
        /*WNOHANG子进程没有退出时立即返回*/
        /*EUNTRACED若存在没有报告状态的进程而返回*/
        waitpid(child, &status, WUNTRACED);    /*等待子进程退出*/
        printf("in parent:\n");
        printf("this pid = %d\n", getpid());
        printf("parent ppid = %d\n", getppid());
        printf("child exited with %d\n", status);
    }
    exit(EXIT_SUCCESS);
}