# Linux编程

## 文件结构

* /bin: 二进制可执行文件
* /etc: 系统配置文件
* /home: 用户家目录
* /tmp: 临时目录
* /var: 经常变化的文件存放目录
* /proc: 将当前运行的进程映射为文件
* /dev: 设备目录
* /usr: 用户相关的程序和库文件
* /sbin: 系统相关的可执行程序
* /boot: 启动过程相关文件，linux内核和引导配置文件

## 系统结构

* 用户程序
* shell: 命令解释器
* 库函数
* linux内核
* 设备驱动

## 文件系统

* 虚拟文件系统(VFS)， 将各种文件系统的公共部分抽象出来，形成抽象层。对用户程序提供文件系统的系统调用接口，而对具体的文件分区格式通过统一的调用接口来屏蔽实现细节，使得文件系统的调用不用关心底层的存储介质和文件系统类型。
  * linux系统初始化时，首先在内存中初始化VFS目录树(给实际的文件系统提供挂载点)
  * 当创建目录时，首先对VFS进行查询，获得建立目录的上级目录信息
  * 在目录下挂载分区时，VFS将对VFS目录树的操作转化为挂载到这个目录的具体文件系统的操作

## 文件

* linux在通过inode实现对文件的管理，inode结构中存储了文件属性、访问权限以及文件数据块的位置

### 文件类型

* d 目录文件
* l 符号链接文件
* s 套接字文件
* b 块设备文件
* c 字符设备文件
* p 命名管道文件
* '-' 普通文件

### 文件访问权限

```shell
ls -lih
1318712 -rw-rw-r-- 1 yungjam yungjam  160 10月  3 15:28 Makefile
1318032 drwxrwxr-x 2 yungjam yungjam 4.0K 10月  4 14:35 RCS
1315638 -rw-rw-r-- 1 yungjam yungjam  612 10月  3 19:49 strcpy.cpp
```

|i节点号|文件类型|所有者权限|组权限|其它用户权限|

### 硬链接和符号链接

* 一个inode可以存在任意数目硬链接
* 删除硬链接不影响节点上的数据
* 删除节点，硬链接依然存在，节点数据也依然存在
* 只有文件才可以建立硬链接
* 硬链接不能跨越文件系统

* 符号链接通过名称指向另一个文件
* 符号链接不影响文件的删除，若文件删除，符号链接将不可用

```bash
-rw-rw-r-- 2 yungjam yungjam  17 10月  4 16:13 hello.dat
-rw-rw-r-- 2 yungjam yungjam  17 10月  4 16:13 hello.link
lrwxrwxrwx 1 yungjam yungjam   9 10月  4 16:14 hello.slink -> hello.dat
```

## 设备文件

* 字符设备：像字节流一样访问的设备
* 块设备：每次以一个或多个块进行传输
* 网络接口：

### 终端设备

* 没有自己的cpu和内存单元，在linux中以tty标识

* 串行端口终端(/dev/ttySn): 使用串行端口连接的终端设备
* 伪终端(dev/pts/n): 使用Telent登录linux实际上是登录到伪终端
* 控制终端(/dev/tty): 如果当前进程存在控制终端，/dev/ttyN就是当前进程的控制终端的设备文件
* 控制台终端(/dev/ttyn,/dev/console): 在linux常将显示器称为控制台终端, 从控制台登录linux使用的是tty1， tty1~tty6称为虚拟终端

#### 终端控制

* stty 显示终端设置
* reset 重置终端参数，清空终端

```cpp
#include <unsitd.h>
char *ttyname(int fd);
int tcgetattr(int fd, struct termios *termios_p);    /* 获取终端参数 */
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);    /* 修改终端参数 */
```

#### 串行通信

## 操作函数

* getcwd: 获取当前目录名
* pathconf: 获取当前系统目录最大长度
* chdir: 改变当前工作目录
* fcdir: 改变当前工作目录
* mkdir: 创建目录
* rmdir: 删除目录

