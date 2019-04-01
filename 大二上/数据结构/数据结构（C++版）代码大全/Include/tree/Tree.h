//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.5.3   树的父母孩子兄弟链表实现
//父母孩子兄弟链表存储的树类

#include <iostream>
using namespace std;
#include "TreeNode.h"                                      //树的孩子兄弟链表结点类
#include "MyString.h"                                      //字符串类（声明见第3章）

//ADT??
//，删除树
template <class T>
class Tree                                                 //父母孩子兄弟链表存储的树类，T指定结点的元素类型
{
  public:
    TreeNode<T> *root;                                     //指向根结点

    Tree();                                                //默认构造空树 
    Tree(MyString prelist[], int n);                       //以横向凹入表示构造树，T必须有MyString类型的构造函数
    ~Tree();                                               //默认析构函数
    friend ostream& operator<<<>(ostream& out, Tree<T>&);  //输出树的横向凹入表示字符串，先根次序遍历树
    void postOrder();                                      //输出树的后根次序遍历序列

    //习题6
    bool empty();                                          //判断是否空树
    int count();                                           //返回树的结点个数
    int height();                                          //返回树的高度
    int childCount(TreeNode<T> *p);                        //返回p结点的孩子结点数
    TreeNode<T>* getChild(TreeNode<T> *p, int i);          //返回p结点的第i个孩子
    TreeNode<T>* getLastChild(TreeNode<T> *p);             //返回p结点的最后一个孩子
    TreeNode<T>* getLastSibling(TreeNode<T> *p);           //返回p结点的最后一个兄弟
    TreeNode<T>* search(T key);                            //查找首次出现的关键字为key结点

    TreeNode<T>* insertRoot(T x);                          //插入根
    TreeNode<T>* insertChild(TreeNode<T> *p, T x, int i);  //插入x元素作为p结点的第i个孩子结点，返回插入结点
    TreeNode<T>* insertSibling(TreeNode<T> *p, T x, int i);//插入x元素作为p结点的第i个兄弟结点，返回插入结点
    TreeNode<T>* insertLastSibling(TreeNode<T> *p, T x);   //插入x作为p结点的最后一个兄弟结点
    TreeNode<T>* insertLastChild(TreeNode<T> *p, T x);     //插入x作为p结点的最后一个孩子

    Tree(Tree<T> &Tree);                                   //拷贝构造函数，深拷贝
    Tree<T>& operator=(Tree<T> &Tree);                     //重载=赋值运算符，深拷贝，
    TreeNode<T>* insertChild(TreeNode<T> *p, Tree<T> &subtree, int i);//复制subtree子树并插入作为p的第i（≥0）棵子树
    void printGenList();                                   //输出树（森林）的广义表表示
    Tree(MyString genlist);                                //以广义表表示构造树，T必须有MyString类的构造函数

  private:
    void preOrder(TreeNode<T> *p, int i);                  //先根次序遍历以p结点为根的子树
    void postOrder(TreeNode<T> *p);                        //后根次序遍历以p结点为根的子树
    void remove(TreeNode<T> *p);                           //删除以p结点为根的子树

    //习题6
    int count(TreeNode<T> *p);                          //返回以p结点为根的子树结点个数
    int height(TreeNode<T> *p);                            //返回以p结点为根的子树高度，后根次序遍历
    TreeNode<T>* search(TreeNode<T> *p, T key);
    void printGenList(TreeNode<T> *p);                     //输出以p为根的子树的广义表表示
    TreeNode<T>* copy(TreeNode<T> *p);                     //复制以p根的子树

//    TreeNode<T>* insertSibling(TreeNode<T> *p, T x, int i);   //插入value作为p结点的下一个兄弟结点
//bool isChild(TreeNode<T> *p, TreeNode<T> *node)   	//判断node是否是p的孩子结点
//    void removeChild(TreeNode<T> *p, int i)               	//删除以p的第i个孩子为根的子树
//void clear()                                      	//删除树

};

template <class T>
Tree<T>::Tree()                                            //构造空树
{
    root = NULL;
}

template <class T>
bool Tree<T>::empty()                                      //判断是否空树
{
    return root==NULL;
}

//（1） 树的遍历 
template <class T>
ostream& operator<<(ostream& out, Tree<T> &tree)           //输出树的横向凹入表示字符串
{
    out<<"树的横向凹入表示：\n";   
    tree.preOrder(tree.root, 0);
    return out;
}
//先根次序遍历以p为根的子树，参数i指定结点的层次，输出i个tab缩进量，递归算法
template <class T>
void Tree<T>::preOrder(TreeNode<T> *p, int i)
{
    if (p!=NULL)
    {
        for (int j=0; j<i; j++)
            cout<<"\t";
        cout<<p->data<<endl;
        preOrder(p->child, i+1);
        preOrder(p->sibling, i);
    }
}

