//《数据结构（C++版）（第3版）》 作者：叶核亚
//06.2.5  二叉树 思考题6-2 基于遍历的操作
//第2版【例6.2】  输出二叉树中指定结点的所有祖先结点。
//【实验6-1】实现BinaryTree类以先根和中根序列构造二叉树的操作。
//【实验6-1】  输出一棵二叉树的所有叶子结点及叶子结点个数。

#include "BinaryTree_实验6-1.h"                            //二叉树类

template <class T>
void printAncestors(BinaryTree<T> &bitree, T key)          //输出bitree二叉树中关键字为key结点的所有祖先结点
{
    BinaryNode<T> *find = bitree.search(key);              //查找
    if (find==NULL)
        cout<<"未找到"<<value<<endl;
    else
    {
        BinaryNode<T> *parent = bitree.parent(find);
        cout<<key<<"的祖先结点是";
        while (parent!=NULL)
        {
            cout<<parent->data<<" ";
            parent = bitree.parent(parent);
        }
        cout<<endl;
    }
}

int main()
{
    char preorder[] = "ABDGCEFH";                          //图6.18（a）所示二叉树的先根序列和中根序列
    char inorder[] = "DGBAECHF";
    BinaryTree<char> bitree(preorder, inorder, 8);         //以先根序列和中根序列构造二叉树

    cout<<bitree;                                          //输出先根次序遍历序列（标明空子树）
    bitree.inOrder();
    bitree.postOrder();
    cout<<"二叉树结点个数："<<bitree.count()<<endl;
    cout<<"二叉树高度："<<bitree.height()<<endl;
    cout<<"叶子结点（"<<bitree.countLeaf()<<"个）：";
    bitree.leaf();
    cout<<endl;

    printAncestors(bitree, 'H');                           //输出bitree二叉树中关键字为key结点的所有祖先结点
    bitree.levelOrder();                                   //按层次遍历二叉树
    cout<<endl;

    char prelist2[] = {'A','B',NULL,NULL,'C'};
    BinaryTree<char> bitree2(prelist2, 5);
    find = bitree2.search('A');
    cout<<"插入Z作为 "<<find->data<<" 的左孩子\n";
    BinaryNode<char>*q=bitree2.insert(find, 'Z');
    cout<<bitree2;
    bitree2.inOrder();
    bitree2.postOrder();
    cout<<"二叉树结点个数："<<bitree2.count()<<endl;
    cout<<"二叉树高度："<<bitree2.height()<<endl;

    cout<<"删除"<<find->data<<" 的右子树\n";
    bitree2.remove(find, false);
    cout<<bitree2;
    bitree2.inOrder();
    bitree2.postOrder();

    system("pause");
    return 0;
}

/*
程序运行结果如下：
先根次序遍历二叉树:  A B D G C E F H 
中根次序遍历二叉树:  D G B A E C H F 
后根次序遍历二叉树:  G D B E H F C A 
二叉树结点个数：8
二叉树高度：4
H的祖先结点是F C A 
层次遍历：  A B C D E F G H 

插入Z作为 A 的左孩子
先根次序遍历二叉树:  A Z B C 
中根次序遍历二叉树:  B Z A C 
后根次序遍历二叉树:  B Z C A 
二叉树结点个数：4
二叉树高度：3
删除A 的右子树
C 先根次序遍历二叉树:  A Z B 
中根次序遍历二叉树:  B Z A 
后根次序遍历二叉树:  B Z A 
撤销二叉树: B Z A 
撤销二叉树: G D B E H F C A 


*/
