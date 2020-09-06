#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define BUFSZ PIPE_BUF

void err_quit(const char *msg)
{
    perror(msg);
    printf("\n%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char *cmd;
    char buf[BUFSZ];
    
    if (argc != 3)
    {
        printf("usage:{cmd\ } {file}\n");
        exit(EXIT_FAILURE);
    }

    cmd = strcat(argv[1], argv[2]);
    printf("%s\n", cmd);

    if ((fp = popen(cmd, "r")) == NULL)
        err_quit("popen");
    
    while (fgets(buf, BUFSZ, fp) != NULL)
        printf("%s", buf);
    
    pclose(fp);
    exit(EXIT_SUCCESS);
}