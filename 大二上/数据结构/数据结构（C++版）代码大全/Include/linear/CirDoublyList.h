//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.3   双链表
//3. 循环双链表类

#include <iostream>
using namespace std;
#include "DoubleNode.h"                                    //双链表结点类

template <class T>
class CirDoublyList                                        //带头结点的循环双链表类
{
  public:
    DoubleNode<T> *head;                                   //头指针

    CirDoublyList();                                       //构造空循环双链表
    CirDoublyList(T values[], int n);                      //构造循环双链表，由values数组提供元素
    ~CirDoublyList();                                      //析构函数

    bool empty();                                          //判断循环双链表是否为空
    int count();                                           //返回循环双链表长度 
    T& get(int i);                                         //返回第i（≥0）个元素
    virtual void set(int i, T x);                          //设置第i（≥0）个元素为x；虚函数
    friend ostream& operator<<<>(ostream& out, CirDoublyList<T>&); //输出循环双链表
    void printPrevious();                                  //输出循环双链表，从后向前，沿着前驱链。循环双链表增加的操作
    DoubleNode<T>* insert(int i, T x);                     //插入x作为第i（≥0）个结点
    virtual DoubleNode<T>* insert(T x);                    //在最后插入x元素结点；虚函数
    T remove(int i);                                       //删除第i（≥0）个结点
    void removeAll();                                      //清空循环双链表
    DoubleNode<T>* search(T key);                          //顺序查找首次出现的关键字为key元素，返回结点地址；若未找到，返回NULL。T必须重载==运算符，约定比较两个元素相等（==）的规则
    virtual void operator+=(CirDoublyList<T> &list);       //将list链接在当前循环双链表之后；虚函数

    //习题解答 习2.6
    DoubleNode<T>* first();                                //返回第一个结点地址
    DoubleNode<T>* next(DoubleNode<T> *p);                 //返回p结点的后继结点地址
    DoubleNode<T>* previous(DoubleNode<T> *p);             //返回p结点的前驱结点地址
    DoubleNode<T>* last();                                 //返回最后一个结点地址

    //第8章查找 8.2.1 顺序查找 习题，T必须重载==和!=运算符
/*
    void insertUnrepeatable(T x);               	//尾插入不重复元素
    virtual void removeFirst(T key);               	//删除首次出现的元素值为key的结点
DoubleNode<T>* search(T x);                             //顺序查找首次出现的元素值为x结点
    bool contain(T x);                                     //判断是否包含元素x
    void replaceFirst(T x, T y);                           //将元素x替换为元素y
    void replaceAll(T x, T y);                             //将所有值为x元素替换为元素y
    void removeFirst(T x);                                 //删除元素x首次出现结点
    void removeLast(T x);                                  //删除最后出现的值为x的结点
    void removeAll(T x);                                   //删除所有元素值为x的结点

    //实验题2
    bool operator==(CirDoublyList<T> &list);        //比较两条循环双链表是否相等
    CirDoublyList(CirDoublyList<T> &list);   //深拷贝，复制循环双链表list
    CirDoublyList<T>& operator=(CirDoublyList<T> &list);   //赋值，深拷贝
    CirDoublyList(HSLinkedList<T> &list);           //由单链表构造循环双链表，深拷贝
    CirDoublyList(CirHSLinkedList<T> &list);        //由循环单链表构造循环双链表，深拷贝
    CirDoublyList(DoublyLinkedList<T> &list);       //由双链表构造循环双链表，深拷贝

    void concat(CirDoublyList<T> &list);            //将list链表合并连接到当前链表*this最后，并设置list链表为空，浅拷贝
    void insert(int i, CirDoublyList<T> &list);     //将list链表中的所有结点复制插入到当前链表第i个结点之前，深拷贝
    void append(CirDoublyList<T> &list);            //将list链表中的所有结点复制添加到当前链表最后，深拷贝
    CirDoublyList<T> sub(int i, int n);             //返回从第i个结点开始、长度为n的子表，深拷贝
    void remove(int i, int n);                             //删除从第i个结点开始、长度为n的子表
    bool contain(CirDoublyList<T> &list);           //判断是否包含list链表的所有结点，判断无序的子集
    DoubleNode<T>* search(CirDoublyList<T> &list);   //查找与list匹配的子表，BF模式匹配
    DoubleNode<T>* search(DoubleNode<T> *start, CirDoublyList<T> &list);  //从start结点开始查找与list匹配的子表
    void removeAll(CirDoublyList<T> &list);         //删除所有与list匹配的子表
    void replaceAll(CirDoublyList<T> &patternlist, CirDoublyList<T> &replacementlist);
                                                           //将当前链表中所有与patternlist匹配的子表替换为replacementlist子表
                                                           */
};

