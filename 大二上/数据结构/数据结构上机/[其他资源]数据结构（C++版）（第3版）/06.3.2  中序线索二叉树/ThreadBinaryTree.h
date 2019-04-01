//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.3   线索二叉树
//6.3.2   中序线索二叉树

#include <iostream>
using namespace std;
#include "ThreadNode.h"                                    //线索二叉树的二叉链表结点类

template <class T>
class ThreadBinaryTree                                     //中序线索二叉树类，T指定结点的元素类型
{
  public:
    ThreadNode<T> *root;                                   //指向根结点

    ThreadBinaryTree();                                    //构造空线索二叉树 
    ThreadBinaryTree(T prelist[], int n);                  //以标明空子树的先根序列构造一棵中序线索二叉树
    ~ThreadBinaryTree();                                   //析构函数

    bool empty();                                        //判断是否空二叉树
    void inOrder();                                        //中根次序遍历中序线索二叉树
//    friend ostream& operator<<<>(ostream& out, ThreadBinaryTree<T>&); //输出先根次序遍历序列（标明空子树）
    void preOrder();                                       //先根次序遍历中序线索二叉树
    void inOrderPrevious();                                //中根次序遍历（反序）
    void postOrderPrevious();                              //后根次序遍历（反序）

    ThreadNode<T>* parent(ThreadNode<T> *node);            //返回node结点的父母结点
    void insert(T x);                                      //插入根
    ThreadNode<T>* insert(ThreadNode<T> *parent, T x, bool leftChild=true); //插入孩子，默认插入左孩子
    void remove();                                         //删除根
    void remove(ThreadNode<T> *parent, bool leftChild);    //删除parent结点的左或右孩子结点

  private:
    ThreadNode<T>* create(T prelist[], int n, int &i);     //以标明空子树的先根次序遍历序列创建一棵子树
    void inThread(ThreadNode<T> *p, ThreadNode<T> *&front);  //中序线索化以p结点为根的子树
    ThreadNode<T>* inNext(ThreadNode<T> *p);               //返回p在中根次序下的后继结点
    ThreadNode<T>* preNext(ThreadNode<T> *p);              //返回p在先根次序下的后继结点
    ThreadNode<T>* inPrev(ThreadNode<T> *p);               //返回p在中根次序下的前驱结点
    ThreadNode<T>* postPrev(ThreadNode<T> *p);             //返回p在后根次序下的前驱结点
    void remove(ThreadNode<T> *p);                         //删除以p结点为根的子树

    ThreadBinaryTree(T prelist[], T inlist[], int n);      //以先根和中根序列构造中序线索二叉树
    ThreadNode<T>* create(T prelist[],  T inlist[], int preStart,int inStart, int n);//以先根和中根序列创建一棵子树，子树根结点是prelist[i]，返回根结点指针
    void removeRight(ThreadNode<T> *parent);               //删除parent结点的右孩子结点
    void removeLeft(ThreadNode<T> *parent);                //删除指定结点parent的左孩子结点
};

template <class T>
ThreadBinaryTree<T>::ThreadBinaryTree()                    //构造空线索二叉树
{
    this->root = NULL;
}

template <class T>
bool ThreadBinaryTree<T>::empty()                        //判断是否空二叉树
{
    return root==NULL;
}

template <class T>
ThreadBinaryTree<T>::ThreadBinaryTree(T prelist[], int n)//以标明空子树的先根序列构造一棵中序线索二叉树
{
    int i=0;
    this->root=create(prelist, n, i);
    ThreadNode<T>* front=NULL;
    inThread(this->root, front);                           //中序线索化二叉树
}

template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::create(T prelist[], int n, int &i)//以标明空子树的先根序列创建一棵子树，算法同BinaryTree
{
    ThreadNode<T> *p=NULL;
    if (i<n)
    {
        T elem = prelist[i];
        i++;
        if (elem!=NULL)
        {
            p = new ThreadNode<T>(elem);
            p->left = create(prelist, n, i);
            p->right = create(prelist, n, i);
        }
    }
    return p;
}

//2.  二叉树的中序线索化
//中序线索化以p结点为根的子树，front指向p的前驱结点 
template <class T>
void ThreadBinaryTree<T>::inThread(ThreadNode<T>* p, ThreadNode<T>* &front)
{
    if (p!=NULL)
    {
        inThread(p->left, front);                          //中序线索化p的左子树

        if (p->left==NULL)                                 //若p的左子树为空
        {
            p->ltag=1;                                     //设置左线索标记
            p->left = front;                               //设置p的left为指向前驱front的线索
        }
        if (p->right==NULL)                                //若p的右子树为空
            p->rtag=1;                                     //设置右线索标记
        if (front!=NULL && front->rtag) 
            front->right=p;                                //设置前驱front的right为指向后继p的线索
               
        front=p;
        inThread(p->right, front);                         //中序线索化p的右子树
    }
}

