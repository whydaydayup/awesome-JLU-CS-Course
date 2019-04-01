//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.5.1   二叉排序树

#include "BinaryTree.h"                                    //二叉链表的二叉树类（第6章）

//二叉排序树类，继承二叉树类，T必须重载==、!=、<运算符
template <class T>
class BinarySortTree : public BinaryTree<T>
{
  public:
    BinarySortTree(){}                                     //构造空二叉排序树，默认执行BinaryTree<T>()
    BinarySortTree(T values[], int n);                     //用values数组元素构造一棵二叉排序树
    ~BinarySortTree(){}                                    //析构函数，默认执行~BinaryTree<T>()，可省略

    T* search(T key);                                      //查找关键字为key元素，返回元素地址
    void insert(T key);                                    //插入key元素，不插入关键字重复元素
    void remove(T key);                                    //删除关键字为key结点
};

template <class T>
BinarySortTree<T>::BinarySortTree(T values[], int n)       //将values数组元素依次插入构造一棵二叉排序树
{                                                          //默认执行BinaryTree<T>()
    for (int i=0; i<n; i++)
        this->insert(values[i]);                           //将元素插入到当前的二叉排序树中
} 

//查找关键字为key元素，若查找成功，返回元素地址，否则返回NULL，T必须重载!=和<。非递归算法
//覆盖基类的search(T key)函数，返回值不同。
template <class T>
T* BinarySortTree<T>::search(T key)
{
    BinaryNode<T> *p=this->root;
    while (p!=NULL && p->data!=key)                        //查找经过一条从根到结点的路径，非递归，T必须重载!=
    {
//        cout<<p->data<<"? ";                             //显示查找经过的结点值，可省略
        if (key < p->data)                                 //若key较小，T必须重载<
            p = p->left;                                   //进入左子树
        else
            p = p->right;                                  //进入右子树
    }
    return p==NULL ? NULL : &p->data;
}

//插入key元素，不插入关键字重复元素，T必须重载==和<，非递归算法
//覆盖基类的insert(x)插入根和insert(p, x, leftChild)插入孩子结点函数，参数列表不同
template <class T>
void BinarySortTree<T>::insert(T key)
{
    if (this->root==NULL)
        this->root = new BinaryNode<T>(key);               //创建根结点
    BinaryNode<T> *p=this->root, *parent=NULL;
    while (p!=NULL)                                        //查找确定插入位置
    {
        if (p->data==key)                                  //查找成功，不插入关键字重复元素 
            return;   
        parent = p;
        if (key < p->data)
            p=p->left;
        else
            p=p->right;
    }    
    if (key < parent->data)                                //插入key结点作为parent的左/右孩子
        parent->left = new BinaryNode<T>(key);
    else
        parent->right = new BinaryNode<T>(key);
}  

//删除关键字为key元素结点。若查找不成功，则不删除，非递归算法
//覆盖基类的remove()删除根和remove(p,leftChild)删除子树函数，参数列表不同。
template <class T>
void BinarySortTree<T>::remove(T key)
{
    BinaryNode<T> *p=this->root, *parent=NULL;
    while (p!=NULL && p->data!=key)                        //查找关键字为key元素结点
    {
        parent = p;                                        //parent是p的父母结点
        if (key < p->data)
             p=p->left;
         else  p=p->right; 
    }
    if (p!=NULL && p->left!=NULL && p->right!=NULL)        //找到待删除结点p，p是2度结点
    {
        BinaryNode<T> *insucc = p->right;                  //寻找p在中根次序下的后继结点insucc
        parent = p;                
        while (insucc->left!=NULL)
        {
            parent = insucc;                
            insucc = insucc->left;
        }
        p->data = insucc->data;                  	       //用后继结点值替换p结点值
        p = insucc;                                        //之后，删除原p的后继结点insucc，转化为删除1、0度结点
    }
    if (p!=NULL && parent==NULL)                           //p是根结点，即p==root，删除根结点
    {
        if (p->left!=NULL)
            this->root = p->left;
        else  this->root = p->right;
        delete p;
        return;
    }
    if (p!=NULL && p==parent->left)                        //p是1度或叶子结点，p是parent的左孩子
        if (p->left!=NULL)
            parent->left = p->left;                        //以p的左子树顶替
        else  parent->left = p->right;
    if (p!=NULL && p==parent->right)                       //p是1度或叶子结点，p是parent的右孩子
        if (p->left!=NULL)
            parent->right = p->left;
        else  parent->right = p->right;
    delete p;
}    
    
    //不支持父类的insertRoot()、insertChild()和removeChild()方法，将其覆盖并抛出异常，省略


/*
    //第8章习题
/*    BinaryNode<T>* searchNode(T x);                        //查找值为x的结点
    BinaryNode<T>* insertNode(T x);                        //插入结点，递归算法
  private:
    BinaryNode<T>* insert(BinaryNode<T> *p, T x);          //将x插入到以p为根的子树中
    BinaryNode<T>* searchNode(BinaryNode<T> *p, T x);  

//第8章习题，递归算法，以下未调试
template <class T>
BinaryNode<T>*  BinarySortTree<T>::insertNode(T x)   //插入结点，不插入关键字重复的结点
{
    if (this->root==NULL)
        return this->root=new BinaryNode<T>(x);
    return insert(this->root, value);            //插入x到以root为根的二叉排序树中
}

template <class T>
BinaryNode<T>* BinarySortTree<T>::insert(BinaryNode<T> *p, T x)  //将x插入到以p为根的子树中
{
    BinaryNode<T>* q=NULL; 
    if (p->data==x)
        return NULL;                             //不插入关键字重复的结点 

    if (value < p->data)
        if (p->left==NULL)
        {
            q = new BinaryNode<T>(value);        //建立叶子结点作为p的左孩子
            p->left = q;
            return q;
        }
        else
            return insert(p->left, value);       //将value插入到p的左子树中
    else
        if (p->right==NULL)
        {
            q = new BinaryNode<T>(value);
            p->right = q;                        //建立叶子结点作为p的右孩子
            return q;
        }
        else
            return insert(p->right, value);      //将value插入到p的右子树中
}

//查找值为x的结点，若查找成功返回结点，否则返回NULL
template <class T>
BinaryNode<T>* BinarySortTree<T>::searchNode(T x)
{
    return searchNode(root, x);
}

//在以p为根的子树中查找值为x的结点，递归算法
template <class T>
BinaryNode<T>* BinarySortTree<T>::searchNode(BinaryNode<T> *p, T x)  
{
    if (p!=NULL && p->data!=x)
    {
        cout<<p->data<<"? ";
        if (x < p->data)
            return searchNode(p->left, x);       //在左子树中查找
        return searchNode(p->right, x);          //在右子树中查找
    }
    return p;                                    //若两个对象相等，查找成功
}


*/