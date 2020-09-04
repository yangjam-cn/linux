#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <pthread.h>
#include <errno.h>

#define INDEX 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long int ticks;
time_t end_time;

void idx_th(void *arg);
void mon_th(void *arg);

void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    pthread_t idx_th_id;
    pthread_t mon_th_id;
    int ret;

    end_time = time(NULL) + 30;
    /*创建线程*/
    ret = pthread_create(&idx_th_id, NULL, (void *)idx_th, NULL);
    if (ret != 0)
        err_quit("pthread_create:idx_th");
    
    ret = pthread_create(&mon_th_id, NULL, (void *)mon_th, NULL);
    if (ret != 0)
        err_quit("pthread_create:mon_th");

    pthread_join(idx_th_id, NULL);
    pthread_join(mon_th_id, NULL);

    exit(EXIT_SUCCESS);
}

void idx_th(void *arg)
{
    long l;

    while (time(NULL) < end_time)
    {
        if (pthread_mutex_lock(&mutex) != 0)    /*为互斥加锁*/
            err_quit("pthread_mutex_lock");

        for (l = 0l; l < INDEX; ++l)
            ++ticks;

        // sleep(1);

        if (pthread_mutex_unlock(&mutex) != 0)    /*解锁互斥*/
            err_quit("pthread_mutex_unlock");
        sleep(1);
    }
}

void mon_th(void *arg)
{
    int noLock = 0;
    int ret;

    while (time(NULL) < end_time)
    {
        sleep(1);

        ret = pthread_mutex_trylock(&mutex);    /*互斥try加锁*/
        if (ret != EBUSY)    /*互斥没有锁*/
        {
            if (ret != 0)
                err_quit("pthread_mutex_trylock");

            printf("mon_th: got lock at %ld\n", ticks);
            if (pthread_mutex_unlock(&mutex) != 0)    /*解除trylock加上的锁*/
                err_quit("pthread_mutex_nulock");
        }
        else
        {
            noLock++;
        }
    }
    printf("mon_th missed lock %d times\n", noLock);
}