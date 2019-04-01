//《数据结构（C++版）（第3版）》 作者：叶核亚
//3.2.3   字符串类

#include "MyString.h"                   //顺序串类

int main() 
{
    const int N=6;
    MyString str[N]={MyString("abc"), MyString("abc"), MyString("axbc"),MyString("abcdef"),MyString(""),MyString()};
    for (int i=0; i<N; i++)
        cout<<str[i]<<endl;

    MyString s1(str[3]), s2=str[2], s3, s4;                //深拷贝
    s3=str[3];                                             //赋值，深拷贝，要扩容，重新分配
    s4="wxyz";
    cout<<"s1："<<s1<<"\ns2："<<s2<<"\ns3："<<s3<<"\ns4："<<s4<<endl;
/*
    for (int i=1; i<5; i++)
        cout<<str[0]<<" < "<<str[i]<<" ？ "<<(str[0]<str[i])<<endl;
    for (int i=1; i<5; i++)
        cout<<str[0]<<" <= "<<str[i]<<" ？ "<<(str[0]<=str[i])<<endl;
    for (int i=1; i<5; i++)
        cout<<str[0]<<" > "<<str[i]<<" ？ "<<(str[0]>str[i])<<endl;
    for (int i=1; i<5; i++)
        cout<<str[0]<<" >= "<<str[i]<<" ？ "<<(str[0]>=str[i])<<endl;
*/
    //2.  对子串的操作
    //（1）求子串
    cout<<s1<<".substring(0,9)="<<s1.substring(0,9)<<endl;
    cout<<s1<<".substring(3)="<<s1.substring(3)<<endl;
//    cout<<s1<<".substring(-1,9)="<<s1.substring(-1,9)<<endl;
//    cout<<s1<<".substring(0,-9)="<<s1.substring(0,-9)<<endl;

    //（2）插入串
//    s3.insert(4, s3.substring(3));                               //要扩容
/*    s1.insert(2, s2);                                              //不扩容
    cout<<"插入串，s1："<<s1<<endl;

    //（3）连接串
    cout<<"\""<<s1<<"\"+\""<<s2<<"\"=\""<<(s1+s2)<<"\""<<endl;  //要扩容
    s1+=s2;                                                     //要扩容
    cout<<"\""<<s1<<"\"+=\""<<s2<<"\"=\""<<s1<<"\""<<endl;
 
    //（4） 删除子串
    cout<<"\""<<s1<<"\".remove(2, 9); ";
    s1.remove(2, 9);                                              //删除到串尾
    cout<<"s1：\""<<s1<<"\""<<endl;
*/

    system("pause");
    return 0;
}
/*
程序运行结果如下：
abc
abc
axbc
abcdef


s1：abc
s2：abc
s3：axbc
s3：abcdef
abc < abc ？ 0
abc < axbc ？ 1
abc < abcdef ？ 1
abc <  ？ 0
abc <= abc ？ 1
abc <= axbc ？ 1
abc <= abcdef ？ 1
abc <=  ？ 0
abc > abc ？ 0
abc > axbc ？ 0
abc > abcdef ？ 0
abc >  ？ 1
abc >= abc ？ 1
abc >= axbc ？ 0
abc >= abcdef ？ 0
abc >=  ？ 1
MyString析构abcdef，count=6，length=7
"abcdef".substring(0,9)="abcdef"
MyString析构abcdef，count=6，length=12
MyString析构def，count=3，length=6
"abcdef".substring(3)="def"
MyString析构def，count=3，length=6
请按任意键继续. . . 
MyString析构abcdef，count=6，length=12
MyString析构abc，count=3，length=6
MyString析构abc，count=3，length=6
MyString析构，count=0，length=6
MyString析构，count=0，length=6
MyString析构abcdef，count=6，length=12
MyString析构axbc，count=4，length=8
MyString析构abc，count=3，length=6
MyString析构abc，count=3，length=6
*/