//（1）线性表ADT基本操作
template <class T>
CirDoublyList<T>::CirDoublyList()                          //构造空循环双链表
{
    this->head = new DoubleNode<T>();                      //创建头结点
    this->head->prev = this->head->next = this->head;
}

template <class T>
CirDoublyList<T>::CirDoublyList(T values[], int n)         //构造循环双链表，由values数组提供元素
{
    this->head = new DoubleNode<T>();                      //创建头结点
    this->head->prev = this->head->next = this->head;
    for (int i=0; i<n; i++) 
        this->insert(values[i]);                           //在循环双链表最后插入结点
}

template <class T>
CirDoublyList<T>::~CirDoublyList()                         //析构函数
{
    this->removeAll();                                     //清空循环双链表
    delete this->head;                                     //释放头结点
}

template <class T>
bool CirDoublyList<T>::empty()                             //判断循环双链表是否为空
{
    return this->head->next==this->head;
}

//以下函数算法同循环单链表
template <class T>
int CirDoublyList<T>::count()                              //返回循环双链表长度
{
    int i=0;
    for (DoubleNode<T> *p=this->head->next; p!=this->head; p=p->next)
        i++;
    return i;
}

template <class T>
T& CirDoublyList<T>::get(int i)                            //返回第i（≥0）个元素。若i＜0或大于表长则抛出异常，O(n)
{
    DoubleNode<T> *p=this->head->next;
    for (int j=0;  p!=this->head && j<i;  j++)             //遍历寻找第i个结点（p指向）
        p=p->next;
    if (i>=0 && p!=NULL)                                   //若不空且i指定元素序号有效
        return  p->data;                                   //返回第i个元素，执行T的拷贝构造函数
    throw out_of_range("参数i指定元素序号超出范围");       //抛出C++ STL范围越界异常
}

//设置第i（≥0）个元素值为x。若i＜0或大于表长则抛出异常，O(n)
template <class T>
void CirDoublyList<T>::set(int i, T x)
{
    DoubleNode<T> *p=this->head->next;
    for (int j=0;  p!=this->head && j<i;  j++)             //遍历寻找第i个结点，p指向第i个结点
        p=p->next;
    if (i>=0 && p!=this->head)                             //若不空且i指定元素序号有效
        p->data = x;                                       //执行T的=赋值运算
    else throw out_of_range("参数i指定元素序号超出范围");  //抛出C++ STL范围越界异常
}

//输出循环双链表所有元素，形式为“(,)”，T必须重载<<，遍历算法，O(n)
template <class T>
ostream& operator<<<>(ostream& out, CirDoublyList<T> &list)
{
    out<<"(";
    for (DoubleNode<T> *p=list.head->next; p!=list.head; p=p->next)
    {
        out<<p->data;
        if (p->next!=list.head)
            out<<", ";
    }
    out<<")\n";
    return out;
}

template <class T>
void CirDoublyList<T>::printPrevious()                     //输出循环双链表，从后向前，沿着前驱域
{
    cout<<"listPrevious: (";
    for (DoubleNode<T> *p=this->head->prev;  p!=this->head;  p=p->prev)
    {
        cout<<p->data;
        if (p->prev!=head)
            cout<<", ";
    }
    cout<<")\n";
}