//思考题 课件
template <class T>
void Tree<T>::postOrder()                                  //后根次序遍历树
{
    cout<<"树的后根次序遍历序列:  ";   
    this->postOrder(root);
    cout<<endl;   
}
template <class T>
void Tree<T>::postOrder(TreeNode<T> *p)                    //后根次序遍历以p为根的子树，递归算法
{
    if (p!=NULL)
    {
        postOrder(p->child);
        cout<<p->data<<" ";
        postOrder(p->sibling);
    }
}

//思考题 课件
template <class T>
Tree<T>::~Tree()                                           //析构函数
{
    cout<<"撤销树: ";
    remove(this->root);
    cout<<endl;
}

template <class T>
void Tree<T>::remove(TreeNode<T> *p)                       //删除以p结点为根的子树，后根次序遍历
{
    if (p!=NULL)
    {
        remove(p->child);
        remove(p->sibling);
        cout<<p->data<<" ";                                //显示撤销结点的次序，可省略
        delete p;
    }
}

//（2） 以横向凹入表示构造树（森林）
//以横向凹入表示构造树，prelist数组存储一棵树的横向凹入表示序列，n为prelist数组长度。
//T必须有MyString类型的构造函数，结点值去除了所有\t前缀。非递归算法
template <class T>
Tree<T>::Tree(MyString prelist[], int n)
{
    this->root = NULL;
    if (n<=0)
        return;
    this->root = new TreeNode<T>(prelist[0]);              //创建根结点
    TreeNode<T> *p = this->root;
    int len=0;                                             //p结点的'\t'前缀个数

    for (int i=1; i<n; i++)                                //将prelist[i]插入作为森林中最后一棵子树的最后一个孩子
    {   int j=0;
        while (j<prelist[i].count() && prelist[i][j]=='\t')   //统计prelist[i]串中'\t'前缀个数
            j++;

        prelist[i].remove(0,j);                            //删除prelist[i]串中从0开始的j个字符，即去除串中j个'\t'前缀
        if (j==len+1)                                      //prelist[i]比前一元素多一个'\t'前缀
        {   p->child = new TreeNode<T>(prelist[i],p,NULL,NULL);   //插入作为p的第0个孩子
            p = p->child;
            len++;
            continue;
        }
        while (len > j)                                    //prelist[i]比前一元素的'\t'少，p向上寻找插入位置
        {   p=p->parent;                                   //p向上一层
           len--;
        }
        p->sibling = new TreeNode<T>(prelist[i],p->parent,NULL,NULL);//前缀个数相同，插入作为p结点的下个兄弟
        p = p->sibling;
    }
}


//实验6-11
template <class T>
int Tree<T>::count()                                       //返回树的结点个数
{
    return this->count(this->root);
}
template <class T>
int Tree<T>::count(TreeNode<T> *p)                         //返回以p结点为根的子树结点个数，算法同二叉树
{
    if (p==NULL)
        return 0;
    return 1+count(p->child)+count(p->sibling);
}

template <class T>
int Tree<T>::childCount(TreeNode<T> *p)                    //返回p结点的孩子结点数
{
    int i=0;
    if (p!=NULL)
        for (p=p->child;  p!=NULL;  p=p->sibling)
            i++;
    return i;
}

template <class T>
int Tree<T>::height()                                      //返回树的高度
{
   return this->height(this->root);
}
template <class T>
int Tree<T>::height(TreeNode<T> *p)                        //返回以p结点为根的子树高度，后根次序遍历
{
   if (p!=NULL)
   {
       int lh = height(p->child)+1;
       int rh = height(p->sibling);
       return (lh>=rh) ? lh : rh;
   }
   return 0;
}

//查找，算法同二叉树
template <class T>
TreeNode<T>* Tree<T>::search(T value)            //查找首次出现的值为value结点
{
    return search(root, value);
}

    //在以p为根的子树中查找，先根次序遍历查找值为value的结点，返回首次出现结点指针，若未找到返回NULL
template <class T>
TreeNode<T>* Tree<T>::search(TreeNode<T> *p, T value)
{
    TreeNode<T> *find=NULL;                      //记载找到结点
    if (p!=NULL)
    {
        if (p->data==value) 
            return p;                            //查找成功，返回结点指针
        find = search(p->child, value);          //在左子树中查找，find指向找到结点，递归调用
        if (find==NULL)                          //若在左子树中未找到
            find = search(p->sibling, value);    //则继续在右子树中查找，递归调用
    }
    return find;                                 //返回查找结果
}

template <class T>
TreeNode<T>* Tree<T>::getChild(TreeNode<T> *p, int i)      //返回p结点的第i个孩子
{
    if (p==NULL || p->child==NULL)                         //p没有孩子
        return NULL;
    p=p->child;                                            //p到达孩子结点
    p = p->child;
    for (int j=1;  j<=i;  j++)
        p = p->sibling;
    return p;
}

//返回结点
template <class T>
TreeNode<T>* Tree<T>::getLastSibling(TreeNode<T> *p)       //返回p结点的最后一个兄弟
{
    if (p==NULL || p->sibling==NULL) 
        return NULL;                                       //p没有兄弟时，返回NULL
    while (p->sibling!=NULL)                               //p沿着兄弟链到达最后一个孩子
        p = p->sibling;
    return p; 
}

