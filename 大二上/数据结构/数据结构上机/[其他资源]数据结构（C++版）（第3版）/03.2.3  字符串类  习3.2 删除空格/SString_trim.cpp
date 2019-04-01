//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习3.2】  删除串中所有空格。

#include "MyString.h"                   //顺序串类
using namespace std;

int main() 
{
    MyString str("   a bc d  e  f  xyz");
    cout<<str<<"，count="<<str.count()<<endl;
    str.trim();

//    trim(str);
    cout<<str<<"，count="<<str.count()<<endl;

//    str.removeAll(" ");
//    cout<<"str.removeAll(" ")="<<str<<endl;

    system("pause");
    return 0;
}

/*
程序设计运行结果如下：
abcdefxyz
*/

/*??
void trim(MyString &str)                          //删除str串中所有空格字符
{
    int n=str.length(), i=0;                     //n获得串长度
    while (i<n)
        if (str.charAt(i)!=' ')                  //非空格
            i++;
        else
        {
            str.remove(i,1);                     //删除空格
            n--;
        }
}*/