```cpp
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*打开文件，返回文件描述符*/
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
/* 关闭文件 */
int close(int fd);

/* 获取文件信息 */
int stat(const char *path, struct stat *buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *path, struct stat *buf);    /*当是符号链接时，返回符号链接信息*/

/* 修改文件权限 */
int chmod(const char *path, mode_t mode);
int fchmod(int fileds, mode_t mode);

/* 修改文件拥有者 */
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fileds, uid_t owner, gid_t group);
int lchown(const char *path, uid_t, gid_t);

/* 创建链接 */
int link(const char *oldpath, const char *newpath);    /* 创建硬链接 */
int symlink(const char *oldpath, const char *newpath);    /* 创建符号链接 */
/* 删除链接 */
int unlink(const char *pathname);

/* 获取目录 信息*/
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dir);

/* 创建文件 */
int create(const char *pathname, mode_t mode);

/* 读写文件 */
ssize_t read(int fd, void *buf, size_t count);    /* 返回读取字节数，0表示读到文件结束位置，-1错误 */
ssize_t write(int fd, const void *buf, size_t count);

/* 改变文件指针位置 */
off_t lssek(int fileds, off_t offset, int whence);

/* 复制文件描述符 */
int dup(int oldfd);
int dup2(int oldfd, int newfd);    /* 若新的文件描述符已打开，则先关闭 */
```

## 进程

### 进程分类

* 交互进程: 由shell启动的进程，可以运行在前台或后台，运行过程中需要用户提供参数或信息
* 批处理进程: 进程序列
* 守护进程: 执行特定功能或者系统相关任务的后台进程

### 虚拟内存

* 提供巨大的寻址空间，分为用户空间和内核空间
* 共享虚拟内存，共享内存提供进程间通信
* 进程保护，进程运行在自己的虚拟地址空间

### shell命令

* vmstat:  查看虚拟内存使用情况
  * procs
    * r: 等待获得cpu时间运行的进程数
    * b: 处于不可中断休眠的进程数
  * memory
    * swapd: 已用虚拟内存大小
    * free: 空闲内存大小
    * buff: 用作磁盘缓冲的内存大小
    * cache: 用作缓冲的内存大小
  * swap
    * si: 每秒从磁盘换入的内存大小
    * so: 每秒从磁盘换出的内存大小
  * io
    * bi: 每秒从磁盘读取的块数
    * bo: 每秒写入磁盘的块数
  * system
    * in: 每秒中断发生次数
    * cs: 每秒上下文切换的次数
  * cpu
    * us: 用户程序所占cpu时间比例
    * sy: 内核代码所占cpu时间比例
    * id: cpu空闲时间所占时间比例
    * wa: 用于等待IO操作所占时间比例
    * st: 抢占虚拟机运行所占时间比例

### 进程内存空间结构

1. 代码段: 用于保存可执行文件的操作指令和程序定义的常量，代码段为只读，当程序多次执行时共享代码段
2. 数据段: 分为初始化数据段和未初始化数据段，初始化段存放初始化的全局变量和静态变量，未初始化段存放为初始化的全局变量
3. 堆栈段: 用于进程运行过程中动态分配内存

### 进程标识

* 进程pid和父进程ppid
* 用户标识uid和有效用户标识euid(一般相同)
  * uid表示进程的创建者
  * euid表示进程对资源和文件的访问权限
  * setuid文件的特殊属性，当设置了setuid后，任何用户启动该文件时，都会将euid设置为创建者的uid，使得使用者获得与创建者相同的权限，如/usr/bin/passwd，使得用户可以通过passwd修改密码
* 组标识gid和有效组标识egid

### 进程创建

* fork和vfork
  * 传统的fork函数在创建新的子进程时会复制所有父进程所拥有的资源
  * vfork创建子进程不会复制相关资源，而是与父进程共享内存空间
  * 使用vfork后，父进程会被阻塞，直到子进程调用exec或_exit函数(子进程不能使用return和exit)
* fork系统调用机制
  * 写时复制(copy-on-write, COW)，子进程在创建时并不复制父进程的资源，而是通过访问相同的物理内存来伪装已经实现了对资源的复制，但是这种共享只是只读的，当子进程对内存数据执行写操作时，才进行资源的复制
