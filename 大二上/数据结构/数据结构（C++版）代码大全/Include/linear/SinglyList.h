//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.2   单链表
//3.  带头结点的单链表

#include <iostream>
using namespace std;
#include "Node.h"                                          //单链表结点类

template <class T>
class SinglyList                                           //带头结点的单链表类，T指定元素类型，T必须重载==关系运算符
{
  public:
    Node<T> *head;                                         //头指针，指向单链表的头结点

    SinglyList();                                          //构造空单链表
    SinglyList(T values[], int n);                         //构造单链表，由values数组提供元素
    ~SinglyList();                                         //析构函数
 
    bool empty();                                          //判断单链表是否为空
    int count();                                           //返回单链表长度 
    T& get(int i);                                         //返回第i（≥0）个元素引用
    virtual void set(int i, T x);                          //设置第i（≥0）个元素为x；虚函数
    friend ostream& operator<<<>(ostream&, SinglyList<T>&);//输出单链表所有元素
    Node<T>* insert(int i, T x);                           //插入x作为第i（≥0）个结点，返回插入结点地址
    virtual Node<T>* insert(T x);                          //在单链表最后插入x元素；虚函数
    T remove(int i);                                       //删除第i（≥0）个结点，返回被删除元素
    void removeAll();                                      //清空单链表

    //5.2.2 稀疏矩阵的三元组行的单链表 用；8.2.1 散列表用，T必须重载==和!=运算符
	Node<T>* search(T key);                                //顺序查找首次出现的关键字为key元素，返回结点地址；若未找到，返回NULL。
                                                           //T必须重载==运算符，约定比较两个元素相等（==）的规则
    void insertUnrepeatable(T x);                          //尾插入不重复元素
    virtual void removeFirst(T key);                       //删除首次出现的元素值为key的结点

	bool operator==(SinglyList<T> &list);                  //重载关系运算符==，比较两条单链表是否相等
    bool operator!=(SinglyList<T> &list);                  //重载关系运算符!=，比较两条单链表是否不相等
    SinglyList(SinglyList<T> &list);                       //深拷贝构造函数，复制单链表list的所有结点
    SinglyList<T>& operator=(SinglyList<T> &list);         //重载=赋值运算符，深拷贝
    virtual void operator+=(SinglyList<T> &list);          //将list链接在当前单链表之后；虚函数

    //习题解答第2章习2.4
    Node<T>* first();                                      //返回单链表第一个结点地址
    Node<T>* next(Node<T> *p);                             //返回p结点的后继结点地址
    Node<T>* previous(Node<T> *p);                         //返回p结点的前驱结点地址
    Node<T>* last();                                       //返回单链表最后一个结点地址

    //【习2.5】逆转单链表。
    void reverse();                                        //将当前单链表逆转

    //实验2
    bool contain(T x);                           //判断单链表是否包含元素x
    bool isSorted();                             //判断单链表是否已排序（升序）
    void replaceFirst(T key, T x);                 //将单链表中的元素key替换为元素x
    void replaceAll(T key, T x);                   //将所有值为key元素替换为元素x
                                                 //将所有与sourcelist匹配的子表替换为destlist子表
    void removeAll(T x);                         //删除所有元素值为key的结点

    //4.4 递归算法
  private:
    Node<T>* create(T values[], int n, int i);    //由指定数组构造单链表
    int count(Node<T> *p);                       //返回从p结点开始的单链表长度
    void print(Node<T> *p);                       //输出从p结点开始的单链表
    bool equals(Node<T> *p, Node<T> *q);         //比较两条单链表是否相等
    Node<T>* copy(Node<T> *p);                   //复制单链表，递归算法
    void replaceAll(Node<T> *p, T key, T x);       //将所有值为key元素替换为元素x
//    void removeAll(T x);                         //删除所有元素值为key的结点

};

template <class T>
SinglyList<T>::SinglyList()                                //构造空单链表
{
//    cout<<"SinglyList()"<<endl;
    this->head = new Node<T>();                            //创建头结点，data数据域未初始化
}

