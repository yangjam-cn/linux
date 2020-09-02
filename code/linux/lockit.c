#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void set_lock(int fd, int type);

int main(int argc, char **argv)
{
    int fd;

    fd = open(argv[1], O_CREAT | O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    set_lock(fd, F_RDLCK);    /*设置读取锁*/
    printf("PID %d locked %s\n", getpid(), argv[1]);
    getchar();

    set_lock(fd, F_UNLCK);    /*清除锁*/
    printf("PID %d unlocked %s\n", getpid(), argv[1]);
    getchar();

    set_lock(fd, F_WRLCK);    /*设置写入锁*/
    printf("PID %d write locked %s\n", getpid(), argv[1]);
    getchar();

    close(fd);
    set_lock(fd, F_UNLCK);
    exit(EXIT_SUCCESS);
}

void set_lock(int fd, int type)
{
    struct flock lock;
    char msg[80];

    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 1;

    /*直到上锁成功返回*/
    while (1)
    {
        lock.l_type = type;

        if ((fcntl(fd, F_SETLK, &lock)) == 0)    /*文件上锁*/
            return;
        
        /*上锁失败*/
        fcntl(fd, F_GETLK, &lock);    /*读取文件是否上锁*/
        if (lock.l_type != F_UNLCK)
        {
            switch (lock.l_type)
            {
                case (F_RDLCK):
                    sprintf(msg, "read lock already set by %d\n"
                        , lock.l_pid);
                    break;
                case (F_WRLCK):
                    sprintf(msg, "write lock already set by %d\n"
                        , lock.l_pid);
                    break;
                default:
                    break;
            }
            puts(msg);
            getchar();
        }
    }
}