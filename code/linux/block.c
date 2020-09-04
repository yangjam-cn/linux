#include <sys/types.h>
#include <sys/unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    sigset_t newSet;

    if ((sigemptyset(&newSet)) < 0)
        err_quit("sigemptyset");
    if ((sigaddset(&newSet, SIGALRM)) < 0)
        err_quit("sigaddset:SIGALRM");
    if ((sigaddset(&newSet, SIGTERM)) < 0)
        err_quit("sigaddset:SIGTERM");
    
    if ((sigprocmask(SIG_BLOCK, &newSet, NULL)) < 0)
        err_quit("sigprocmask");
    pause();
    exit(EXIT_SUCCESS);
}