//3.  中根次序遍历中序线索二叉树
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::inNext(ThreadNode<T> *p) //返回p在中根次序下的后继结点
{                                     
    if (p->rtag==1)                                        //若右子树为空
        p=p->right;                                        //则p->right是指向p后继结点的线索
    else
    {
        p=p->right;                                        //进入右子树
        while (p->ltag==0)                                 //寻找最左边的后代结点
            p=p->left;
    }
    return p;
}

template <class T>
void ThreadBinaryTree<T>::inOrder()                        //中根次序遍历中序线索二叉树，非递归算法
{
    cout<<"中根次序遍历中序线索二叉树:  ";   
    ThreadNode<T> *p=this->root;
    while (p!=NULL && p->ltag==0)                          //寻找根的最左边的后代结点，即第一个访问结点
        p=p->left;  
    while (p!=NULL)
    {
        cout<<p->data<<" ";
        p=inNext(p);                                       //返回p在中根次序下的后继结点
    }
    cout<<endl;
}    

//4.  先根次序遍历中序线索二叉树
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::preNext(ThreadNode<T> *p) //返回p在先根次序下的后继结点
{
    if (p->ltag==0)                                        //若左子树非空
        p=p->left;                                         //左孩子是p的后继结点
    else                                                   //否则，后继是右兄弟或某个中序祖先的右孩子
    {
        while (p->rtag==1 && p->right!=NULL)               //沿着右线索向上，寻找某个中序祖先
            p=p->right; 
        p=p->right;                                        //后继是其某个中序祖先的右孩子
    }
    return p;
}

template <class T>
void ThreadBinaryTree<T>::preOrder()             //先根次序遍历中序线索二叉树，非递归算法
{
    cout<<"先根次序遍历中序线索二叉树:  ";   
    ThreadNode<T> *p=this->root;
    while (p!=NULL)
    {
        cout<<p->data<<" ";
        p=preNext(p);                            //返回p在先根次序下的后继结点
    }
    cout<<endl;
}

//第6章习题
//以先根和中根序列构造中序线索二叉树，n指定序列长度
template <class T>
ThreadBinaryTree<T>::ThreadBinaryTree(T prelist[], T inlist[], int n)
{                                                
    root = create(prelist, inlist, 0, 0, n);
    ThreadNode<T>* front=NULL;
    inThread(root, front);                                 //中序线索化二叉树
}
    //以先根和中根序列创建一棵子树，子树根结点是prelist[i]，返回根结点指针
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::create(T prelist[],  T inlist[], int preStart,int inStart, int n)
{
    ThreadNode<T> *p=NULL;
    if (n>0)
    {
        T elem=prelist[preStart];                          //根结点值
        p = new ThreadNode<T>(elem);                       //创建结点
        int i=0;
        while (i<n && elem!=inlist[inStart+i])             //在中根序列中查找根值所在位置
            i++;
        p->left = create(prelist, inlist, preStart+1, inStart, i);           //创建左子树
        p->right = create(prelist, inlist, preStart+i+1, inStart+i+1, n-1-i);//创建右子树
    }
    return p;
}

//【思考题6-4】 求p结点在中根次序下的前驱结点，按中根次序遍历中序线索二叉树。
    //返回p在中根次序下的前驱结点
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::inPrev(ThreadNode<T> *p)
{
    if (p->ltag==1)
        p=p->left;                                         //若左子树为空，p->left就是指向p前驱结点的线索
    else                                                   //若左子树非空
    {
        p=p->left;                                         //进入左子树
        while (p->rtag==0)                                 //找到最右边的后代结点
            p=p->right;
    }
    return p;
}

template <class T>
void ThreadBinaryTree<T>::inOrderPrevious()                //中根次序（反序）遍历中序线索二叉树，非递归算法
{
    cout<<"中根次序遍历（反序）中序线索二叉树:  ";   
    ThreadNode<T> *p=this->root;
    while (p!=NULL && p->rtag==0)                          //寻找根的最右边的后代结点
        p=p->right;
    while (p!=NULL)
    {
        cout<<p->data<<" ";
        p=inPrev(p);                                       //返回p在中根次序下的前驱结点
    }
    cout<<endl;
}    

