#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int fd;
    FILE *fp;
    /*临时文件名*/
    char template[] = "/home/youngjam/imx6/workdir/code/linux/test-XXXXXX";
    char str[80];
    int size = strlen(template);         /*临时文件绝对路径长度*/
    // fd = mkstemp(template);
    if ((fd = mkstemp(template)) < 0)    /*创建临时文件*/
    {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }
    else 
        printf("fd = %d\n", fd);
    
    write(fd, template, size);    /*将临时文件民写入临时文件*/
    close(fd);      /*关闭临时文件*/

    fp = fopen(template, "r");    /*调用c库函数以只读方式打开临时文件*/
    fscanf(fp, "%s", str);        /*从临时文件读取字符串传给str*/
    printf("%s\n", str);          /*将str输出到标准输出流*/
    fclose(fp);     /*关闭临时文件*/

    sleep(10);      /*等待10s*/
    remove(str);    /*删除临时文件*/

    exit(EXIT_SUCCESS);
}