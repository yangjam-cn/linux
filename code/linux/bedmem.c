#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char g_buf[5];

int main(void)
{
    char *buf;
    char *leak;
    char l_buf[5];

    leak = malloc(10);          /*没有回收内存造成内存泄露*/

    buf = malloc(5);

    strcpy(buf, "abcde");       /*越界访问动态分配的堆内存*/
    printf("little : %s\n", buf);
    free(buf);

    buf = malloc(5);
    strcpy(buf, "abcdefgh");    /*越界访问动态分配的对内存*/
    printf("big : %s\n", buf);

    *(buf - 2) = '\0';          /*越下界访问内存缓冲区*/
    printf("underrun: %s\n", buf);

    free(buf);
    free(buf);                  /*同一内存区域释放两次*/

    strcpy(buf, "this will blow up");    /*访问已经被释放的内存*/
    printf("freed: %s\n", buf);

    strcpy(g_buf, "global boom");       /*越界扰乱静态分配的全局内存*/
    printf("global : %s\n", g_buf);

    strcpy(l_buf, "local boom");        /*越界扰乱静态分配的栈内存*/
    printf("local : %s\n", l_buf);

    exit(EXIT_SUCCESS);
}