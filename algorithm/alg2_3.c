/**
 * @copyright: Copyright (c) 2020 yungjam All rights reserved.
 * @filename: alg2_3.c
 * @description: 栈结构实例
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.11.02
 * @history:
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 50

typedef struct
{
    char name[10];
    int    age;
}Data;
typedef struct Stack
{
    Data data[MAXLEN + 1];
    int     top;
}StackType;

StackType* initST()
{
    StackType *pST;

    if ((pST = (StackType *)malloc(sizeof(StackType))) != NULL)
    {
        pST->top = 0;
        return pST;
    }
    return NULL;
}

int is_emptyST(StackType *pST)
{
    return (pST->top == 0);
}

int is_fullST(StackType *pST)
{
    return (pST->top == MAXLEN);
}

void clearST(StackType *pST)
{
    pST->top = 0;
}

void freeST(StackType *pST)
{
    if (pST != NULL)
    {
        free(pST);
    }
}

int pushST(StackType *pST, Data data)
{
    if ((pST->top + 1) > MAXLEN)
    {
        printf("栈溢出！\n");
        return 0;
    }
    pST->data[++pST->top] = data;
    return 1;
}

Data popST(StackType *pST)
{
    if (pST->top <= 0)
    {
        printf("栈为空！\n");
        exit(0);
    }
    return (pST->data[pST->top--]);
}

Data peekST(StackType *pST)
{
    if (pST->top <= 0)
    {
        printf("栈为空！\n");
        exit(0);
    }
    return (pST->data[pST->top]);
}

int main(void)
{
    StackType *stack;
    Data data, data1;

    stack = initST();
    printf("入栈操作：\n");
    printf("输入姓名 年龄进行入栈操作：\n");
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
            pushST(stack, data);
        }
    }while(1);

    do
    {
        printf("\n出栈操作：按任意键进行出栈操作：");
        fflush(stdin);
        getchar();
        data1 = popST(stack);
        printf("出栈数据是(%s %d)\n", data1.name, data1.age);
        if (is_emptyST(stack))
        {
            break;
        }
    }while(1);

    freeST(stack);
    return 0;
}