//插入x作为第i（≥0）个元素，返回插入结点地址。
//若i＜0，插入x作为第0个元素；若i大于表长，插入x作为最后一个元素。O(n)
template <class T>
DoubleNode<T>* CirDoublyList<T>::insert(int i, T x)
{
    DoubleNode<T> *front=this->head;                       //front指向头结点
    for (int j=0; front->next!=head && j<i; j++)           //遍历寻找插入位置
        front = front->next;                               //循环停止时，front定位到第i-1个结点或最后一个结点
        //以下在front之后插入x结点，包括头插入（i≤0）、中间/尾插入（i＞0）
    DoubleNode<T> *q = new DoubleNode<T>(x, front, front->next);
    front->next->prev = q;
    front->next = q;
    return q;                                              //返回插入结点地址
}

template <class T>
DoubleNode<T>* CirDoublyList<T>::insert(T x)               //在最后插入x元素结点，返回插入结点地址，O(1)
{
    DoubleNode<T> *q = new DoubleNode<T>(x, this->head->prev, this->head);
    this->head->prev->next = q;                            //插入在头结点之前，相当于尾插入
    this->head->prev = q;
    return q;
}

//删除第i（≥0）个结点，返回被删除元素。若i＜0或大于表长则抛出异常，O(n)
template <class T>
T CirDoublyList<T>::remove(int i)
{
    DoubleNode<T> *p=this->head->next;
    for (int j=0;  p!=this->head && j<i;  j++)             //遍历寻找第i个结点，p指向第i个结点
        p=p->next;
    if (i>=0 && p!=this->head)                             //删除p结点自己
    {
        T old = p->data;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        return old;                                        //执行T的拷贝构造函数
    }    
    throw out_of_range("参数i指定元素序号超出范围");
}

template <class T>
void CirDoublyList<T>::removeAll()                             //清空循环双链表
{
    DoubleNode<T> *p=this->head->next;
    while (p!=this->head)
    {
        DoubleNode<T> *q = p;
        p = p->next;
        delete q;
    }
    this->head->next = this->head->prev = this->head;      //设置循环双链表为空
}
//以上是第2章内容，实现线性表ADT
//以上2.3.3节


/*//习题解答第2章
//以下声明错误，
template <class T>
class CirDoublyList : public SinglyList<T>        //循环双链表类，继承单链表类
*/

//习题解答 习2.6 循环双链表的迭代器
template <class T>
DoubleNode<T>* CirDoublyList<T>::first()                   //返回循环双链表第一个结点地址，O(1)
{
    return head->next==head ? NULL : head->next;
}

template <class T>
DoubleNode<T>* CirDoublyList<T>::next(DoubleNode<T> *p)     //返回p结点的后继结点地址，O(1)
{
    return (head->next==head || p==NULL || p==head || p==head->prev) ? NULL : p->next;
}

template <class T>
DoubleNode<T>* CirDoublyList<T>::previous(DoubleNode<T> *p) //返回p结点的前驱结点地址，O(1)
{
    return (head->next==head || p==NULL || p==head || p==head->next) ? NULL : p->prev;
}

template <class T>
DoubleNode<T>* CirDoublyList<T>::last()                    //返回循环双链表最后一个结点地址，O(1)
{
    return head->prev==head ? NULL : head->prev;
}

//习题解答 习2.7
//将list链表合并连接到当前链表*this最后，并设置list链表为空
template <class T>
void CirDoublyList<T>::operator+=(CirDoublyList<T> &list)
{
    DoubleNode<T> *rear=this->head->prev;                   //rear指向当前链表最后一个结点
    rear->next = list.head->next;
    list.head->next->prev = rear;
    rear=list.head->prev;
    rear->next = this->head;
    this->head->prev = rear;
    list.head->prev = list.head; 
    list.head->next = list.head; 
}