template <class T>
TreeNode<T>* Tree<T>::getLastChild(TreeNode<T> *p)         //返回p结点的最后一个孩子
{
    if (p==NULL || p->child==NULL)                         //p没有孩子
        return NULL;
    p=p->child;                                            //p到达孩子结点
    if (p->sibling==NULL)
        return p;
    return this->getLastSibling(p);                        //返回p结点的最后一个兄弟
}


//插入x元素作为根结点，原根结点作为x的孩子结点，返回插入结点
template <class T>
TreeNode<T>* Tree<T>::insertRoot(T x)
{
    return this->root = new TreeNode<T>(x, NULL, this->root);
}

//插入x作为p结点的最后一个兄弟结点
template <class T>
TreeNode<T>* Tree<T>::insertLastSibling(TreeNode<T> *p, T x)
{
    if (p==NULL) 
        return NULL;
    if (p->sibling!=NULL)                                  //当p有兄弟时
        p=this->getLastSibling(p);                         //p到达最后一个兄弟
    return p->sibling = new TreeNode<T>(x, p->parent);     //插入x为p的兄弟，返回插入结点
}

//插入x作为p结点的最后一个孩子结点
template <class T>
TreeNode<T>* Tree<T>::insertLastChild(TreeNode<T> *p, T x)
{
    if (p==NULL)
        return NULL;
    if (p->child==NULL)                                    //当p没有孩子时
       return p->child = new TreeNode<T>(x, p);            //插入x作为p的孩子，返回插入结点
    return this->insertLastSibling(p->child, x);           //当p有孩子时，插入x作为p孩子结点的最后一个兄弟
}

//插入x元素作为p结点的第i个兄弟结点，返回插入结点。
//当i≤0时，插入x作为p结点的下一个兄弟结点；当i大于p结点的兄弟个数时，插入x作为p结点的最后一个兄弟结点
template <class T>
TreeNode<T>* Tree<T>::insertSibling(TreeNode<T> *p, T x, int i)
{
    if (p==NULL)
        return NULL;
    for (int j=0;  j<i && p->sibling!=NULL;  j++)
        p = p->sibling;
    return p->sibling = new TreeNode<T>(x, p->parent, NULL, p->sibling); //插入x作为p的下个兄弟
}

//插入x元素作为p结点的第i个孩子结点，返回插入结点。
//当i≤0时，插入x作为p结点的第0个孩子结点；当i大于p结点的孩子个数时，插入x作为p结点的最后一个孩子结点
template <class T>
TreeNode<T>* Tree<T>::insertChild(TreeNode<T> *p, T x, int i)
{
    if (p==NULL)
        return NULL;
    if (p->child==NULL || i<=0)                            //插入x作为p结点的第0个孩子
    {
        p->child = new TreeNode<T>(x, p, NULL, p->child);  //插入x作为p结点的第i（≥1）个孩子
        return p->child;
    }
    p = p->child;
//    for (int j=1;  j<i && p->sibling!=NULL;  j++)
//        p = p->sibling;
    return insertSibling(p, x, i);//->sibling = new TreeNode<T>(x, p->parent, NULL, p->sibling); //插入x作为p的下个兄弟
}


//深拷贝
template <class T>
Tree<T>::Tree(Tree<T> &tree)                               //深拷贝，由已知的Tree构造树
{
    this->root = copy(tree.root);
}

template <class T>
TreeNode<T>* Tree<T>::copy(TreeNode<T> *p)                 //复制以p根的子树
{                                                          //返回新建子树的根结点
    TreeNode<T> *q=NULL;
    if (p!=NULL)                                           //非空时建立结点
    {
        q = new TreeNode<T>(p->data, q);
        q->child = copy(p->child);                         //复制左子树，递归调用
        q->sibling = copy(p->sibling);                     //复制右子树，递归调用
    }
    return q;                                              //返回建立子树的根结点
}

template <class T>
Tree<T>& Tree<T>::operator=(Tree<T> &tree)                 //重载=赋值运算符，深拷贝
{
    destroy(this->root);
    this->root = copy(tree.root);
    return *this;
}

//广义表表示
template <class T>
void Tree<T>::printGenList()                                 //以广义表表示输出树
{
    cout<<"树的广义表表示：\n";
    printGenList(root);
    cout<<endl;
}

template <class T>
void Tree<T>::printGenList(TreeNode<T> *p)                 //输出以p结点为根的子树的广义表表示
{
    if (p!=NULL)
    {
        cout<<p->data;
        if (p->child!=NULL)
        {
            cout<<"(";                                     //子树以()标记
            printGenList(p->child);                        //输出子树，递归调用
            cout<<")";
        }
        if (p->sibling!=NULL)
        {
            cout<<",";                                     //子树之间以逗号分隔
            printGenList(p->sibling);                      //输出其后兄弟子树，递归调用
        }
    }
}