template <class T>
SinglyList<T>::SinglyList(T values[], int n)                //构造单链表，由values数组提供元素，尾插入
{
    this->head = new Node<T>();                            //创建头结点，构造空链表
    Node<T> *rear = this->head;                            //rear指向单链表最后一个结点
    for (int i=0; i<n; i++)                                //若n>0，构造非空链表
    {
        rear->next = new Node<T>(values[i]);                //创建结点链入rear结点之后，尾插入
        rear = rear->next;                                 //rear指向新的链尾结点
    }
}

template <class T>
SinglyList<T>::~SinglyList()                               //析构函数
{
//    cout<<"析构~SinglyList()"<<*this;
    this->removeAll();                                         //清空单链表
    delete this->head;                                     //释放头结点
}

template <class T>
bool SinglyList<T>::empty()                              //判断单链表是否为空，O(1)
{
    return this->head->next==NULL;
}

//输出单链表所有元素，形式为“(,)”，T必须重载<<，单链表遍历算法，O(n)
template <class T>
ostream& operator<<<>(ostream& out, SinglyList<T> &list)
{
//    out<<"0x"<<list.head->next;
    out<<"(";
    for (Node<T> *p=list.head->next;  p!=NULL;  p=p->next) //p遍历单链表
    {
        out<<p->data;                                      //执行T的<<，T必须重载<<输出流运算符
        if (p->next!=NULL)
            out<<", ";
    }
    out<<")\n";
    return out;
}

template <class T>
int SinglyList<T>::count()                                 //返回单链表长度，单链表遍历算法，O(n)
{
    int i=0;
    for (Node<T> *p=this->head->next;  p!=NULL;  p=p->next)//p遍历单链表
        i++;
    return i;
}

template <class T>
T& SinglyList<T>::get(int i)                               //返回第i（≥0）个元素。若i＜0或大于表长则抛出异常，O(n)
{
    Node<T> *p=this->head->next;
    for (int j=0;  p!=NULL && j<i;  j++)                   //遍历部分单链表，寻找第i个结点（p指向）
        p=p->next;
    if (i>=0 && p!=NULL)                                   //若单链表不空且i指定元素序号有效
        return  p->data;                                   //返回第i个元素，执行T的拷贝构造函数
    throw out_of_range("参数i指定元素序号超出范围");       //抛出C++ STL范围越界异常
}
           
//设置第i（≥0）个元素值为x。若i<0或大于表长则抛出异常，O(n)
template <class T>
void SinglyList<T>::set(int i, T x)
{
    Node<T> *p=this->head->next;
    for (int j=0;  p!=NULL && j<i;  j++)                   //遍历寻找第i个结点，p指向第i个结点
        p=p->next;
    if (i>=0 && p!=NULL)                                   //若单链表不空且i指定元素序号有效
        p->data = x;                                       //执行T的=赋值运算
    else throw out_of_range("参数i指定元素序号超出范围");  //抛出C++ STL范围越界异常
}

//插入x作为第i（≥0）个元素，返回插入结点地址。
//若i＜0，插入x作为第0个元素；若i大于表长，插入x作为最后一个元素。O(n)
template <class T>
Node<T>* SinglyList<T>::insert(int i, T x) 
{
    Node<T> *front=this->head;                             //front指向头结点
    for (int j=0; front->next!=NULL && j<i; j++)           //遍历部分单链表寻找插入位置
        front=front->next;                                 //循环停止时，front定位到第i-1个结点或最后一个结点
    front->next = new Node<T>(x, front->next);
                               //在front之后插入x结点，包括头插入（i≤0）、中间/尾插入（i＞0）
    return front->next;                                    //返回插入结点地址
}

template <class T>
Node<T>* SinglyList<T>::insert(T x)                        //在单链表最后插入x元素结点，返回插入结点地址，O(n)
{
    Node<T> *rear=this->head;
    while (rear->next!=NULL)                               //遍历寻找单链表尾结点，插入其后
        rear=rear->next;
    rear->next = new Node<T>(x);                           //在rear结点之后插入值为x结点
    return rear->next;                                     //返回插入结点地址
}

