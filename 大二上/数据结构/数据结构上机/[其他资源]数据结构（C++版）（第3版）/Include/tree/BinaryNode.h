//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.2.5   二叉树的二叉链表实现
//二叉树的二叉链表结点类

template <class T>
class BinaryNode                                           //二叉树的二叉链表结点类，T指定结点的元素类型
{
  public:
    T data;                                                //数据域，存储数据元素
    BinaryNode<T> *left,*right;                            //指针域，分别指向左、右孩子结点

    //构造结点，data指定元素，left、right指针分别指向左孩子和右孩子结点，默认空
    BinaryNode(T data, BinaryNode<T> *left=NULL, BinaryNode<T> *right=NULL)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    bool isLeaf()
    {
        return this->left==NULL && this->right==NULL;
    }
};