* exit、_exit和return
  * 在主程序中使用正常结束程序
  * exit函数结束进程时，会先执行atexit函数注册的函数，然后调用on_exit函数清理动作；函数执行顺序与注册的顺序相反
  * _exit函数立即结束调用进程，与进程相关的文件描述符都将关闭，进程的子进程都将变成init进程的子进程，不会执行注册函数
  * exit和_exit区别
    * exit是ANSI C函数，_exit是POSIX标准函数
    * exit函数终止调用进程，在退出前关闭所有文件，清空标准输入输出缓冲区，并执行atexit注册的回调函数
    * _exit终止调用进程，关闭进程相关文件，不清空标准输入输出缓冲区，也不调用回调函数
* wait
  1. 判断子进程是否存在
  2. 子进程存在
     1. 判断子进程是否结束
     2. 没结束，阻塞父进程，返回1(line.225)
     3. 结束，返回状态值和子进程pid
  3. 不存在，返回-1

### 僵尸进程

* 子进程退出后，父进程没有使用wait函数收集子进程状态而产生
* 僵尸进程不占据cpu资源，但是会占据进程表空间
* 杀死僵尸进程，杀死僵尸进程的父进程，进程会被init进程接管，init会负责相应的清理工作

### 守护进程

* 运行在后台的特殊进程，不存在控制终端，并周期性地执行某项任务或等待处理某项任务
  * 所有守护进程都由root用户启动
  * 没有控制终端 tty为?
  * 终端进程组ID(tpgid)为-1，该值表示与控制终端相关的前台进程组

#### 创建守护进程

1. 让init成为新进程的父进程
   * 调用fork创建进程后，立刻退出父进程，init将接管子进程成为其父进程
2. 调用setsid函数
   * 让新进程脱离控制终端，同时创建新的进程组，该进程成为该组的首进程
   * 新进程继承了父进程的控制终端、进程组和会话，故使用setsid创建新的会话脱离父进程的影响
   * pid_t setsid(void);
3. 更改当前工作目录
   * fork函数继承了父进程的工作目录，当进程没有结束时，工作目录不能卸载，故一般将目录更改为/
4. 关闭文件描述符，并重定向标准输入、输出和错误
   * 关闭不用的文件
   * 后台进程不应该在终端上产生输出信息，可以使用dup重定向到/dev/null(空设备)
5. 设置守护进程的文件权限创建掩码
   * 用户保护进程产生的临时文件，不被其他用户查看

### 进程组和会话(session)

* 进程组是一个或多个进程的集合，组内成员拥有相同的gpid(由领头进程的pid决定)，
* 会话是一个或多个进程组的集合，每个会话都有一个领头进程
* 每个进程都属于一个进程组，进程组又属于某个会话，当用户从终端登录系统时，系统会创建一个新会话，在该终端上启动的进程都会被系统划归到会话的进程组中
* 会话中的进程通过该会话的领头进程(控制进程)与一个终端相连，该终端是会话的控制终端，一个会话只能有一个控制终端
* 若会话存在一个控制终端，那它必然拥有一个前台进程组，属于该组的进程可以从终端获得输入，其他进程组都为后台进程组

### 进程间通信

### 系统命令

* ps
* chmod

### 函数调用

```cpp
#include <sys/type.h>
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
uid_t getgid(void);
uid_t getegid(void);

pid_t fork(void);
pid_t vfork(void);    /* 父子进程共享虚拟内存空间 */

/* exec函数对创建进程的数据段、代码段和堆栈段进行替换 */
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg,..., char *const envp[]);
int execv(const char *path, const char *arg[]);
int execvp(const char *file, const char *arg[]);
int execve(const char *path, const char *arg[], char *const envp[]);

/* wait用于父进程等待子进程结束 */
#include <sys/wait.h>
pid_t wait(int *status);    /* 挂起当前进程直到子进程结束 */
pid_t waitpid(pid_t pid, int *status, int options);

int kill(pid_t pid, int sig);
```
