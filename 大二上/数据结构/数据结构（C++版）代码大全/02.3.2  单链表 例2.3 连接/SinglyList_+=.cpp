//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例2.3】连接两条单链表。

#include "SinglyList.h"                                    //单链表类

int main()
{
    SinglyList<char> lista("abc",3), listb("xy",2);        //创建单链表
    lista += listb;                                        //将listb链接在lista之后
    cout<<"lista："<<lista<<"listb："<<listb;              //输出单链表

    system("pause");
    return 0;
}

/*
程序运行结果如下：
（1）引用参数
lista：(a, b, c, x, y) 
listb：()


（2）对象参数，浅拷贝
(a, b, c, x, y) 
()                                                   //运行错

（3）对象参数，深拷贝
析构~SinglyList ()
lista：(a, b, c, x, y)
listb：(x, y)
析构~SinglyList (x, y)
析构~SinglyList (a, b, c, x, y)


*/