//删除第i（≥0）个结点，返回被删除元素。若i<0或大于表长则抛出异常，O(n)
template <class T>
T SinglyList<T>::remove(int i)
{
    Node<T> *front=this->head;                             //front指向头结点
    for (int j=0; front!=NULL && j<i;  j++)                //遍历部分单链表，front定位到第i-1个结点
        front=front->next;
    if (i>=0 && front!=NULL && front->next!=NULL)          //当front的后继结点存在时，删除之
    {
        Node<T> *q=front->next;                            //q结点为front的后继结点
        T old = q->data;
        front->next = q->next;
        delete q;
        return old;                                        //执行T的拷贝构造函数
    }
    throw out_of_range("参数i指定元素序号超出范围");
}

template <class T>
void SinglyList<T>::removeAll()                            //清空单链表，O(n)
{
    Node<T> *p=this->head->next;
    while (p!=NULL)
    {
        Node<T> *q = p;
        p = p->next;                                       //到达p的后继结点
        delete q;                                          //释放q结点所占用的存储单元
    }
    head->next=NULL;                                       //设置单链表为空，否则运行错
}

//第5章 稀疏矩阵的三元组行的单链表。用其子类
//顺序查找首次出现的关键字为key元素，返回结点地址；若未找到，返回NULL。
//T必须重载==运算符，约定比较两个元素相等（==）的规则
template <class T>
Node<T>* SinglyList<T>::search(T key)
{
    for (Node<T>* p=this->head->next;  p!=NULL;  p=p->next)
        if (p->data==key)                                  //T必须重载==运算符
            return p;
    return NULL;
}

//比较两条单链表是否相等，其中所有对应结点元素相等且长度相等。T必须重载==运算符
template <class T>
bool SinglyList<T>::operator==(SinglyList<T> &list)
{
    if (this==&list || this->head==list.head)
              //指针比较，当两个对象引用同一个实例，或单链表浅拷贝，两个对象引用同一条单链表时
        return true;
    Node<T> *p=this->head->next, *q=list.head->next;
    while (p!=NULL && q!=NULL && p->data==q->data)         //T必须重载==运算符
    {
        p = p->next;
        q = q->next;
    }
    return p==NULL && q==NULL;
}
template <class T>
bool SinglyList<T>::operator!=(SinglyList<T> &list)        //比较两条单链表是否不相等
{
    return !(*this==list);
}

//5.  单链表的浅拷贝与深拷贝
/*
template <class T>
SinglyList<T>::SinglyList(SinglyList<T> &list)   //默认拷贝构造函数，浅拷贝
{
    this->head = list.head;                      //对应成员变量赋值，指针赋值，导致两个对象指向同一条单链表，析构出错
}
template <class T>
SinglyList<T>& SinglyList<T>::operator=(SinglyList<T> &list)   //默认=赋值，浅拷贝
{
    this->head = list.head;                      //对应成员变量赋值，指针赋值，导致两个对象指向同一条单链表，析构出错
    return *this;
}*/

//重载=赋值运算符，深拷贝，删除再复制插入算法
//构造结点将执行T的=运算，是否复制元素对象，取决于T的=是浅拷贝或深拷贝
template <class T>
SinglyList<T>& SinglyList<T>::operator=(SinglyList<T> &list)
{
    this->removeAll();                                     //清空当前单链表，只剩头结点，释放其他结点
    Node<T> *rear = this->head;                            //rear指向单链表最后一个结点
    for (Node<T> *p=list.head->next;  p!=NULL;  p=p->next) //p遍历list单链表
    {
        rear->next = new Node<T>(p->data);                 //复制结点尾插入到this单链表
        rear = rear->next;                                 //rear指向新的链尾结点
    }
    return *this;
}

template <class T>
SinglyList<T>::SinglyList(SinglyList<T> &list)             //深拷贝，复制单链表，拷贝调用=
{
    this->head = new Node<T>();                            //创建头结点
    *this=list;                                            //执行单链表赋值，深拷贝
}

