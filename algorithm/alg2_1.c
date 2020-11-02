/**
 * @copyright: Copyright (c) 2020 yungjam All rights reserved.
 * @filename: alg2_1.c
 * @description: 顺序表实例
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.11.02
 * @history:
 */
#include <stdio.h>
#include <string.h>

#define MAXLEN 100    /* 顺序表最大长度 */

typedef struct
{
    char key[10];
    char name[20];
    int    age;
}DATA;

typedef struct
{
    DATA ListData[MAXLEN + 1];
    int       ListLen;
}SLType;

/**
 * Description: 初始化顺序表
 */
void SLInit(SLType *SL)
{
    SL->ListLen = 0;
}

/**
 * Description: 返回顺序表长度
 */
int SLLength(SLType *SL)
{
    return (SL->ListLen);
}

/**
 * Description: 在顺序表序号为n的地方插入data
 */
int SLInsert(SLType *SL, int n, DATA data)
{
    int i;
    if (SL->ListLen >= MAXLEN)
    {
        printf("顺序表已满，不能插入结点！\n");
        return 0;
    }

    if (n < 1 || n > (SL->ListLen - 1))
    {
        printf("插入元素序号错误，不能插入元素！\n");
        return 0;
    }

    for (i = SL->ListLen; i >= n; --i)
    {
        SL->ListData[i + 1] = SL->ListData[i];
    }    /* end while(i == n - 1) */
    SL->ListData[n] = data;
    ++SL->ListLen;

    return 1;
}

/**
 * Description: 在顺序表尾部加入data
 */
int SLAdd(SLType *SL, DATA data)
{
    if (SL->ListLen >= MAXLEN)
    {
        printf("顺序表已满，不能再添加结点！\n");
        return 0;
    }
    SL->ListData[++SL->ListLen] = data;
    return 1;
}

/**
 * Description: 删除顺序表中序号为n的项
 */
int SLDelete(SLType *SL, int n)
{
    int i;

    if (n < 1 || n > (SL->ListLen - 1))
    {
        printf("删除结点序号错误，不能删除结点！\n");
        return 0;
    }

    /* 删除尾部的项 */
    if (n == SL->ListLen)
    {
        --SL->ListLen;
        return 1;
    }

    for (i = n; i < SL->ListLen; ++i)
    {
        SL->ListData[i] = SL->ListData[i + 1];
    }    /* end while(i == ListLen) */
    --SL->ListLen;
    return 1;
}

/**
 * Description: 返回顺序表中序号为n的项的指针
 */
DATA* SLFindByNum(SLType *SL, int n)
{
    if (n < 1 || n > SL->ListLen)
    {
        printf("结点序号错误，不能返回结点！\n");
        return NULL;
    }

    return &(SL->ListData[n]);
}

/**
 * Description: 查找顺序表中关键字为key的项并返回在顺序表中的序号
 */
int SLFindByCont(SLType *SL, char *key)
{
    int i;
    for (i = 1; i <= SL->ListLen; ++i)
    {
        if (strcmp(SL->ListData[i].key, key) == 0)
        {
            return i;
        }
    }    /* end while(i > SL->ListLen || key == SL->ListData[i]) */
    return 0;
}

/**
 * Description: 按序打印顺序表中的项到终端
*/
int SLAll(SLType *SL)
{
    int i;
    for (i = 1; i <= SL->ListLen; ++i)
    {
        printf("(%s, %s, %d)\n", SL->ListData[i].key, SL->ListData[i].name, SL->ListData[i].age);
    }    /* end while(i > SL->ListLen) */
    return 0;
}

int main(void)
{
    int i;
    SLType SL;
    DATA   data;
    DATA *pdata;
    char      key[10];

    printf("顺序表操作演示！\n");

    SLInit(&SL);
    printf("顺序表初始化完成！\n");

    do
    {
        printf("输入添加的结点(学号 姓名 年龄)：");
        fflush(stdin);
        scanf("%s %s %d", data.key, data.name, &data.age);
        if (data.age > 0)
        {
            if (SLAdd(&SL, data) == 0)
            {
                break;
            }
        }
        else
        {
            break;
        }
    } while (1);

    printf("\n顺序表中的结点顺序为：\n");
    SLAll(&SL);

    fflush(stdin);
    printf("\n要取出的结点的序号：");
    scanf("%d", &i);
    pdata = SLFindByNum(&SL, i);
    if (pdata != NULL)
    {
        printf("第%d个结点为：(%s %s %d)\n", i, pdata->key, pdata->name, pdata->age);
    }

    SLDelete(&SL, i);
    printf("第%d个结点已删除.\n", i);

    fflush(stdin);
    printf("\n要查找结点的关键字：");
    scanf("%s", key);
    i = SLFindByCont(&SL, key);
    pdata = SLFindByNum(&SL, i);
    if (pdata != NULL)
    {
        printf("第%d个结点为：(%s %s %d)\n", i, pdata->key, pdata->name, pdata->age);
    }
    getchar();
    return 0;
}
