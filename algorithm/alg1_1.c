/**
 * @copyright: Copyright (c) 2020 yungjam All rights reserved.
 * @filename: alg1_1.c
 * @description: 在拥有20个整数数据的数组中查找数据
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.11.02
 * @history:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
int arr[N];

/**
 * Description: 以number为随机数种子创建随机序列，在其中查找number
 * Return: 0->找到number    -1->没有找到number
 */
int find_number_game(int number);

int main(void)
{
    int init;
    int flag = -1;
    printf("请输入要查找的整数：");
    scanf("%d", &init);

    flag = find_number_game(init);

    while (flag != 0)
    {
        flag = find_number_game(arr[0]);
    }

    return 0;
}

int find_number_game(int numer)
{
    int x = numer, n, i;
    int f = -1;

    srand((unsigned)numer);

    for (i = 0; i < N; ++i)
    {
        arr[i] = rand() %100;
    }

    for (i = 0; i < N; ++i)
    {
        if (x == arr[i])
        {
            f = i;
            break;
        }
    }

    printf("\n随机生成的数据序列：\n");
    for (i = 0; i < N; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    if (f < 0)
    {
        printf("没找到数据：%d\n", x);
        return -1;
    }
    else
    {
        printf("数据：%d位于数组的第%d个元素处.\n", x, f + 1);
        return 0;
    }
}

