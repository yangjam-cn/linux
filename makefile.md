<!--
 * @Author: youngjam
 * @Date: 2020-07-01 20:19:36
 * @LastEditTime: 2020-07-01 21:10:37
 * @Description:makefile知识 
 * @logs: 
--> 
# 函数
## foreach函数
* $(forech < var >, < list >, < text >)
  * 把参数< list >中的单词逐一取出放到参数< var >所指定的变量中，然后再执行< text >所包含的表达式。每一次< text >会返回一个字符串。循环过程中，< text >所返回的每个字符串会以空格分隔。最后循环结束时，< text>所返回的每个字符串所组成的整个字符串将会是foreach的返回值
  * var是一个临时的局部变量，其作用于仅在foreach函数中
  * list可以是一个表达式
    ```makefile
    names = a b c d
    files := $(foreach n, $(names), $(n).o)
    # files = a.o b.o c.o d.o
    ```
## patsubst
* $(patsubst < pattern>, < replacement>, < text>)
  * 名称：模式字符串替换函数
  * 功能：查找< text>中的单词(单词以“空格”、“Tab”或“回车”“换行”分隔)是否符合模式< pattern>，如果匹配的话，则以< replacement>替换。《patern》可以包括通配符"%"表示任意长度字串。如果《replacement》中也包含"%"，那么《replacement》中的"%"将是《patern》中的那个"%"代表的字串。(可以用"\%"转义"%")
  * 返回：替换后的字串
  ```makefile
  $(patsubst %.c, %.o, x.c bar.c)
  # output = x.o bar.o
  ```
  # 变量
  ## 自动化变量
  * 列表
    |符号|意义|
    |:---:|:-----|
    |$@|匹配目标文件|
    |$%|与 $@类似，但$%仅匹配"库类型的目标文件"|
    |$<|依赖中的第一个目标文件|
    |$^|所有的依赖目标，如果依赖中有重复的，只保留一份|
    |$+|所有的依赖目标，即使重复也原样保留|
    |$?|所有比目标要新的依赖目标|