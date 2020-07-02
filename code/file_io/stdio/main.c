/*
 * @Author: youngjam
 * @Date: 2020-07-01 18:56:02
 * @LastEditTime: 2020-07-01 19:11:17
 * @Description: 文件的标准库操作，（野火教程代码）
 * @logs: 
 */ 
#include <stdio.h>
#include <string.h>

/* 要写入的字符串 */
const char buf[] = "filesystem_test:Hello world!\n";
FILE *fp;    /* 文件描述符 */
char str[100];

int main(void)
{
    /* 创建一个文件 */
    fp = fopen("filesystem_test.txt", "w+");
    /* 正常返回文件指针，异常返回NULL */
    if (NULL == fp)
    {
        printf("Fail to open file\n");
        return 0;
    }

    /* 
     * 将buf的内容写入文件
     * 每次写入一个字节，总长度有strlen给出
     */
    fwrite(buf, 1, strlen(buf), fp);
    fwrite("Embedfire\n", 1, strlen("Embedfile\n"), fp);

    /* 把缓冲区的数据立即写入文件 */
    fflush(fp);

    /* 此时文件位置指针位于文件的结尾处，使用fseek函数使文件指针返回文件头 */
    fseek(fp, 0, SEEK_SET);

    /*
     * 从文件中读取内容到str中
     * 每次读取100个字节，读取一次 
     */
    fread(str, 100, 1, fp);

    printf("File content:\n%s \n", str);

    fclose(fp);
    
    return 0;
}