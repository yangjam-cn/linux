#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    pid_t child;
    int status, retval;

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (0 == child)
    {
        printf("child pid = %d\n", getpid());
        sleep(100);
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (waitpid(child, &status, WNOHANG) == 0)
        {
            retval = kill(child, SIGKILL);
            if (retval != 0)
            {
                puts("kill failed!\n");
                perror("kill");
                waitpid(child, &status, 0);
            }
            else
            {
                printf("%d killed!\n", child);
            }
        }
    }
    exit(EXIT_SUCCESS); 
}