//【思考题6-5】求p结点在后根次序下的前驱结点，按后根次序遍历中序线索二叉树。
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::postPrev(ThreadNode<T> *p)   //返回p在后根次序下的前驱结点
{
    if (p->rtag==0)
        p=p->right;                                        //右孩子是p的前驱结点
    else                                                   //否则，前驱是某个中序祖先的左孩子
    {
        while (p->ltag==1 && p->left!=NULL)                //寻找某个中序祖先
            p=p->left;
        p=p->left;                                         //左孩子是前驱结点
    }
    return p;
}

template <class T>
void ThreadBinaryTree<T>::postOrderPrevious()              //后根次序（反序）遍历中序线索二叉树，非递归算法
{
    cout<<"后根次序遍历（反序）中序线索二叉树:  ";   
    ThreadNode<T> *p=this->root;
    while (p!=NULL)
    {
        cout<<p->data<<" ";
        p=postPrev(p);                                     //返回p在后根次序下的前驱结点
    }
    cout<<endl;
}
    
//5.  析构函数
template <class T>
ThreadBinaryTree<T>::~ThreadBinaryTree()                   //析构函数
{
    cout<<"撤销中序线索二叉树: ";
    remove(this->root);
    cout<<endl;
}

//撤销以p结点为根的子树，后根次序遍历的递归算法
template <class T>
void ThreadBinaryTree<T>::remove(ThreadNode<T> *p)
{
    if (p!=NULL)
    {
        if (p->ltag==0)
            remove(p->left);
        if (p->rtag==0)
            remove(p->right);
        cout<<p->data<<" ";                                //显示撤销结点的次序
        delete p;
    }
}

//实验6
//6. 求父母结点

//7. 插入结点
template <class T>
void ThreadBinaryTree<T>::insert(T x)                      //插入作为根结点
{
    if (root==NULL)
        root=new ThreadNode<T>(x,NULL,NULL,1,1);
    else
    {
        ThreadNode<T> *p=root;
        while (p!=NULL && p->rtag==0)                      //寻找原根的最右边子孙结点p，即最后访问结点
            p=p->right;
        root=new ThreadNode<T>(x,root,NULL,0,1);
        p->right=root;                                     //修改p的后继线索
    }
}

    //插入x作为parent结点的孩子结点，若leftChild为true（默认），插入左孩子，否则插入右孩子，返回插入的孩子结点
template <class T>
ThreadNode<T>* ThreadBinaryTree<T>::insert(ThreadNode<T> *parent, T x, bool leftChild)
{
    ThreadNode<T> *q=NULL;
    if (leftChild)                                          //插入左孩子
    {
        q=new ThreadNode<T>(x, p->left, p, p->ltag, 1);
        p->left=q;
        p->ltag = 0;
        if (q->ltag==0)
        {
            ThreadNode<T> *prev=inPrev(q);                 //prev是q在中根次序下的前驱
            prev->right=q;                                 //修改前驱结点prev的后继线索
        }
    }
    else                                                   //插入右孩子
    {
        q=new ThreadNode<T>(value, p, p->right,1, p->rtag);
        p->right=q;
        p->rtag=0;
        if (q->rtag==0)
        {
            ThreadNode<T> *succ=inNext(q);                 //succ是q在中根次序下的后继
            succ->left=q;                                  //修改后继结点succ的前驱线索
        }
    }
    return q;
}

//8.删除结点
    //删除指定结点parent结点的左或右孩子结点，若leftChild为true，删除左孩子，否则删除右孩子
    //算法左右各分4种情况
