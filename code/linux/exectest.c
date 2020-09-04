#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// void err_quit(const char *msg);

int main(void)
{
    char *path = {"/home/youngjam/imx6/workdir/code/linux/arg"};
    char *argv[] = {"test", "execv", "execvp", NULL};
    char *envp[] = {"PATH=~/imx6/wordir/code/linux", "USR=root", NULL};
    char *file = {"arg"};
    int retval;

    /*path没有找到，返回-1*/
    // retval = execl(path, "execl", "test", NULL);
    // retval = execlp(path,"test", "execlp", NULL);
    // retval = execv(path, argv);
    printf("old pid = %d\n", getpid());
    printf("   ppid = %d\n", getppid());
    printf("    uid = %d\n", getuid());
    // retval = execve(file, argv, envp);
    retval = execv(file, argv);
    printf("Couldn't print the msg! the retval = %d\n", retval);
    exit(EXIT_FAILURE);
}

// void err_quit(const char *msg)
// {
//     perror(msg);
//     exit(EXIT_FAILURE);
// }