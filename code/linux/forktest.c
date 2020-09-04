#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/types.h>


int main(void)
{
    int cnt = 0;
    pid_t child;
    if ((child = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        while (cnt < 10)
        {
            if (0 == child)
            {
                printf("in child, cnt = %d\n", cnt++);
                printf("pid is %d\n", getpid());
                printf("ppid is %d\n", getppid());
            }
            else
            {
                printf("in parent, cnt = %d\n", cnt++);
                printf("child pid is %d\n", child);
                printf("pid is %d\n", getpid());
            }
        }
    }
    exit(EXIT_SUCCESS);
}