#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    while (argc > 0)
    {
        printf("%s\n", argv[--argc]);
    }
    printf(" pid = %d\n", getpid());
    printf("ppid = %d\n", getppid());
    printf(" uid = %d\n", getuid());
    return 0;
}