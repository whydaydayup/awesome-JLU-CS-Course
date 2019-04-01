//《数据结构（C++版）（第3版）》 作者：叶核亚
//【实验6-3】二叉链表表示的完全二叉树类。

#include "CompleteBinaryTree.h"                       //完全二叉树类

int main()
{
    char levellist[] = "ABCDEFGH";                   //图6.17所示完全二叉树的层次遍历序列
    CompleteBinaryTree<char> cbitree(levellist, 8);
    cbitree.preOrder();
    cbitree.inOrder();
    cbitree.postOrder();
    cout<<"二叉树结点个数："<<cbitree.count()<<endl;
    cout<<"二叉树高度："<<cbitree.height()<<endl<<endl;
    return 0;
}

/*
程序运行结果如下：
先根次序遍历二叉树:  A B D H E C F G
中根次序遍历二叉树:  H D B E A F C G
后根次序遍历二叉树:  H D E B F G C A 
二叉树结点个数: 8
二叉树高度: 4
撤销二叉树:  H D E B F G C A 

*/
 
