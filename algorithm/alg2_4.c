/**
 * @copyright: Copyright (c) 2020 yungjam All rights reserved.
 * @filename: alg2_4.c
 * @description: 队列的实例
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.11.02
 * @history:
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define QUEUELEN 15

typedef struct
{
    char name[10];
    int    age;
}Data;
typedef struct
{
    Data data[QUEUELEN];
    int head;
    int tail;
}SQType;

SQType *init()
{
    SQType *q;

    if ((q = (SQType *)malloc(sizeof(SQType))) != NULL)
    {
        q->head = 0;
        q->tail = 0;
        return q;
    }
    else
    {
        return NULL;
    }
}

int is_empty(SQType *q)
{
    return (q->head == q->tail);
}

int is_full(SQType *q)
{
    return (q->tail == QUEUELEN);
}

void clear(SQType *q)
{
    q->head = q->tail = 0;
}

void freeSQT(SQType *q)
{
    if (q != NULL)
    {
        free(q);
    }
}

int enqueue(SQType *q, Data data)
{
    if (is_full(q))
    {
        printf("队列已满！操作失败！\n");
        return 0;
    }
    else
    {
        q->data[q->tail++] = data;
        return 1;
    }
}

Data* dequeue(SQType *q)
{
    if (is_empty(q))
    {
        printf("队列为空！操作失败！\n");
        exit(0);
    }
    else
    {
        return &(q->data[q->head++]);
    }
}

Data *peekSQT(SQType *q)
{
    if (is_empty(q))
    {
        printf("空队列！\n");
        exit(0);
    }
    else
    {
        return &(q->data[q->head]);
    }
}

int length(SQType *q)
{
    return (q->tail - q->head);
}

int main(void)
{
    SQType *q;
    Data data, *pdata;

    q = init();
    printf("入队操作：\n");
    printf("输入姓名 年龄进行入队操作：\n");
    do
    {
        fflush(stdin);
        scanf("%s %d", data.name, &data.age);
        if (strcmp(data.name, "0") == 0)
        {
            break;
        }
        else
        {
            enqueue(q, data);
        }
    }while(1);

    do
    {
        printf("出队列操作：按任意键进行出栈操作：\n");
        getchar();
        pdata = dequeue(q);
        printf("出队列的数据是(%s %d)\n", pdata->name, pdata->age);
        if (is_empty(q))
        {
            break;
        }
    }while(1);

    freeSQT(q);
    return 0;
}
