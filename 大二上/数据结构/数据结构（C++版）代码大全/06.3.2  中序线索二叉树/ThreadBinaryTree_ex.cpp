//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.3   线索二叉树
//6.3.2   中序线索二叉树
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习6.1】构造中序线索二叉树并分别按先根、中根、后根次序遍历。

#include "ThreadBinaryTree.h"                         //中序线索二叉树类

int main()
{                                                      //图6.25所示二叉树标明空子树的先根遍历序列
    char prelist[] = {'A','B','D',NULL,NULL,'E','G',NULL,NULL,NULL,'C','F',NULL,'H',NULL,NULL,'K'};
    ThreadBinaryTree<char> tbitree(prelist, 17);      //创建中序线索二叉树
    tbitree.inOrder();                                //中根次序遍历
    tbitree.preOrder();                               //先根次序遍历
    tbitree.inOrderPrevious();                        //中根次序遍历（求前驱）
    tbitree.postOrderPrevious();                      //后根次序遍历（求前驱）

    system("pause");
    return 0;
}

/*
程序运行结果如下：
//插入
中根次序遍历中序线索二叉树:  C B X F E G H D W A Y J M L K N Z I O 
先根次序遍历中序线索二叉树:  A B C X D E F G H W I Z J Y K L M N O 
中根次序（反序）遍历中序线索二叉树:  O I Z N K L M J Y A W D H G E F X B C 
后根次序（反序）遍历中序线索二叉树:  A I O Z J K N L M Y B X D W E G H F C 
撤销中序线索二叉树: C F H G E W D X B Y M L N K J Z O I A 

*/ 
/*
以下第3版未调试
    char prelist[] = {'A','B','C',NULL,NULL,'D','E','F',NULL,NULL,'G',NULL,'H',NULL,NULL,NULL,
                          'I','J',NULL,'K','L','M',NULL,NULL,NULL,'N',NULL,NULL,'O'};
    ThreadBinaryTree<char> tbitree(prelist, 29);      //创建中序线索二叉树
    //插入
//    ThreadBinaryTree<char> tbitree;                   //创建空中序线索二叉树
    tbitree.insertRoot('A');                          //插入根
    tbitree.insert(tbitree.root->left->right, 'W', false);//插入D的右孩子W
    tbitree.insert(tbitree.root->left, 'X', false);     //插入B的右孩子X
    tbitree.insert(tbitree.root->right->left, 'Y');     //插入J的右孩子Y
    tbitree.insert(tbitree.root->right, 'Z');           //插入I的右孩子Z

    //删除
//    ThreadBinaryNode<char> *p=tbitree.insert(tbitree.root->left, 'M', false);//插入B的右孩子M
    tbitree.remove(tbitree.root->left,false);         //删除B的右孩子X
    tbitree.remove(tbitree.root->left->right,false);  //删除D的右孩子W
    tbitree.remove(tbitree.root->left,false);         //删除B的右孩子D

/*
    //删除右孩子
//    char prelist[] = {'A','B','C',NULL,NULL,'X','D','E',NULL,NULL,'F',NULL,'G',NULL,NULL,'H','I','J',NULL,NULL,NULL,'K',NULL,NULL,'L'};                                                
    char prelist[] = "ABC\0\0XDE\0\0F\0G\0\0HIJ\0\0\0K\0\0L";      //可行                                          
    ThreadBinaryTree<char> tbitree(prelist, 25);
    tbitree.removeRightChild(tbitree.root->left->left);  //删除C的右孩子，没有，不删除
    tbitree.removeRightChild(tbitree.root->left);                //删除B的右孩子X，X是2度结点
    tbitree.removeRightChild(tbitree.root->left->right->right);  //删除F的右孩子G，G是只有右孩子的1度结点
    tbitree.removeRightChild(tbitree.root->left->right->right->right);   //删除H的右孩子K，K是0度结点
    tbitree.removeRightChild(tbitree.root->left->right->right);  //删除F的右孩子H，H是只有左孩子的1度结点

    //删除左孩子
    char prelist[] = "AB\0\0CXDE\0\0F\0G\0\0HIJ\0\0\0K\0\0L";      //可行                                          
    ThreadBinaryTree<char> tbitree(prelist, 25);
    tbitree.removeLeftChild(tbitree.root->left);           //删除B的左孩子，没有，不删除
    tbitree.removeLeftChild(tbitree.root->right);          //删除C的左孩子X，X是2度结点
    tbitree.removeLeftChild(tbitree.root->right->left);    //删除D的左孩子E，E是0度结点
    tbitree.removeLeftChild(tbitree.root->right);          //删除C的左孩子D，D是只有右孩子的1度结点
    tbitree.removeLeftChild(tbitree.root->right->left->right->right);  //删除H的左孩子I，I是只有左孩子的1度结点
/*
    tbitree.remove(tbitree.root->left);           //删除B的左孩子，没有，不删除
    tbitree.remove(tbitree.root->right);          //删除C的左孩子X，X是2度结点
    tbitree.remove(tbitree.root->right->left);    //删除D的左孩子E，E是0度结点
    tbitree.remove(tbitree.root->right);          //删除C的左孩子D，D是只有右孩子的1度结点
    tbitree.remove(tbitree.root->right->left->right->right);  //删除H的左孩子I，I是只有左孩子的1度结点

    tbitree.inOrder();                                //中根次序遍历
    tbitree.preOrder();                               //先根次序遍历
    tbitree.inOrderPrevious();                        //中根次序遍历（求前驱）
    tbitree.postOrderPrevious();                      //后根次序遍历（求前驱）
*/


//??
//    ThreadBinaryNode<char> *node = tbitree.root->left->right->right;    //
/*    ThreadBinaryNode<char> *node = tbitree.root->right->left->left;       
    ThreadBinaryNode<char> *parent = tbitree.getParent(node);
    cout<<node->data<<"的父母结点是";
    if (parent==NULL)
        cout<<"NULL"<<endl;
    else
        cout<<parent->data<<endl;
*/
//试题6.4
/*
#include "ThreadBinaryTree.h"                         //中序线索二叉树类

int main()
{
    char prelist[] = "PHEJLKACFG";                         //10
    char inlist[] = "EHLJPAFCKG";                          //后根ELJHFCAGKP
    ThreadBinaryTree<char> tbitree(prelist, inlist,10);    //以先根和中根序列创建中序线索二叉树
    tbitree.inOrder();                                     //中根次序遍历
    tbitree.preOrder();                                    //先根次序遍历
    tbitree.inOrderPrevious();                             //中根次序遍历（求前驱）
    tbitree.postOrderPrevious();                           //后根次序遍历（求前驱）

    system("pause");
    return 0;
}

/*
程序运行结果如下：
*/