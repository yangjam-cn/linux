#include <unistd.h>
#include <stdio.h>

int main(void)
{
    unsigned int seconds;
    printf("this an alarm test function!\n");
    seconds =  alarm(20);
    printf("last alarm seconds remianing is %u!\n", seconds);
    printf("process sleep 5 seconds!\n");
    sleep(5);
    printf("sleep woke up, reset alarm!\n");
    seconds = alarm(5);
    printf("last alarm seconds remaining is %u!\n", seconds);
    sleep(20);
    printf("couldn't printf this message!\n");
    return 0;
}