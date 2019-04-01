//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.2.5   二叉树的二叉链表实现
//二叉树类

#include <iostream>
using namespace std;

#include "BinaryNode.h"                                    //二叉树的二叉链表结点类
#include "MyString.h"                                      //字符串类（第3章）
#include "SeqStack.h"                                      //顺序栈（第4章）
//#include "LinkedStack.h"                                   //链式栈（第4章）
#include "SeqQueue.h"                                      //顺序循环队列（第4章）
#include "LinkedQueue.h"                                   //链式队列（第4章）

template <class T>
class BinaryTree                                           //二叉树类
{
  public:
    BinaryNode<T> *root;                                   //指向根结点

    BinaryTree();                                          //构造空二叉树 
    BinaryTree(T prelist[], int n);                        //以标明空子树的先根序列构造一棵二叉树
    BinaryTree(MyString genlist);                          //以广义表表示构造二叉树
    ~BinaryTree();                                         //析构函数

    bool empty();                                          //判断是否空二叉树
    friend ostream& operator<<<>(ostream& out, BinaryTree<T>&); //输出先根次序遍历序列（标明空子树）
    void inOrder();                                        //输出中根次序遍历序列
    void postOrder();                                      //输出后根次序遍历序列

    BinaryNode<T>* insert(T x);                            //插入元素x作为根结点
    BinaryNode<T>* insert(BinaryNode<T> *p, T x, bool leftChild=true); //插入x作为p结点的左或右孩子
    void remove(BinaryNode<T> *p, bool leftChild);         //删除p结点的左或右子树
    void remove();                                         //删除根结点，删除二叉树
    void printGenList();                                   //输出二叉树的广义表表示
    void inOrderTraverse();                                //中根次序遍历二叉树的非递归算法
    void levelOrder();                                     //输出二叉树的层次遍历序列

  private:
    BinaryNode<T>* create(T prelist[], int n, int &i);     //以标明空子树的先根遍历序列创建子树
    BinaryNode<T>* create(MyString &genlist, int &i);      //以广义表表示创建一棵子树
    void preOrder(BinaryNode<T> *p);                       //先根次序遍历以p结点为根的子树
    void inOrder(BinaryNode<T> *p);                        //中根次序遍历以p结点为根的子树
    void postOrder(BinaryNode<T> *p);                      //后根次序遍历以p结点为根的子树
    void remove(BinaryNode<T> *p);                         //删除以p结点为根的子树
    void printGenList(BinaryNode<T> *p);                   //输出以p结点为根的子树的广义表表示
    //以上ADT，教材第157页


    //以下第6章实验题6-1
  public:
    BinaryTree(T prelist[], T inlist[], int n);            //以先根和中根序列构造二叉树

    int count();                                           //返回二叉树的结点个数
    int height();                                          //返回二叉树的高度
    BinaryNode<T>* search(T key);                          //查找先根次序遍历首次出现的关键字为key结点，T必须重载==运算
    BinaryNode<T>* parent(BinaryNode<T> *node);            //返回node结点的父母结点

    void leaf();                                           //遍历输出叶子结点
    int leafCount();                                       //返回二叉树的叶子结点数
    bool replace(T key, T x);                              //将首次出现的关键字为key结点值替换为x
    void replaceAll(T key, T x);                           //将所有关键字为key的结点全部替换为x

    int operator==(BinaryTree<T> &bitree);                 //重载==运算符，比较两棵二叉树是否相等，T必须重载==运算
    BinaryTree(BinaryTree<T> &bitree);                     //拷贝构造函数，深拷贝
    BinaryTree<T>& operator=(BinaryTree<T> &bitree);       //重载=赋值运算符，深拷贝
    void preOrderTraverse();                               //先根次序遍历二叉树的非递归算法
    int getLevel(T x);                                     //返回x结点所在的层次
    bool isCompleteBinaryTree();                           //判断是否完全二叉树
    //？？
    void traverseGenList();                                //以广义表表示输出二叉树，使用栈的非递归遍历算法
    bool isSorted();                                       //判断一棵二叉树是否为二叉排序树

