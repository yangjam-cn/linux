#include <iostream>
int main(void)
{
    using namespace std;
    cout << "hello linux!" << endl;
    return 0;
}

/*diff -c old.cpp new1.cpp > old.patch //生成补丁*/
/*patch -p0 < old.patch //安装补丁*/
/*patch -p0 -R < old.patch //逆向补丁还原原文件*/