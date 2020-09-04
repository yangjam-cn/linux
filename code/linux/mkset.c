#include <signal.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <stdlib.h>

void err_quit(const char *);

int main(void)
{
    sigset_t newSet;

    if ((sigemptyset(&newSet)) < 0)
        err_quit("sigemptyset");
    if ((sigaddset(&newSet, SIGCHLD)) < 0)
        err_quit("sigaddset");
    if (sigismember(&newSet, SIGCHLD))
        puts("SIGCHLD is in signal mask");
    else
        puts("SIGCHLD not in signal mask");
    if (sigdelset(&newSet, SIGCHLD) < 0)
        err_quit("sigdelaet");
    if (sigismember(&newSet, SIGCHLD))
        puts("SIGCHLD is in signal mask");
    else
        puts("SIGCHLD not in signal mask");
    exit(EXIT_SUCCESS);
}

void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}