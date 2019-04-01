//2.3.3   双链表
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.7】  合并连接两条循环双链表。

#include "CirDoublyList.h"                                 //循环双链表类

int main()
{
    CirDoublyList<char> lista("abcd",4), listb("xyz",3);
    lista += listb;
    cout<<"lista："<<lista<<"listb："<<listb;

    system("pause");
    return 0;
}

/*
程序运行结果如下：
lista：(a, b, c, d, x, y, z)
listb：()

*/