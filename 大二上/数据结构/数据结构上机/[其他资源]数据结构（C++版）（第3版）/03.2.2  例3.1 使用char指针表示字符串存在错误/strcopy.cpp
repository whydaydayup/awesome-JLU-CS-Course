//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例3.1】 C/C++语言的string.h中strcpy()和strcat()函数存在下标越界错误。

#include <iostream>
using namespace std;
#include <string.h>

int main()
{
    char src[]="abcdefghijlkmn", dest[3]="", *p;
    p = strcpy(dest, src);                            //VC++ 2008编译警告:“strcpy函数不安全”
    cout<<"src=\""<<src<<"\", dest=\""<<dest<<"\", p=\""<<p<<"\""<<endl;

    system("pause");
    return 0;
          //之后有运行错
}

/*
程序运行 ：



*/
