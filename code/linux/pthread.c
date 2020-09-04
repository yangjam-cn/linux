#include <pthread.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <stdlib.h>

void task1(int *count);
void task2(int *count);
void cleanup(int counter1, int counter2);

int g1 = 0;
int g2 = 0;

int main(int argc, char **argv)
{
    pthread_t thrd1, thrd2;
    int ret;

    ret = pthread_create(&thrd1, NULL, (void *)task1, (void *)&g1);
    if (ret != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&thrd2, NULL, (void *)task2, (void *)&g2);
    if (ret != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(thrd2, NULL);    /*挂起当前线程，直到指定线程结束*/
    pthread_join(thrd1, NULL);

    cleanup(g1, g2);
    exit(EXIT_SUCCESS);
}

void task1(int *count)
{
    while (*count < 5)
    {
        printf("task1 count: %d\n", *count);
        ++(*count);
        sleep(1);
    }
}

void task2(int *count)
{
    while (*count < 5)
    {
        printf("task2 count: %d\n", *count);
        ++(*count);
        sleep(1);
    }
}

void cleanup(int counter1, int counter2)
{
    printf("total iterations: %d\n", counter1 + counter2);
}