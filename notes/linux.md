<!--
 * @Author: youngjam
 * @Date: 2020-06-19 16:50:04
 * @LastEditTime: 2020-06-20 16:46:49
 * @Description:linux学习文件 
 * @logs: 
--> 
# linux文件目录
## home目录
* 当前用户的主文件夹
## /根目录
* linux下所有文件和目录的起点
## 根目录结构
* 根目录结构
    |目录|目录内容|
    |:-----|:-----------|
    |bin|存放系统命令|
    |boot|存放开机启动过程所需的内容|
    |dev|所有设备文件的目录|
    |etc|系统的配置文件|
    |home|用户的家目录数据存放目录|
    |lib|存放sbin和bin目录下命令所需的库文件|
    |lib32/lib64|存放二进制函数库，支持32位/64位|
    |lost+found|在ext3/4系统中，当系统意外崩溃或意外关机时，会产生一些碎片文件在该目录下，系统启动fcsk工具会检查该目录，并修复已损坏的文件|
    |media|用于挂载光盘，软盘和DVD等设备|
    |mnt|用于临时挂载存储设备|
    |opt|第三方软件安装存放目录|
    |proc|进程及内核信息存放目录，不占用硬盘空间|
    |root|root用户的家目录|
    |run|临时文件系统，存储系统启动以来的信息。当系统重启时，该目录下文件被删除或清除|
    |sbin|root用户使用的命令存放目录|
    |srv|一些网络服务所需要的数据文件|
    |sys|同proc目录，用于记录cpu和系统硬件的相关信息|
    |tmp|程序运行时产生的临时文件存放目录|
    |usr|系统存放程序的目录|
    |var|存放内容常变动的文件目录，如系统日志文件|
## 文件类型
* 在linux下，看到的一切都是文件，主要包括以下类型
  * `普通文件`：如文本文件，bin文件等
  * `可执行文件`：包括脚本和应用程序，这些文件可以被系统加载运行
  * `链接文件`：
        + `硬链接`：一个文件的不同别名
        + `软链接`：类似于快捷方式的特殊文件，包含了另一个文件的位置信息
  * `目录文件`：linux下目录也是文件
  * `设备文件`：硬件设备也是文件，通过打开相应的设备文件可以初始化部分设备，部分设备还可以通过读写设备文件实现对硬件的控制
## 文件扩展名
* 后缀.tar、.tar.gz、.tgz、.zip、.tar.bz等表示压缩文件，创建命令一般为tar、gzip、zip等，后缀通常表示自身的压缩格式
* .sh表示shell脚本文件
* .pl表示perl语言文件
* .py表示python文件
* .html、.htm、php、.jsp、.do等表示网页语言文件
* .conf表示系统服务的配置文件
* .rpm表示rpm安装包文件
----------------------------------------
# 用户组与文件权限
## 用户及用户组
* linux是多用户操作系统，其中具有管理其它用户和计算机全部资源的用户，称为root
* 在linux中，每个用户有一个特定的编号uid，用于标识一个系统用户
  ```shell
  ~$ id
  uid=1000(youngjam) gid=1000(youngjam) 组=1000(youngjam),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare)
  ```
* gid用于标识当前用户所在分组(Group)，每个用户可以对应多个分组
## 文件权限
* linux的文件属性可以分为读权限、写权限、执行权限(加载到内存中，由操作系统加载执行)
* 文件使用者的三种情况，文件拥有者、分组成员、其他分组成员
----------------------------------------
# 使用命令行
* `Shell`：指命令行解释器，常见的解释器有bash、sh，在ubuntu中默认使用bash解释器
* `终端(Terminal)`：通常指用来运行shell的程序，视场景的不同，如ubuntu系统自带的叫本地终端，嵌入式开发板常常提供串口进行输入输出的串口终端，通过网络访问的ssh终端
* `控制台(Console)`：特指某些终端，通常指它的物理形态，如带键盘和显示器的物理设备
## 打开终端
* 快捷键 ctrl+alt+k
## 命令提示符
  * 示例
    ```shell
    youngjam@ubuntu:~$
    ```
    + youngjam：显示的是当前的登录用户
    + @：分割符号，可理解为at，表示youngjam用户在主机ubuntu上
    + ubuntu：当前系统的主机名
    + “:”：分割符号
    + ~：冒号后表示用户当前所在目录，“~”表示当前用户的家目录
    + \$：命令提示符，标识用户的权限等级；超级用户为"#"，普通用户为"$"
