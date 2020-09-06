#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int g1 = 0, g2 = 0;

void task1(int *cnt);
void task2(int *cnt);
void cleanup(int cnt1, int cnt2);

int main(void)
{
    pthread_t thrd1, thrd2;
    int ret;

    ret = pthread_create(&thrd1, NULL, (void *)task1, (void *)&g1);
    if (ret != 0)
    {
        perror("pthread_create: task1");
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&thrd2, NULL, (void *)task2, (void *)&g2);
    if (ret != 0)
    {
        perror("pthread_create: task2");
        exit(EXIT_FAILURE);
    }

    pthread_cancel(thrd2);
    pthread_join(thrd2, NULL);
    // pthread_cancel(thrd1);
    pthread_join(thrd1, NULL);

    cleanup(g1, g2);
    exit(EXIT_SUCCESS);
}

void task1(int *cnt)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    printf("gid = %d\n", getpid());
    while (*cnt < 5)
    {
        printf("task1 cnt: %d\n", (*cnt)++);
        sleep(1);
    }
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}

void task2(int *cnt)
{
    printf("gid = %d\n", getpid());
    while (*cnt < 5)
    {
        printf("task2 cnt: %d\n", (*cnt)++);
        sleep(1);
    }
}

void cleanup(int cnt1, int cnt2)
{
    printf("pid is %d\n", getpid());
    printf("total %d\n", cnt1 + cnt2);
}