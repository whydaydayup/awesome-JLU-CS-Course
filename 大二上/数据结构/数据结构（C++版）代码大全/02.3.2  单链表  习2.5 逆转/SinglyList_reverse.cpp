//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.5】逆转单链表。

#include "SinglyList.h"                                    //单链表类

int main()
{
    SinglyList<char> list("ABCDEFGH",8);
    cout<<"单链表："<<list;
    list.reverse();
    cout<<"逆转后："<<list;

    system("pause");
    return 0;
}

/*
程序运行结果如下：
单链表：(A, B, C, D, E, F, G, H)
逆转后：(H, G, F, E, D, C, B, A)


head┌─┬─┐  ┌─┬─┐  ┌─┬─┐  ┌─┬─┐  ┌─┬─┐ 
  →│1 │  ┼→│2 │  ┼→│3 │  ┼→│4 │  ┼→│5 │＾│ 
    └─┴─┘  └─┴─┘  └─┴─┘  └─┴─┘  └─┴─┘ 
*/
