#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    sigset_t set, pendSet;
    struct sigaction action;

    sigemptyset(&set);

    sigaddset(&set, SIGTERM);

    sigprocmask(SIG_BLOCK, &set, NULL);

    kill(getpid(), SIGTERM);

    sigpending(&pendSet);

    if (sigismember(&pendSet, SIGTERM))
    {
        sigemptyset(&action.sa_mask);
        action.sa_handler = SIG_IGN;     /*解除阻塞后，SIGTERM不能正常递送*/
        sigaction(SIGTERM, &action, NULL);
    }
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    exit(EXIT_SUCCESS);
}