  private:
    BinaryNode<T>* create(T prelist[], T inlist[], int preStart, int inStart, int n);  //以先根和中根序列创建一棵子树

    int count(BinaryNode<T> *p);                           //返回以p结点为根的子树结点个数
    int height(BinaryNode<T> *p);                          //返回以p结点为根的子树高度
    BinaryNode<T>* search(BinaryNode<T> *p, T key);        //在以p为根的子树中查找首次出现的值为key的结点
    BinaryNode<T>* parent(BinaryNode<T> *p, BinaryNode<T> *node);

    void leaf(BinaryNode<T> *p);                           //输出以p结点为根的子树的所有叶子结点
    int leafCount(BinaryNode<T> *p);                       //返回以p结点为根的子树的叶子结点个数
    void replaceAll(BinaryNode<T> *p, T key, T x);         //在以p为根的子树中实现全部替换
    bool equals(BinaryNode<T> *p, BinaryNode<T> *q);       //判断以p和q结点为根的两棵子树是否相等
    BinaryNode<T>* copy(BinaryNode<T> *p);                 //复制以p根的子二叉树
    int getLevel(BinaryNode<T> *p, int i, T x);            //在以p结点（层次为i）为根的子树中求x结点所在的层次


    //第8章习题
    bool isSorted(BinaryNode<T>* p);             //判断一棵二叉树是否为二叉排序树

};

template <class T>
BinaryTree<T>::BinaryTree()                                //构造空二叉树
{
    this->root = NULL;
}

template <class T>
bool BinaryTree<T>::empty()                              //判断是否空二叉树
{
    return this->root==NULL;
}

//3.  二叉树的先根、中根和后根次序遍历算法
template <class T>
ostream& operator<<<>(ostream& out, BinaryTree<T> &btree)  //输出先根次序遍历序列（标明空子树）
{
    out<<"先根次序遍历二叉树:  ";   
    btree.preOrder(btree.root);                            //调用先根次序遍历二叉树的递归函数
    out<<endl; 
    return out;
}
template <class T>
void BinaryTree<T>::preOrder(BinaryNode<T> *p)             //先根次序遍历以p结点为根的子树，递归函数
{
    if (p==NULL)                                           //若二叉树空
        cout<<"∧";                                        //输出空结点标记
    else
    {
        cout<<p->data<<" ";                                //输出当前结点元素
        preOrder(p->left);                                 //按先根次序遍历p的左子树，递归调用
        preOrder(p->right);                                //按先根次序遍历p的右子树，递归调用
    }
}

template <class T>
void BinaryTree<T>::inOrder()                              //中根次序遍历二叉树
{
    cout<<"中根次序遍历二叉树:  ";   
    this->inOrder(root);                                   //调用中根次序遍历二叉树的递归函数
    cout<<endl;   
}
template <class T>
void BinaryTree<T>::inOrder(BinaryNode<T> *p)              //中根次序遍历以p结点为根的子树，递归函数
{
    if (p!=NULL)
    {
        inOrder(p->left);                                  //按中根次序遍历p的左子树，递归调用
        cout<<p->data<<" ";
        inOrder(p->right);                                 //按中根次序遍历p的右子树，递归调用
    }
}

template <class T>
void BinaryTree<T>::postOrder()                            //后根次序遍历二叉树
{
    cout<<"后根次序遍历二叉树:  ";   
    this->postOrder(root);                                 //调用后根次序遍历二叉树的递归函数
    cout<<endl;   
}
template <class T>
void BinaryTree<T>::postOrder(BinaryNode<T> *p)            //后根次序遍历以p结点为根的子树，递归函数
{
    if (p!=NULL)
    {
        postOrder(p->left);
        postOrder(p->right);
        cout<<p->data<<" ";
    }
}


//4. 二叉树插入结点
//插入元素x作为根结点，原根结点作为其左孩子，返回插入结点地址。
template <class T>
BinaryNode<T>* BinaryTree<T>::insert(T x)
{
    return this->root = new BinaryNode<T>(x, this->root, NULL);
}
//    void insertRoot(T x);             	//不能声明如此，因为，子类二叉排序树要覆盖两个insert()

