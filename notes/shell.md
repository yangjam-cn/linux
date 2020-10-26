# shell编程

## 文件安全与权限

* 文件访问方式
  * 读
  * 写
  * 执行
* 文件权限
  * 文件属主
  * 同组用户
  * 其他用户

```shell
-rw-rw-r-- 1 yungjam yungjam 1.8K 10月 19 13:18 串行通信.md
-rw-rw-r-- 1 yungjam yungjam 4.2K 10月 19 13:18 多线程.md
-rw-rw-r-- 1 yungjam yungjam  14K 10月 19 13:18 进程间通信.md
-rw-rw-r-- 1 yungjam yungjam  425 10月 19 13:58 数的表示.md
-rw-rw-r-- 1 yungjam yungjam 6.8K 10月 19 13:19 c_cpp面试.md
-rw-rw-r-- 1 yungjam yungjam  12K 10月 19 13:19 linux编程.md
-rw-rw-r-- 1 yungjam yungjam  155 10月 19 21:41 shell.md
```

* suid和guid
  * 文件被设置suid位后，使用该文件的用户将获得与文件属主相同的权限

## 相关命令

* touch 创建文件
* chmod 修改文件权限
  * chmod [who] [operator] [permission] filename
  * who: u o g a
  * operator: + - =
  * permission: r w x s t l
  * chmod [mode] filename
  * mode: 八进制数
