#生成可执行文件的名称
Target = file_demo
ARCH ?= x86
#编译器CC
#根据传入参数ARCH，确定使用的编译器
#默认使用gcc编译器
#make ARCH=arm时使用ARM-GCC编译器
ifeq ($(ARCH), x86)
	CC = gcc
else
	CC = arm-linux-gnueabihf-gcc
endif
#存放中间文件的文件夹
build_dir = build_$(ARCH)
#存放源文件的文件夹
src_dir = .
## 因为源文件和makefile在同一目录，所以使用"."表示当前目录
#存放头文件的文件夹
inc_dir = includes .

#源文件
sources = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.c))
## wildcard用于获取文件列表并使用空格隔开
## sources = ./*.c  即源文件为当前目录下的所有.c后缀文件
#目标文件(*.o)
objects = $(patsubst %.c, $(build_dir)/%.o, $(notdir $(sources)))
## patsubst模式字符串替换
## notdir 去掉文件的路径中的目录部分
## 将源文件目录下的.c文件名提取替换为build_dir下的.o文件
#头文件
includes = $(foreach dir, $(inc_dir), $(wildcard $(dir)/*.h))
## includes = 将includes和当前目录下的.h文件
#编译参数
#指定头文件路径
CFLAGS = $(patsubst %, -I%, $(inc_dir))
## gcc -I 指定头文件路径
## 

#链接过程
#开发板上无法使用动态库，因此使用静态链接的方式
$(build_dir)/$(Target) : $(objects) | create_build
	$(CC) $^ -o $@
## "|"为前置依赖，表示create_build这个需要先被执行
## 编译所有依赖目标输出为目标文件

#编译工程
#编译src文件夹中的源文件，并将生成的目标文件放在objs文件夹中
$(build_dir)/%.o : $(src_dir)/%.c $(includes) | create_build
	$(CC) -c $(CFLAGS) $< -o $@

#以下为伪目标，调用方式为make 伪目标
#clean：用于clean project
#check：用于检查某个变量的值
.PHONY:clean cleanall check create_build
#按架构删除
clean:
	rm -rf $(build_dir)

#全部删除
cleanall:
	rm -rf build_x86 build_arm

#命令前带@表示不在终端输出执行命令
#这个目标主要用来调试makefile时输出一些内容
check:
	@echo $(CFLAGS)
	@echo $(CURDIR)
	@echo $(src_dir)
	@echo $(sources)
	@echo $(objects)

#创建一个新目录create，用于存放过程文件
create_build:
	@mkdir -p $(build_dir)