template <class T>
void ThreadBinaryTree<T>::remove(ThreadNode<T> *parent, bool leftChild)
{
    if (root==NULL || parent==NULL || leftChild && parent->ltag==1 || !leftChild && parent->rtag==1)
        return;
    ThreadNode<T> *q=NULL;
    if (leftChild && parent->ltag==0)                      //删除p的非空左孩子结点
    {
        q=parent->left;                                    //q是待删除结点
        if (q->ltag==1 && q->rtag==1)                      //q是叶子结点
        {
            parent->left = q->left;
            parent->ltag=1;
        }
        else if (q->ltag==0 && q->rtag==1)                 //q是1度结点，只有左孩子
        {
            parent->left = q->left;                        //用q的左孩子顶替q，p->rtag未变
            inPrev(q)->right=q->right;                     //修改q前驱结点inPrev(q)的后继线索
        }
        else if (q->ltag==1 && q->rtag==0)                 //q是1度结点，只有右孩子
        {
            parent->left = q->right;                       //用q的右孩子顶替q，p->rtag未变
            inNext(q)->left=q->left;                       //修改q后继结点inNext(q)的前驱线索
        }
        else if (q->ltag==0 && q->rtag==0)                 //q是2度结点，有左孩子也有右孩子
        {
            parent->left = q->left;                        //用q的左孩子顶替q，p->rtag未变
            ThreadNode<T> *prev=inPrev(q);                 //prev是q在中根次序下的前驱
            prev->right=q->right;                          //修改q前驱结点prev的后继线索
            prev->rtag=0;
            inNext(q)->left=prev;                          //修改q后继结点inNext(q)的前驱线索
        }
    }
    else if (!leftChild && p->rtag==0)                     //删除p的非空右孩子结点q
    {
        q=parent->right;                                   //q是待删除结点
        if (q->ltag==1 && q->rtag==1)                      //q是叶子结点
        {
            parent->right = q->right;
            parent->rtag=1;
        }
        else if (q->ltag==0 && q->rtag==1)                 //q是1度结点，只有左孩子
        {
            parent->right = q->left;                       //用q的左孩子顶替q，p->rtag未变
            inPrev(q)->right=q->right;                     //修改q前驱结点inPrev(q)的后继线索
        }
        else if (q->ltag==1 && q->rtag==0)                 //q是1度结点，只有右孩子
        {
            parent->right = q->right;                      //用q的右孩子顶替q，p->rtag未变
            inNext(q)->left=p;                             //修改q后继结点inNext(q)的前驱线索
        }
        else if (q->ltag==0 && q->rtag==0)                 //q是2度结点，有左孩子也有右孩子
        {
            parent->right = q->left;                       //用q的左孩子顶替q，p->rtag未变
            ThreadNode<T> *prev=inPrev(q);                 //prev是q在中根次序下的前驱
            prev->right=q->right;                          //修改q前驱结点prev的后继线索
            prev->rtag=0;
            inNext(q)->left=prev;                          //修改q后继结点inNext(q)的前驱线索
        }
    }
    delete q;
}

    //删除指定结点parent的右孩子结点，合并4种情况，叶算法
template <class T>
void ThreadBinaryTree<T>::removeRight(ThreadNode<T> *parent)
{
    if (root==NULL || parent==NULL || parent->rtag==1)     //若parent无右孩子，则不删除
        return;
    ThreadNode<T> *q=p->right;                             //q为待删除结点
    if (q->ltag==0)                                        //q有左孩子
    {
        parent->right = q->left;                           //用q的左孩子顶替q，p->rtag未变
        ThreadNode<T> *prev=inPrev(q);                     //prev指向q在中根次序下的前驱
        prev->right=q->right;                              //修改前驱结点prev的后继线索
        prev->rtag=q->rtag;
        if (q->rtag==0)                                    //q也有右孩子，q是2度结点
            inNext(q)->left=prev;                          //修改q后继结点inNext(q)的前驱线索
    }
    else                                                   //q或是只有右孩子的1度结点，或是叶子结点
    {
        parent->right = q->right;                          //用q的右孩子（或后继线索）顶替q
        parent->rtag = q->rtag;
        if (q->rtag==0)                                    //q有右孩子没有左孩子
            inNext(q)->left=parent;                        //修改q后继结点inNext(q)的前驱线索
    }
    delete q;
}

    //删除指定结点p的左孩子结点
template <class T>
void ThreadBinaryTree<T>::removeLeft(ThreadNode<T> *parent)
{
    if (root==NULL || parent==NULL || p->ltag==1)          //若p无左孩子，则不删除
        return;
    ThreadNode<T> *q=parent->left;                         //q为待删除结点
    if (q->ltag==0)                                        //q有左孩子
    {
        parent->left = q->left;                            //用q的左孩子顶替q，parent->rtag未变
        ThreadNode<T> *prev=inPrev(q);                     //prev指向q在中根次序下的前驱
        prev->right=q->right;                              //修改前驱结点prev的后继线索
        prev->rtag=q->rtag;
        if (q->rtag==0)                                    //q也有右孩子，q是2度结点
            inNext(q)->left=prev;                          //修改q后继结点inNext(q)的前驱线索
    }
    else                                                   //q或是只有右孩子的1度结点，或是叶子结点
    {
        if (q->rtag==1)                                    //q是叶子结点
        {
            parent->left = q->left;                        //用q的前驱线索顶替q
            parent->ltag = 1;
        }
        else                                               //q是只有右孩子的1度结点
        {
            parent->left = q->right;                       //用q的右孩子顶替q
            inNext(q)->left=q->left;                       //修改q后继结点inNext(q)的前驱线索
        }
    }
    delete q;
}

