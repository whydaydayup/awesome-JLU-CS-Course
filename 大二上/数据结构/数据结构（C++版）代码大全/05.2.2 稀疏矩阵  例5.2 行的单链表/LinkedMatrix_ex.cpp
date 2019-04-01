//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例5.2】  采用行的单链表存储稀疏矩阵。

#include "LinkedMatrix.h"                                  //采用行的单链表存储的稀疏矩阵类

int main()
{
    LinkedMatrix mat(3,4);                                 //构造矩阵，元素值为0
    cout<<mat;

    Triple itema[]={Triple(0,2,11), Triple(0,4,17), Triple(4,4,50), Triple(1,1,20), Triple(3,0,19), Triple(3,5,28)};
    Triple itemb[]={Triple(0,2,-11), Triple(0,3,15), Triple(2,0,19), Triple(3,5,20), Triple(4,5,31)};
    LinkedMatrix smata(5,6,itema,6), smatb(5,6,itemb,5);   //稀疏矩阵5行6列5个非零元素
    cout<<"三元组行的单链表：\n";
    cout<<"A "<<smata<<"\nB "<<smatb;

    system("pause");
    return 0;
}

/*
程序运行结果如下：
0 -> ()
1 -> ()
2 -> ()
三元组行的单链表：
A 0 -> ((0,2,11), (0,4,17))
1 -> ((1,1,20))
2 -> ()
3 -> ((3,0,19), (3,5,28))
4 -> ((4,4,50))

B 0 -> ((0,2,-11), (0,3,15))
1 -> ()
2 -> ((2,0,19))
3 -> ((3,5,20))
4 -> ((4,5,31))




*/