## 常用命令
  * cd 切换目录
  * mkdir 创建新目录
  * touch 创建新文件
  * ls 显示指定目录下的内容
  * cat 把两个内容串联起来，通常用来在终端下输出文件进行查看
  * echo 在终端打印文字或变量
  * ">" 将命令执行的结果输出到文件(覆盖掉原文件)，">>"追加到文件的末尾
  * rmdir 删除空的目录 -p 递归删除子目录
  * rm 删除一个或多个文件或目录
    * -i：删除文件或文件夹前，终端会逐一询问确认
    * -r：将目录及其包含的子目录或文件全部删除
    * -f：忽略不存在的文件，无需逐一确认
  * sudo 为当前用户追加root权限
  * clear 清除当前屏幕
  * reboot/poweroff 控制系统的重启/关机
  * man 查看命令的说明手册
----------------------------------
# 包管理器
## 软件包与包管理工具
* 在Debian、Ubuntu等linux发行版中，通常使用deb(debian)形式的软件包，安装方式如下：
  ```sehll
  sudo dpkg -i xxxx.deb
  ```
## apt工具
* apt-get install 软件包名
* sudo apt-get install 软件包名
* apt-get remove 软件包名
* 常用镜像站
  * https://mirrors.tuna.tsinghua.edu.cn/
  * https://mirrors.ustc.edu.cn/
  * main：完全开源软件，可以被ubuntu官方完全支持的软件
  * multiverse：非开源软件，不提供任何支持和补丁
  * restricted：不完全开源的软件，依然被ubuntu官方那个支持的软件，不能提供完全技术支持
  * universe：ubuntu官方不提供支持与补丁，全靠社区支持
* 修改软件源
  * ubuntu软件源配置文件 etc/apt/sources.list
  * 软件源格式
    |软件包格式|镜像源地址|ubuntu发行版版本号|软件包类型|
    |:------------|:------------|:-------------------------|:------------|
    |deb/deb-src|https://mirrors.tuna.tsinghua.edu.cn/ubuntu/|bionic|main restricted universe multiverse|
    * 第一部分：deb格式表示软件包，deb-src对应软件的源代码
    * 第二部分：镜像源地址
    * 第三部分：发行版本号
    * 第四部分：软件包类型
* sudo apt-get update：扫描每个软件源地址，并为该软件源地址所具有软件包资源建立索引文件，存放在本地的var/lib/apt/lists/目录下
* apt-cache工具
  |命令|作用|
  |:----|:-----|
  |apt-cache showsrc package-name|显示软件包的相关信息，如版本信息，依赖关系等|
  |apt-cache search p-name|按关键字查找软件包|
  |... depends name|显示该软件包的依赖关系|
  |... rdepands name|显示所有依赖于该软件包的软件包名字|
  |... show name|显示指定软件包的信息，如版本信息，依赖关系等|
  |... pkgnames|显示所有软件包名字|
  |... policy name|显示软件包的安装状态|
## apt与apt-get
* 表-apt命令
  |命令|作用|
  |:----|:-----|
  |apt install pkg-name|安装指定软件包|
  |apt remove pkg-name|卸载指定的软件包|
  |apt update|更新软件源列表|
  |apt search pkg-name|根据关键字搜索对应的软件包|
  |apt show pkg-name|显示软件包的相关信息|
  |apt list|根据名称列出所有软件包|