/**
 * @copyright: Copyright (c) 2020 yungjam All rights reserved.
 * @filename: alg2_2.c
 * @description: 链表操作实例
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.11.02
 * @history:
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct
{
    char key[10];
    char name[20];
    int    age;
}Data;
typedef struct Node
{
    Data nodeData;
    struct Node *next;
}CLType;


/**
 * Description: 在链表尾部添加项
 */
CLType* add_endCL(CLType *head, Data nodeData)
{
    CLType *node, *hTemp;

    if ((node = (CLType *)malloc(sizeof(CLType))) == NULL)
    {
        printf("申请内存失败！\n");
        return NULL;
    }    /* end if(node == null) */
    else
    {
        node->nodeData = nodeData;
        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            return head;
        }

        hTemp = head;
        while (hTemp->next != NULL)
        {
            hTemp = hTemp->next;
        }    /* end while(hTemp->next == null) */
        hTemp->next = node;
        return head;
    }    /* end if(node != null) */
}    /* end add_endCL */


/**
 * Description: 在链表头部添加项
 */
CLType* add_firstCL(CLType *head, Data nodeData)
{
    CLType *node;

    if ((node = (CLType *)malloc(sizeof(CLType))) == NULL)
    {
        printf("申请内存失败！\n");
        return NULL;
    }    /* end if(node == null) */
    else
    {
        node->nodeData = nodeData;
        node->next = head;
        return node;
    }    /* end if(node != null) */
}     /* end add_firstCL */


/**
 * Description: 在链表中查找关键字为key的项，并返回其结点指针
 */
CLType* find_nodeCL(CLType *head, char *key)
{
    CLType *hTemp = head;

    while (hTemp != NULL)
    {
        if (strcmp(hTemp->nodeData.key, key) == 0)
        {
            return hTemp;
        }    /* end if(hTemp->nodeData.key == key) */
        hTemp = hTemp->next;
    }    /* end while(hTemp == null) */
    return NULL;
}    /* end find_nodeCL */


/**
 * Description: 在find_key所在项后面插入nodeData
 */
CLType* insert_nodeCL(CLType *head, char *findKey, Data nodeData)
{
    CLType *node, *nodeTemp;

    if ((node = (CLType *)malloc(sizeof(CLType))) == NULL)
    {
        printf("申请内存失败！\n");
        return NULL;
    }    /* end if(node == null) */

    node->nodeData = nodeData;
    nodeTemp = find_nodeCL(head, findKey);
    if (nodeTemp != NULL)
    {
        node->next = nodeTemp->next;
        nodeTemp->next = node;
    }    /* end if(nodeTemp != null) */
    else
    {
        printf("未找到正确的插入位置！\n");
        free(node);
    }    /* end if(nodeTemp == null) */
    return head;
}    /* end insert_nodeCL */


/**
 * Description: 删除链表中关键字为key的项(注：不能删除表头项)
 */
int delete_nodeCL(CLType *head, char *key)
{
    CLType *node = head, *hTemp = head;

    while (hTemp != NULL)
    {
        if (strcmp(hTemp->nodeData.key, key) == 0)
        {
            node->next = hTemp->next;
            free(hTemp);
            return 1;
        }    /* end if(hTemp->nodeData.key == key) */
        else
        {
            node = hTemp;
            hTemp = node->next;
        }
    }    /* end while(hTemp == null) */
    return 0;
}    /* end delete_nodeCL */


/**
 * Description: 返回链表当前长度
*/
int lengthCL(CLType *head)
{
    CLType *hTemp = head;
    int len = 0;

    while (hTemp != NULL)
    {
        ++len;
        hTemp = hTemp->next;
    }    /* end while(hTemp == null) */
    return len;
}    /* end lengthCL */


/**
 * Description: 打印当前链表数据到终端
 */
void print_nodeCL(CLType *head)
{
    CLType *hTemp = head;
    Data nodeData;

    printf("当前链表共有%d个结点，链表所有数据如下：\n", lengthCL(head));
    while (hTemp != NULL)
    {
        nodeData = hTemp->nodeData;
        printf("结点(%s %s %d)\n", nodeData.key, nodeData.name, nodeData.age);
        hTemp = hTemp->next;
    }    /* end while(hTemp == null) */
}    /* end print_nodeCL */


/**
 * Description: 删除链表，释放内存
*/
void* delete_listCL(CLType *head)
{
    CLType *hTemp = head;
    while (hTemp != NULL)
    {
        hTemp = head->next;
        free(head);
        head = hTemp;
    }    /* end while(hTemp == null) */
    return NULL;
}


int main(void)
{
    CLType *node, *head = NULL;
    Data nodeData;
    char key[10], findKey[10];

    printf("链表测试。先输入链表中的数据，格式为：关键字 姓名 年龄\n");
    do
    {
        fflush(stdin);
        scanf("%s", nodeData.key);
        if (strcmp(nodeData.key, "0") == 0)
        {
            break;
        }    /* end if(nodeData.key == "0") */
        else
        {
            scanf("%s %d", nodeData.name, &nodeData.age);
            head = add_endCL(head, nodeData);
        }
    } while (1);    /* end while(nodeData.key == "0") */
    print_nodeCL(head);

    printf("\n演示插入结点，输入插入位置的关键字：");
    fflush(stdin);
    scanf("%s", findKey);
    printf("输入插入结点的数据(关键字 姓名 年龄)：");
    scanf("%s %s %d", nodeData.key, nodeData.name, &nodeData.age);
    head = insert_nodeCL(head, findKey, nodeData);
    print_nodeCL(head);

    printf("\n演示要删除的结点，输入要删除的关键字：");
    fflush(stdin);
    scanf("%s", key);
    delete_nodeCL(head, key);
    print_nodeCL(head);

    printf("\n演示查找链表中的数据，输入要查找的关键字：");
    fflush(stdin);
    scanf("%s", findKey);
    node = find_nodeCL(head, findKey);
    if (node != NULL)
    {
        nodeData = node->nodeData;
        printf("关键字%s对应的结点为(%s %s %d)\n", findKey, nodeData.key, nodeData.name
            , nodeData.age);
    }
    else
    {
        printf("没有在链表中找到关键字为%s的结点！\n", findKey);
    }

    head = delete_listCL(head);
    return 0;
}
