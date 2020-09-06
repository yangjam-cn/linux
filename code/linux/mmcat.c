#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <errno.h>

void err_quit(const char *msg)
{
    perror(msg);
    printf("\n%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int fdIn;
    char *src;
    struct stat statBuf;
    off_t len;

    /*检查输入参数*/
    if (argc != 2)
    {
        fprintf(stderr, "usage: mmcat {file}\n");
        exit(EXIT_FAILURE);
    }

    /*打开文件*/
    if ((fdIn = open(argv[1], O_RDONLY)) < 0)
        err_quit("open");
    
    /*获取文件状态*/
    if (fstat(fdIn, &statBuf) < 0)
        err_quit("fstat");
    len = statBuf.st_size;    /*获取文件长度*/

    /*将文件映像到内存*/
    if ((src = mmap(0, len, PROT_READ, MAP_SHARED, fdIn, 0)) == (void *)-1)
        err_quit("mmap");
    
    /*将读取到内存的数据输出到屏幕*/
    printf("%s", src);

    close(fdIn);
    munmap(src, len);   /*解除映像区占用*/
    exit(EXIT_SUCCESS);
}