//插入x作为parent结点的左/右孩子，原parent的左/右孩子作为x结点的左/右孩子；返回插入结点地址；
//若parent为空，则不插入；leftChild指定左或右孩子，取值为true（左孩子，默认）、false（右孩子）
template <class T>
BinaryNode<T>* BinaryTree<T>::insert(BinaryNode<T> *parent, T x, bool leftChild)
{
    if (parent==NULL)
        return NULL;
    if (leftChild)                                         //插入x结点作为parent的左/右孩子
        return parent->left = new BinaryNode<T>(x, parent->left, NULL);
    return parent->right = new BinaryNode<T>(x, NULL, parent->right);
}    

//5. 删除子树
template <class T>
BinaryTree<T>::~BinaryTree()                               //析构函数
{
    cout<<"析构二叉树: ";
    this->remove(this->root);
    cout<<endl;
}
template <class T>
void BinaryTree<T>::remove()                               //删除根结点，删除二叉树
{
    this->remove(this->root);
}

//删除parent结点的左或右子树，若leftChild为true，删除左子树，否则删除右子树。
template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *parent, bool leftChild)
{
    if (parent!=NULL)
        if (leftChild)
        {
            remove(parent->left);                          //删除左子树
            parent->left = NULL;
        }
        else
        {
            remove(parent->right);                         //删除右子树
            parent->right = NULL;
        }
}

template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *p)               //删除以p结点为根的子树，后根次序遍历
{
    if (p!=NULL)
    {
        remove(p->left);
        remove(p->right);
        cout<<p->data<<" ";                                //显示删除结点的次序
        delete p;                                          //释放结点占用的存储空间
    }
}

//6. 构造二叉树

//构造二叉树，prelist数组指定二叉树标明空子树的先根遍历序列，n指定序列长度
template <class T>
BinaryTree<T>::BinaryTree(T prelist[], int n)
{
    int i=0;
    this->root = this->create(prelist, n, i);
}
//以标明空子树的先根序列（从i开始）创建一棵以prelist[i]为根的子树，返回根结点，递归算法
template <class T>
BinaryNode<T>* BinaryTree<T>::create(T prelist[], int n, int &i)  
{
    BinaryNode<T> *p=NULL;
    if (i<n)
    {
        T elem = prelist[i];
        i++;
        if (elem!=NULL)                                    //不能elem!='^'，因为T不一定是char
        {
            p = new BinaryNode<T>(elem);                   //创建结点
            p->left = create(prelist, n, i);               //创建左子树，递归调用
            p->right = create(prelist, n, i);              //创建右子树，递归调用
        }
    }
    return p;
}
//【例6.1】二叉树的构造、遍历及插入。


//【例6.2】 二叉树的广义表表示。

template <class T>
void BinaryTree<T>::printGenList()                         //输出二叉树的广义表表示字符串
{
    this->printGenList(root);
    cout<<endl;
}
//输出以p结点为根的一棵子树的广义表表示字符串，先根次序遍历，递归算法
template <class T>
void BinaryTree<T>::printGenList(BinaryNode<T> *p)
{
    if (p==NULL)
        cout<<"∧";                                        //输出空子树表示
    else
    {
        cout<<p->data;
        if (p->left!=NULL || p->right!=NULL)               //非叶子结点
        {
            cout<<"(";
            printGenList(p->left);                         //输出左子树，递归调用
            cout<<",";
            printGenList(p->right);                        //输出右子树，递归调用
            cout<<")";
        }
    }
}

//以广义表表示构造二叉树，genlist指定二叉树广义表表示字符串
//T必须有MyString类型的构造函数
template <class T>
BinaryTree<T>::BinaryTree(MyString genlist)
{
    int i=0;
    this->root = this->create(genlist, i);
}

