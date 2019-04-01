//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例6.1】二叉树的构造、遍历及插入。

#include "BinaryTree.h"                                    //二叉树类

int main()
{
                                                           //图6.21所示二叉树标明空子树的先根序列
    char prelist[] = {'A','B','D',NULL,'G',NULL,NULL,NULL,'C','E',NULL,NULL,'F','H'};
    BinaryTree<char> bitree(prelist, 14);
    cout<<bitree;                                          //输出先根次序遍历序列（标明空子树）
    bitree.inOrder();                                      //输出中根次序遍历序列
    bitree.postOrder();                                    //输出后根次序遍历序列
    bitree.insert(bitree.root->left,'X');                  //插入左孩子，图6.20（a）
    bitree.insert(bitree.root->right,'Y',false);           //插入右孩子，图6.20（b）
    bitree.insert('Z');                                    //插入根
    cout<<bitree;
    
    bitree.preOrderTraverse();                             //7.  二叉树遍历的非递归算法
    bitree.inOrderTraverse();
    bitree.levelOrder();                                   //8.  二叉树的层次遍历
    
    system("pause");
    return 0;
}

/*
程序运行结果如下：
先根次序遍历二叉树:  A B D ∧G ∧∧∧C E ∧∧F H ∧∧∧                 //例6.1
中根次序遍历二叉树:  D G B A E C H F 
后根次序遍历二叉树:  G D B E H F C A 
先根次序遍历二叉树:  Z A B X D ∧G ∧∧∧∧C E ∧∧Y ∧F H ∧∧∧∧
请按任意键继续. . . 
撤销二叉树: G D X B E H F Y C A Z 
*/
 


