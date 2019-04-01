//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.2   单链表
//6.  排序单链表

#include "SinglyList.h"                                    //带头结点的单链表类

//排序单链表类，继承单链表类，T必须重载==、!=、>、>=、<、<=关系运算符
template <class T>
class SortedSinglyList : public SinglyList<T>
{
  private:
    bool asc;                                              //排序次序约定，取值为true（升序）、false（降序）

  public:
    SortedSinglyList(bool asc=true);                       //构造空排序单链表，默认升序
    SortedSinglyList(T values[], int n, bool asc=true);     //构造排序单链表，由values数组提供元素 

//    SortedSinglyList(SortedSinglyList<T> &list):SinglyList<T>(list){}   //默认拷贝构造函数，可省略
//    ~SortedSinglyList(){}                             //默认析构函数，自动执行~SinglyList<T>()，可省略

    void set(int i, T x);                                  //不支持该操作，抛出异常；覆盖
    Node<T>* insert(T x);                                  //插入，根据x元素大小确定插入位置；覆盖
    Node<T>* search(T key);                                //顺序查找首次出现的关键字为key元素；覆盖
//    void insertUnrepeatable(T x);                          //插入不重复元素，返回插入结点地址；覆盖
    void removeFirst(T key);                               //删除首次出现的关键字为key元素的结点；覆盖

    //第9章排序
    SortedSinglyList(SinglyList<T> &list, bool asc=true);  //重载拷贝构造函数，由单链表构造排序单链表
    void operator+=(SortedSinglyList<T> &list);            //归并两条排序单链表；覆盖
};


//构造空排序单链表，asc指定升序（true）或降序（false），默认升序
template <class T>
SortedSinglyList<T>::SortedSinglyList(bool asc) 
{                                                          //此处自动执行SinglyList<T>()，创建头结点
    this->asc = asc;
//    cout<<"SortedSinglyList(bool asc)"<<endl;
}

//构造排序单链表，由values数组提供元素，n指定values数组长度，
//asc指定升序（true）或降序（false），默认升序。直接插入排序算法
template <class T>
SortedSinglyList<T>::SortedSinglyList(T values[], int n, bool asc)
{                                                          //此处自动执行SinglyList<T>()
    this->asc = asc;
    for (int i=0; i<n; i++)  
        this->insert(values[i]);                            //排序单链表插入
}

template <class T>
void SortedSinglyList<T>::set(int i, T x)                  //不支持该操作，抛出异常；运行时覆盖
{
    throw logic_error("不支持set(int i, T x)操作");        //抛出C++ STL逻辑错误异常
}

//插入结点，根据x元素大小确定插入位置，返回插入结点地址。T必须重载>=、<=运算符。
//覆盖基类insert(int i, T x)和insert(T x)成员函数；运行时覆盖基类insert(T x)虚函数。
//采用顺序查找算法确定操作位置，查找成功插入相同元素。
template <class T>
Node<T>* SortedSinglyList<T>::insert(T x)
{
    Node<T> *front=head, *p=head->next;                    //front是p的前驱结点
    //以下循环先寻找x的插入位置，插入x在等值结点之后。升序时比较>=；降序时比较<=
    while (p!=NULL && (asc ? x>=p->data : x<=p->data))
    {   front = p;                                         //记住p的前驱front 
        p = p->next;
    }
    Node<T> *q = new Node<T>(x, p);
    front->next = q;                                       //插入在front结点之后
    return q;
}

//5.2.2 稀疏矩阵的三元组行的单链表 用；
//第7章中用 图的邻接表 

//顺序查找首次出现的关键字与key相等的元素，返回元素结点；查找不成功返回NULL。
//T必须重载==、<=、>=运算，==约定查找过程中比较两个元素相等的规则；<=、>=运算约定排序规则
//覆盖基类SinglyList<T>的search(T key)函数
//排序单链表的顺序查找算法，只比较部分单链表即可确定查找不成功，不需要遍历单链表。
template <class T>
Node<T>* SortedSinglyList<T>::search(T key)
{
    Node<T>* p=this->head->next; 
    while (p!=NULL && (asc ? p->data<=key : p->data>=key)) //T必须重载<=、>=运算
    {
        if (p->data==key)                                  //T必须重载==运算
            return p;
        p=p->next
    }
    return NULL;
}