//以广义表表示字符串（从i开始）创建一棵以genlist[i]为根的子树，返回根结点，递归算法
template <class T>
BinaryNode<T>* BinaryTree<T>::create(MyString &genlist, int &i)  
{
    if (genlist[i]=='^')                                   //跳过'^'
    {
        i++;
        return NULL;
    }
    int n=0;
    char ch;
    while (i<genlist.count() && (ch=genlist[i+n]) && ch!='(' && ch!=',' && ch!=')')
        n++;
    MyString str=genlist.substring(i,n);                   //获得从i开始长度为n的子串
    i+=n;
    BinaryNode<T> *p = new BinaryNode<T>(str);             //创建叶子结点
    if (genlist[i]=='(')
    {
        i++;                                               //跳过'('
        p->left = create(genlist, i);                      //创建左子树
        i++;                                               //跳过','
        p->right = create(genlist, i);                     //创建右子树
        i++;                                               //跳过')'
    }
    return p;
}

//7.  二叉树遍历的非递归算法
template <class T>
void BinaryTree<T>::preOrderTraverse()                     //先根次序遍历二叉树的非递归算法
{
    cout<<"先根次序遍历（非递归）：  ";
    SeqStack<BinaryNode<T>*> stack;                        //创建空栈，元素为结点地址
    BinaryNode<T> *p = this->root;
    while (p!=NULL || !stack.empty())                    //p非空或栈非空时
        if (p!=NULL)
        {
            cout<<p->data<<" ";                            //访问结点
            stack.push(p);                                 //p结点地址入栈
            p = p->left;                                   //进入左子树
        }
        else                                               //p为空且栈非空时
        {
            p = stack.pop();                               //p指向出栈结点
            p = p->right;                                  //进入右子树
        }
    cout<<endl;
}    

template <class T>
void BinaryTree<T>::inOrderTraverse()                      //中根次序遍历二叉树的非递归算法
{
    cout<<"中根次序遍历（非递归）：  ";
    SeqStack<BinaryNode<T>*> stack;                        //创建空栈，元素为结点地址
//    LinkedStack<BinaryNode<T>*> stack;                     //创建一个空栈
    BinaryNode<T> *p = this->root;
    while (p!=NULL || !stack.empty())                    //p非空或栈非空时
        if (p!=NULL)
        {
            stack.push(p);                                 //p结点入栈
            p = p->left;                                   //进入左子树
        }
        else                                               //p为空且栈非空时
        {
            p = stack.pop();                               //p指向出栈结点
            cout<<p->data<<" ";                            //访问结点
            p = p->right;                                  //进入右子树
        }
    cout<<endl;
}    

//8.   二叉树的层次遍历
template <class T>
void BinaryTree<T>::levelOrder()                           //按层次遍历二叉树
{ 
    cout<<"层次遍历：  ";
//    SeqQueue<BinaryNode<T>*> que;                //创建一个空队列
    LinkedQueue<BinaryNode<T>*> que;                       //创建一个空队列
    BinaryNode<T> *p = this->root;                         //根结点没有入队
    while (p!=NULL)
    {
        cout<<p->data<<" ";
        if (p->left!=NULL)    
            que.enqueue(p->left);                          //p的左孩子结点入队
        if (p->right!=NULL)
            que.enqueue(p->right);                         //p的右孩子结点入队
        p = que.empty() ? NULL : que.dequeue();            //p指向出队结点或NULL
    }
    cout<<endl;
}

//以下实验6-1
#include "BinaryTree.h"                                    //二叉树类

//构造二叉树，prelist、inlist数组分别指定先根和中根遍历序列，n指定序列长度
template <class T>
BinaryTree<T>::BinaryTree(T prelist[], T inlist[], int n)
{
    this->root = this->create(prelist, inlist, 0, 0, n);
}
//以先根和中根序列构造子二叉树，先根子序列从prelist数组的preStart开始，子树根结点是
//prelist[preStart]；中根子序列从inlist数组的inStart开始，n指定子序列长度；返回根结点地址
template <class T>
BinaryNode<T>* BinaryTree<T>::create(T prelist[],  T inlist[], int preStart,int inStart, int n)
{
    BinaryNode<T> *p=NULL;
    if (n>0)
    {
        T elem=prelist[preStart];                          //根结点值
        p = new BinaryNode<T>(elem);                       //创建结点
        int i=0;
        while (i<n && elem!=inlist[inStart+i])             //在中根序列中查找根值所在位置
            i++;
        p->left = create(prelist, inlist, preStart+1, inStart, i);           //创建左子树
        p->right = create(prelist, inlist, preStart+i+1, inStart+i+1, n-1-i);//创建右子树
    }
    return p;
}

