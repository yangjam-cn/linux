#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    pid_t child;
    int errRet;

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (0 == child)
    {
        sleep(30);
    }
    else
    {
        printf("sending SIGCHLD to %d\n", child);
        errRet = kill(child, SIGCHLD);
        if (errRet < 0)
            perror("kill:SIGCHLD");
        else
            printf("%d still alive, retval = %d\n", child, errRet);
        
        printf("killing %d\n", child);
        if ((errRet = kill(child, SIGKILL)) < 0)
            perror("kill:SIGKILL");
        printf("retval = %d\n", errRet);
        /*若子进程先死掉，父进程必须接收它的退出状态以避免它变成僵进程*/
        waitpid(child, NULL, 0);
    }
    exit(EXIT_SUCCESS);
}