//删除首次出现的关键字为key元素的结点。覆盖基类removeFirst(T key)成员函数。
//采用顺序查找算法确定操作位置，查找成功删除，否则不删除。T必须重载==、>、<运算符
template <class T>
void SortedSinglyList<T>::removeFirst(T key)
{
    Node<T> *front=head, *p=head->next;                    //front是p的前驱结点
    while (p!=NULL && (asc ?  key>p->data : key<p->data))  //T必须重载>或<
    {   front = p;
        p = p->next;
    }
    if (p!=NULL && key==p->data)                           //T必须重载==，用于识别对象
    {   front->next = p->next;                             //删除p结点
        delete p;
    }
}

//以上2.3节

/*
//插入不重复元素x，根据元素大小插入在合适位置，返回插入结点地址。T必须重载==和>=运算
template <class T>
//？？Node<T>* 升序?降序?
void SortedSinglyList<T>::insertUnrepeatable(T x)
{
    Node<T> *front=this->head, *p=front->next;   //front是p的前驱结点
    while (p!=NULL && x >= p->data)              //寻找插入位置，不插入重复元素，T必须重载>=运算
    {
        if (x == p->data)                        //T必须重载==运算
            return NULL;
        front = p;
        p = p->next;
    }
    front->next = new Node<T>(x, p);             //在front结点之后p之前插入值为x结点
    return front->next;                          //返回插入结点地址
}



/*正确，可省略
template <class T>
SortedSinglyList<T>::~SortedSinglyList()     //默认析构函数，不能继承基类析构函数，自动执行基类析构函数
{
//    cout<<"析构~SortedSinglyList "<<*this;
}                                                //此处自动执行基类析构函数~SinglyList<T>()

//如果声明
template <class T>
SortedSinglyList<T>::SortedSinglyList(SortedSinglyList<T> &list)//默认拷贝构造函数
{                                                //此处默认调用SinglyLinkedList()
 //   this->head = list.head;   //语义错，浅拷贝
}

//默认赋值，不继承基类的=，可用
template <class T>
SortedSinglyList<T>& SortedSinglyList<T>::operator=(SortedSinglyList<T> &list)//此处不声明显式声明调用基类=
{
    SinglyLinkedList<T>::operator=(list);         	 //调用基类赋值，已重载为深拷贝
    return *this;
}*/

//第9章排序
//9.6   单/双链表的排序算法
//1.  由单链表构造排序单链表，直接插入排序

//重载拷贝构造函数，由单链表构造排序单链表（深拷贝），asc指定升序（true）或降序（false），默认升序。
template <class T>
SortedSinglyList<T>::SortedSinglyList(SinglyList<T> &list, bool asc)
{                                                          //此处默认执行SinglyList<T>()
    this->asc = asc;
    for (Node<T> *p=list.head->next;  p!=NULL;  p=p->next) 
        this->insert(p->data);                             //排序单链表插入，一趟直接插入排序
}
//2.  由单链表构造排序单链表，直接选择排序


//3.  归并两条排序单链表
//归并两条排序单链表，覆盖基类同名函数。两条排序单链表必须次序相同，否则抛出异常
template <class T>
void SortedSinglyList<T>::operator+=(SortedSinglyList<T> &list)
{
    if (this->asc == list.asc)                            //两条排序单链表的次序相同
    {
        Node<T> *front=head, *p=head->next;               //p遍历this单链表，front是p的前驱
        Node<T> *q=list.head->next;                       //q遍历list单链表
        while (p!=NULL && q!=NULL)
            if (this->asc ? p->data < q->data : p->data > q->data)
            {                //比较两条单链表当前结点值，升序时比较<；降序时比较>
                front = p;
                p = p->next;
            }
            else
            {                                              //将q结点插入到front结点之后
                front->next = q;
                q = q->next;
                front = front->next;
                front->next = p;
            }
        
        if (q!=NULL)                                       //将list链表中剩余结点并入当前链表尾
            front->next=q;
        list.head->next = NULL;                            //设置list设置为空单链表
    }
    else throw invalid_argument("两条排序单链表次序不同，不能归并"); //抛出C++ STL无效参数异常
}
