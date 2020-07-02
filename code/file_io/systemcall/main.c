/*
 * @Author: youngjam
 * @Date: 2020-07-01 21:21:01
 * @LastEditTime: 2020-07-01 21:43:16
 * @Description: 
 * @logs: 
 */ 
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int fd;
char str[100];

int main(void)
{
    fd = open("testscript.sh", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd < 0)
    {
        printf("Fail to Open file\n");
        return 0;
    }
    write(fd, "pwd\n", strlen("pwd\n"));
    write(fd, "ls\n", strlen("ls\n"));
    lseek(fd, 0, SEEK_SET);
    read(fd, str, 100);
    printf("File content:\n%s \n", str);
    close(fd);
    return 0;
}