//基于遍历的操作
template <class T>
int BinaryTree<T>::count()                                 //返回二叉树的结点个数
{
    return this->count(this->root);
}

template <class T>
int BinaryTree<T>::count(BinaryNode<T> *p)                 //返回以p结点为根的子树结点个数
{
    if (p==NULL)
        return 0;
    return 1+count(p->left)+count(p->right);
}

template <class T>
int BinaryTree<T>::height()                                //返回二叉树的高度
{
   return this->height(root);
}

template <class T>
int BinaryTree<T>::height(BinaryNode<T> *p)                //返回以p结点为根的子树高度，后根次序遍历
{
   if (p==NULL)
       return 0;
   int lh = height(p->left);                               //返回左子树的高度
   int rh = height(p->right);                              //返回右子树的高度
   return (lh>=rh) ? lh+1 : rh+1;                          //返回两棵子树高度较大值加1
}

template <class T>
BinaryNode<T>* BinaryTree<T>::search(T key)                //查找首次出现的关键字为key结点
{
    return this->search(this->root, key);
}

//在以p结点为根的子树中查找首次出现的关键字为key结点，返回结点地址，若未找到返回NULL
//T必须重载==。先根次序遍历算法
template <class T>
BinaryNode<T>* BinaryTree<T>::search(BinaryNode<T> *p, T key)
{
    BinaryNode<T> *find=NULL;                    //记载查找结果
    if (p!=NULL)
    {
        if (p->data==key)                        //T必须重载==
            return p;                            //查找成功，返回结点地址
        find = search(p->left, key);             //在左子树中查找，find指向找到结点，递归调用
        if (find==NULL)                          //若在左子树中未找到
            find = search(p->right, key);        //则继续在右子树中查找，递归调用
    }
    return find;                                 //返回查找结果
}

//返回node结点的父母结点地址，若空树、未找到或node为根，返回NULL
template <class T>
BinaryNode<T>* BinaryTree<T>::parent(BinaryNode<T> *node)
{
    if (root==NULL || node==NULL || node==root)
        return NULL; 
    return parent(root, node);
}
//在以p为根的子树中查找并返回node结点的父母结点地址
template <class T>
BinaryNode<T>* BinaryTree<T>::parent(BinaryNode<T> *p, BinaryNode<T> *node)
{
    BinaryNode<T> *find=NULL;
    if (p!=NULL)
    {
        if (p->left==node || p->right==node) 
            return p;
        find = parent(p->left, node);
        if (find==NULL)
            find = parent(p->right, node);
    }
    return find;
}

template <class T>
void BinaryTree<T>::leaf()                                 //遍历输出叶子结点
{
    leaf(root);
}

//输出以p结点为根的子树的所有叶子结点。先根次序遍历算法，中根、后根次序遍历算法也可，结果一样
template <class T>
void BinaryTree<T>::leaf(BinaryNode<T> *p)
{
    if (p!=NULL)
    {
        if (p->left==NULL && p->right==NULL)
            cout<<p->data<<" ";
        leaf(p->left);
        leaf(p->right);
    }
}

template <class T>
int BinaryTree<T>::countLeaf()                             //返回二叉树的叶子结点数
{
    return countLeaf(root);
}

template <class T>
int BinaryTree<T>::countLeaf(BinaryNode<T> *p)             //返回以p结点为根的子树的叶子结点个数
{
    if (p==NULL)
        return 0;
    if (p->left==NULL && p->right==NULL)
        return 1;
    return countLeaf(p->left)+countLeaf(p->right);
}

template <class T>
bool BinaryTree<T>::replace(T key, T x)                    //将首次出现的关键字为key结点值替换为x
{
    BinaryNode<T> *find = search(key);                     //查找关键字为key的结点
    if (find!=NULL)
        find->data = x;                                    //替换结点元素值
    return find!=NULL;    
}