//【例2.3】连接两条单链表。
//将list链接在当前单链表之后，首尾相接合并成一条单链表
template <class T>
void SinglyList<T>::operator+=(SinglyList<T> &list)  //参数是对象引用
//void SinglyList<T>::mergeWith(SinglyList<T> list) //参数是对象，参数传递时执行拷贝构造函数
{
    Node<T> *rear=this->head;
    while (rear->next!=NULL)                               //找到当前单链表的最后一个结点
        rear = rear->next;
    rear->next = list.head->next;                          //两条单链表首尾相接连接合并成一条单链表
    list.head->next = NULL;                                //设置list单链表为空，否则运行错
//    cout<<*this<<list;                          //输出单链表
}
//以上是第2章内容，实现线性表ADT

/*运行错，习题解答第2章
template <class T>
void SinglyList<T>::removeAll()                          //清空单链表，O(n)
{
    for (Node<T> *p=this->head->next;  p!=NULL;  p=p->next)
    {
        Node<T> *q=p;
        delete q;                                          //释放q结点所占用的存储单元
    }
    head->next=NULL;                                       //设置单链表为空，否则运行错
}*/

//第2章思考题，散列表用
//尾插入不重复元素x，基于查找算法，T必须重载==运算符。
template <class T>
void SinglyList<T>::insertUnrepeatable(T x)
{
    Node<T> *front=this->head, *p=front->next;
    while (p!=NULL && p->data!=x)                          //查找，T必须重载!=运算符
    {
        front = p;                                         //front是p的前驱结点
        p = p->next;
    }
    if (p==NULL)                                           //尾插入值为x结点，不插入重复元素
        front->next = new Node<T>(x); 
}

//删除首次出现的元素值为x的结点，T必须重载!=运算符，散列表用
template <class T>
void SinglyList<T>::removeFirst(T x)
{
    Node<T> *front=this->head, *p=front->next;
    while (p!=NULL && p->data!=x)                          //查找值为x结点，T必须重载!=运算符
    {
        front = p;
        p=p->next;
    }
    if (p!=NULL)                                           //删除p结点
    {
        front->next = p->next;
        delete(p);
    }
}

//以下是第2章习题
//【习2.4】求单链表的最大值。

//单链表的迭代器
template <class T>
Node<T>* SinglyList<T>::first()                            //返回单链表第一个结点地址，O(1)
{
    return this->head->next;
}

template <class T>
Node<T>* SinglyList<T>::next(Node<T> *p)                   //返回p结点的后继结点地址，O(1)
{
    return p==NULL ? NULL : p->next;
}

template <class T>
Node<T>* SinglyList<T>::previous(Node<T> *p)               //返回p结点的前驱结点地址，O(n)
{
    if (p==NULL || p==this->head)
        return NULL;
    Node<T> *front=head->next;
    while (front!=NULL && front->next!=p)
        front=front->next;
    return front;
}

template <class T>
Node<T>* SinglyList<T>::last()                             //返回单链表最后一个结点地址，O(n)
{
    Node<T> *p=head->next;
    while (p!=NULL && p->next!=NULL)
        p=p->next;
    return p;
}

//【习2.5】逆转单链表。
template <class T>
void SinglyList<T>::reverse()                              //将当前单链表逆转。算法描述图见习题解答图2.8
{
    Node<T> *p=this->head->next, *front=NULL;              //front作为p结点的前驱结点
    while (p!=NULL)
    {
        Node<T> *succ = p->next;                           //设置succ是p的后继结点
        p->next = front;                                   //使p->next指向p结点的前驱结点
        front = p;
        p = succ;                                          //p到达后继结点
    }
    this->head->next = front;                              //改变单链表头结点的指针域
}


//基于查找的删除和替换
template <class T>
void SinglyList<T>::replaceFirst(T x, T y)               //将首次出现的元素x替换为元素y，T必须重载!=运算符
{
    Node<T>* p=this->search(x);
    if (p!=NULL)
        p->data = y;
}

template <class T>
void SinglyList<T>::replaceAll(T x, T y)                 //将所有值为x元素替换为元素y，T必须重载==运算符
{
    for (Node<T>* p=this->head->next;  p!=NULL;  p=p->next)
        if (p->data==x)
            p->data = y;
}

