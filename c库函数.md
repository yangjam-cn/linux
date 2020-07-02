<!--
 * @Author: youngjam
 * @Date: 2020-07-02 08:41:11
 * @LastEditTime: 2020-07-02 09:30:54
 * @Description: 
 * @logs: 
--> 
# 常用文件操作
## fopen函数
* FILE *fopen(const *pathname, conts char *mode);
    * pathname：指定打开或要创建的文件名
    * mode：指定文件打开方式，输入为字符串
      * "r"：以只读方式打开，文件指针位于文件开头
      * "r+"：以读和写的方式打开文件，文件指针位于文件开头
      * "w"：以写的方式打开，原内容清空，文件指针位于开头
      * "w+"：同上，不过当文件不存在时会创建新文件，"w"会返回错误
      * "a"：以追加内容的方式打开，若文件不存在则创建新文件，文件指针位于末尾，不会清空原内容
      * "a+"：以读和追加的方式打开文件，其他同上
    * 返回值是FILE类型的文件流，当值不为NULL表示正常
## fread函数
* size_t frad(void *ptr, size_t size, size_t nmemb, FILE *stream);
* stream是使用fopen打开的文件流，fread通过它指定要访问的文件，它从该文件中读取nmemb项数据，每项的大小为size，读取的数据会被存储到ptr指向的数组中。fead的返回值为成功读取的项数(项的单位为size)
## fwrite函数
* size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
* 与fread相反，把ptr数组中的内容写入到stream文件流，写入的项数为nmemb，每项的大小为size，返回成功写入的项数
## fclose函数
* int fclose(FILE *stream);
* 关闭指定的文件流，关闭时会把尚未写到文件的内容都写出
## fflush函数
* int fflush(FILE *stream);
* fflush函数用于把尚未写到文件的内容立即写出,常用于确保前面操作的数据被写入到磁盘上，fclose函数本身也包含了fflush操作
## fseek函数
* int fseek(FILE *stream, long offset, int whence);
* fseek函数用于设置下一次读写函数操作的位置
* offset用于指定位置
* whence定义了offset的意义，取值如下
  * SEEK_SET：offset是绝对位置
  * SEEK_END：offset是以文件尾为参考点的相对位置
  * SEEK_CUR：offset是以当前位置为参考点的相对位置