template <class T>
void BinaryTree<T>::replaceAll(T key, T x)                 //将所有关键字为key的结点全部替换为x
{
    replaceAll(root, key, x);
}

template <class T>
void BinaryTree<T>::replaceAll(BinaryNode<T> *p, T key, T x)//在以p为根的子树中实现全部替换
{
    if (p!=NULL)
    {
        if(p->data==key) 
            p->data = x;                   	               //替换
        replaceAll(p->left, key, x);
        replaceAll(p->right, key, x);
    }
}
template <class T>
int BinaryTree<T>::getLevel(T x)                           //返回x结点所在的层次，若空树或未查找到x返回-1
{ 
    if (root==NULL)
        return -1;
    return getLevel(root, 1, x);                           //令根结点的层次为1
}

template <class T>
int BinaryTree<T>::getLevel(BinaryNode<T> *p, int i, T x)  //在以p结点（层次为i）为根的子树中求x结点所在的层次
{
    if (p!=NULL)
    {
        if (p->data==x) 
            return i;                                      //查找成功
        int level = getLevel(p->left, i+1, x);             //在左子树查找
        if (level!=-1)
            return level;
        return getLevel(p->right, i+1, x);                 //继续在右子树中查找
    }
    return -1;                                             //查找不成功
}

//两棵二叉树的操作
template <class T>
int BinaryTree<T>::operator==(BinaryTree<T> &bitree)       //比较两棵二叉树是否相等，重载运算符==
{
    return equals(this->root, bitree.root);
}

template <class T>
bool BinaryTree<T>::equals(BinaryNode<T> *p, BinaryNode<T> *q)  //判断以p和q结点为根的两棵子树是否相等
{
    return p==NULL && q==NULL || p!=NULL && q!=NULL && p->data==q->data && 
           equals(p->left, q->left) && equals(p->right, q->right);//递归函数
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree<T> &bitree)           //深拷贝，由已知bitree构造二叉树
{
    this->root = copy(bitree.root);
}

template <class T>
BinaryNode<T>* BinaryTree<T>::copy(BinaryNode<T> *p)       //复制以p根的子二叉树，返回新建子二叉树的根结点
{
    BinaryNode<T> *q=NULL;
    if (p!=NULL)                                           //非空时建立结点
    {
        q = new BinaryNode<T>(p->data);
        q->left = copy(p->left);                           //复制左子树，递归调用
        q->right = copy(p->right);                         //复制右子树，递归调用
    }
    return q;                                              //返回建立子树的根结点
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T> &bitree)   //赋值，深拷贝，重载运算符=
{
    destroy(this->root);
    this->root = copy(bitree.root);
    return *this;
}



//后根次序未写

template <class T>
bool BinaryTree<T>::isCompleteBinaryTree()                 //判断一棵二叉树是否是完全二叉树
{
    if (this->root==NULL)                                  //空树是完全二叉树
        return true;
    SeqQueue<BinaryNode<T>*> que;                          //创建一个空队列
//    LinkedQueue<BinaryNode<T>*> que;
    BinaryNode<T> *p=this->root;
    cout<<"层次遍历：";
    while (p->left!=NULL)                //2度结点的两个孩子结点入队，寻找第一个非2度结点
    {
        cout<<p->data<<" ";
        que.enqueue(p->left);     
        if (p->right!=NULL)
            que.enqueue(p->right);
        p = que.dequeue();
    }
//    cout<<"；1度或叶子结点："<<p->data<<"；";              //循环停止时，p->left==NULL && p是1度或叶子结点
    if (p->right!=NULL)                   //p的左子树空而右子树不空，确定不是
        return false;
    cout<<"队列：";
    while (!que.isEmpty())                                 //检测队列中是否都是叶子结点
    {
        cout<<p->data<<" ";
        if (p->left!=NULL || p->right!=NULL)               //发现非叶子，确定不是
            return false;
        p = que.dequeue();
    }
    return true;
}