template <class T>
void SinglyList<T>::removeAll(T x)                       //删除单链表中所有元素值为x的结点，T必须重载!=运算符
{
    Node<T> *front=this->head, *p=front->next;
    while (p!=NULL)
        if (p->data!=x)                                    //查找，T必须重载!=运算符
        {
            front = p;
            p = p->next;
        }
        else
        {
            front->next = p->next;                         //删除p结点
            delete p;
            p = front->next;                               //p指向front后继结点，再次查找
        }
}

template <class T>
bool SinglyList<T>::isSorted()                             //判断单链表是否已排序（升序），T必须重载>运算符
{
    Node<T> *front=this->head->next, *p;
    while (front!=NULL)
    {
        p=front->next;
        if (p!=NULL && front->data > p->data)              //T必须重载>运算符
            return false;
        front = p;
    }
    return true;
}

/*
//4.4 递归算法，正确
template <class T>
SinglyList<T>::SinglyList(T values[], int n)               //构造单链表，由values数组提供元素
{
    this->head = new Node<T>();                            //创建头结点
    this->head->next = create(values,n,0);
}

//构造单链表，递归算法，由values数组的第i个元素构造当前结点，尾插入
template <class T>
Node<T>* SinglyList<T>::create(T values[], int n, int i)
{
    Node<T> *p=NULL;
    if (i<n)
    {
        p = new Node<T>(values[i]);
        p->next = create(values, n, i+1);                   //递归调用
    }
    return p;
}

template <class T>
int SinglyList<T>::count()                                 //返回单链表长度，递归算法
{
    return count(this->head->next);
}
template <class T>
int SinglyList<T>::count(Node<T>*p)                        //返回从p结点开始的单链表长度，递归算法
{
    if (p==NULL)
        return 0;
    return 1+count(p->next);                               //递归调用
}

//实验4
//输出单链表，递归算法，形式为“(,)”，T必须重载<<
template <class T>
ostream& operator<<<>(ostream& out, SinglyList<T> &list)
{
    out<<"(";
    list.print(list.head->next);
    out<<")\n";
    return out;
}

template <class T>
void SinglyList<T>::print(Node<T>*p)                       //输出从p结点开始的单链表，递归算法，私有函数
{
    if (p!=NULL)
    {
        cout<<p->data;
        if (p->next!=NULL)
            cout<<", ";
        print(p->next);                                    //递归调用
    }
}

template <class T>
bool SinglyList<T>::operator==(SinglyList<T> &list)        //比较两条单链表是否相等
{
    return equals(this->head->next, list.head->next);
}
template <class T>
bool SinglyList<T>::equals(Node<T> *p, Node<T> *q)         //比较两条单链表是否相等，递归算法，私有函数
{
    return p==NULL && q==NULL || p!=NULL && q!=NULL && p->data==q->data && equals(p->next, q->next);
}

template <class T>
SinglyList<T>::SinglyList(SinglyList<T> &list)             //单链表的拷贝构造函数
{
    this->head = new Node<T>();                            //创建头结点
    this->head->next = copy(list.head->next);
}
template <class T>
Node<T>* SinglyList<T>::copy(Node<T> *p)                   //复制单链表，递归算法，私有函数
{
    Node<T> *q=NULL;
    if (p!=NULL)
    {
        q = new Node<T>(p->data);
        q->next = copy(p->next);                           //递归调用
    }
    return q;
}

//顺序查找首次出现的关键字为key元素，返回结点地址；若未找到，返回NULL。
template <class T>
Node<T>* SinglyList<T>::search(T key)
{
    return search(key, this->head->next);
}

template <class T>
Node<T>* SinglyList<T>::search(T key, Node<T>* p)          //从单链表p结点开始顺序查找元素key
{
    if (p!=NULL && p->data!=key)                           //T必须重载!=
        return search(key, p->next);
    return p;
}

template <class T>
void SinglyList<T>::replaceAll(T key, T y)                   //将所有值为key元素替换为元素x
{
     replaceAll(head->next, key, x);
}

template <class T>
void SinglyList<T>::replaceAll(Node<T> *p, T key, T x)     //将所有值为key元素替换为元素x，递归算法，私有函数
{
    if (p!=NULL)
    {
        if (p->data==key)
            p->data = x;
        replaceAll(p->next, key, x);
    }
}*/

