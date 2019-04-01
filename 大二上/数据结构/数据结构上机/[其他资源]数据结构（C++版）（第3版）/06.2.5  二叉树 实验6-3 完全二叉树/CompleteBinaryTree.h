//《数据结构（C++版）（第3版）》 作者：叶核亚
//【实验6-3】二叉链表表示的完全二叉树类。

#include "BinaryTree.h"                                    //二叉树类

template <class T>
class CompleteBinaryTree : public BinaryTree <T>           //二叉链表表示的完全二叉树类，继承二叉树类
{
  private:
    BinaryNode<T>* create(T levellist[], int n, int i);    //创建以levellist[i]为根的一棵子树

  public:
    CompleteBinaryTree(T levellist[], int n);              //以层次序列构造完全二叉树


};
 
//以完全二叉树的层次序列构造完全二叉树，levellist指定层次序列
template <class T>
CompleteBinaryTree<T>::CompleteBinaryTree(T levellist[], int n)
{
    this->root = create(levellist, n, 0);                  //创建以levellist[0]为根的一棵二叉树
}

//创建以levellist[i]为根的一棵子树
template <class T>
BinaryNode<T>* CompleteBinaryTree<T>::create(T levellist[], int n, int i)
{
    BinaryNode<T> *p = NULL;
    if (i<n)
    {
        p = new BinaryNode<T>(levellist[i]);
        p->left = create(levellist, n, 2*i+1);
        p->right = create(levellist, n, 2*i+2);
    }
    return p;
}
