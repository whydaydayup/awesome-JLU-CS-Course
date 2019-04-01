//2.3.3   双链表
//4.  排序循环双链表

#include "CirDoublyList.h"                                 //循环双链表类
//？？
template <class T>
class SortedCirDoublyList : public CirDoublyList<T>        //按升序排序的循环双链表类，继承带头结点的循环双链表类
{
  public:
    SortedCirDoublyList(){}                                //构造空双链表，自动执行CirDoublyList<T>()
    SortedCirDoublyList(T values[], int n);                 //构造由指定数组提供元素的双单链表

    DLinkNode<T>* insert(T x);                             //插入结点，根据元素大小插入在合适位置
    void removeFirst(T key);                               //删除首次出现的关键字值为key结点

    //第9章排序
    SortedCirDoublyList(HSLinkedList<T> &list);  //深拷贝构造函数，由单链表list构造排序循环双链表，直接插入排序
    void merge(SortedCirDoublyList<T> &list);    //归并两条排序循环双链表 
    SortedCirDoublyList(CirDoublyList<T> list); //深拷贝构造方法，由循环双链表list构造排序循环双链表，快速排序算法
    void quickSort(DLinkNode<T> *begin, DLinkNode<T> *end);//一趟快速排序，begin、end指定序列的开始和最后结点，递归算法
};
//    ~SortedCirDoublyList(){}                     //不能继承基类析构函数，自动执行~CirDoublyList<T>()

template <class T>
SortedCirDoublyList<T>::SortedCirDoublyList(T values[], int n)  //构造由指定数组提供元素的双链表
{                                                //此处自动执行CirHDLinkedList<T>()，创建头结点
    for (int i=0; i<n; i++)   
        this->insert(values[i]);
}

template <class T>
DLinkNode<T>* SortedCirDoublyList<T>::insert(T x)//插入结点，根据元素大小插入在合适位置，T必须重载>运算符
{
    DLinkNode<T> *p=this->head->prev, *q=NULL;
    if (p!=head && x > p->data)                  //最大值插入在头结点之前，即插入在链尾，T必须重载>运算符
    {
        q = new DLinkNode<T>(x, p, this->head);  //插入在head结点之前、p结点之后
        this->head->prev = q;
        p->next = q;
    }
    else
    {   p=this->head->next;
        while (p!=this->head && x > p->data)     //寻找插入位置，插入在等值结点之前，T必须重载>运算符
            p = p->next;
        q = new DLinkNode<T>(x, p->prev, p);     //插入在p结点之前
        p->prev->next = q;
        p->prev = q;
    }
    return q;
}

//删除首次出现的值为x结点，若操作成功返回true。T必须重载>和==运算符
template <class T>
bool SortedCirDoublyList<T>::remove(T x)
{
    DLinkNode<T> *p=this->head->next;
    while (p!=this->head && x > p->data)         //寻找待删除结点，T必须重载>运算符
        p = p->next;
    if (x == p->data)                            //删除p结点，T必须重载==运算符
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        return true;
    }
    return false;
}

//第9章排序
//深拷贝构造函数，由单链表list构造排序循环双链表。直接插入排序（升序）算法
template <class T>
SortedCirDoublyList<T>::SortedCirDoublyList(HSLinkedList<T> &list)
{                       //此处自动执行基类的默认构造函数，创建空循环双链表
    DLinkNode<T> *p=this->head;
    for (Node<T> *q=list.head->next;  q!=NULL;  q=q->next) 
    {           //将list单链表中结点依次逐个复制插入到this单链表中，根据q->data值的大小决定插入位置
        DLinkNode<T> *t;
        if (p!=this->head && q->data > p->data)
        {
            while (p!=this->head && q->data > p->data)     //q->data较大，p向后走
                p = p->next;
            t = new DLinkNode<T>(q->data, p->prev, p);     //t插入在p结点之前
            p->prev->next = t;
            p->prev = t;
        }
        else
        {
            while (p!=this->head && q->data < p->data)     //q->data较小，p向前走
                p = p->prev;
            t = new DLinkNode<T>(q->data, p, p->next);     //t插入在p结点之后
            p->next->prev = t;
            p->next = t;
        }
        p=t;
    }
}

//深拷贝构造方法，由循环双链表list构造排序循环双链表，快速排序算法
template <class T>
SortedCirDoublyList<T>::SortedCirDoublyList(CirDoublyList<T> list)  
{   //此处自动执行基类的默认构造函数CirDoublyList<T>()。list已获得实际参数单链表的深拷贝
    DLinkNode<T> *tmp=this->head;
    this->head = list.head;                           //this获得参数list的深拷贝单链表
    list.head=tmp;                                    //设置单链表list为空
    quickSort(this->head->next, this->head->prev);
}    
//一趟快速排序，begin、end指定序列的开始和最后结点，递归算法
template <class T>
void SortedCirDoublyList<T>::quickSort(DLinkNode<T> *begin, DLinkNode<T> *end)
{
    if (begin!=end && begin!=end->next)                    //排除空和单结点链表情况
    {
        DLinkNode<T> *front=begin, *rear=end;
        T vot=front->data;                                 //第一个值作为基准值
        while (front!=rear)                                //一趟排序
        {
            while (front!=rear && rear->data >vot)         //从后向前寻找较小值
                rear=rear->prev;
            if (front!=rear)
            {   front->data = rear->data;                  //较小元素向前移动
                front=front->next;
            }
            while (front!=rear && front->data < vot)       //从前向后寻找较大值
                front=front->next;
            if (front!=rear)
            {   rear->data = front->data;                  //较大元素向后移动
                rear=rear->prev;
            }
        }
        front->data=vot;                                   //基准值到达最终位置
        quickSort(begin, rear->prev);                      //前端子序列再排序，递归调用
        quickSort(front->next, end);                       //后端子序列再排序，递归调用
    }
}

//归并两条排序循环双链表，将list中所有结点归并到当前排序循环双链表中，合并后设置list空
template <class T>
void SortedCirDoublyList<T>::merge(SortedCirDoublyList<T> &list)  
{
    DLinkNode<T> *p=this->head->next;
    DLinkNode<T> *q=list.head->next;
    while (p!=this->head && q!=list.head)
        if (p->data < q->data)                        //比较两个链表当前结点值
            p = p->next;
        else                                          //将q结点插入到结点之前
        {   q->prev = p->prev;
            p->prev->next = q;
            p->prev = q;
            q = q->next;
            q->prev->next = p;
        }
    if (q!=list.head)                                 //将list链表中剩余结点并入当前链表尾
    {
        this->head->prev->next = q;
        q->prev = this->head->prev;
        while (q->next!=list.head)
            q = q->next;
        q->next = this->head;
        this->head->prev = q;
    }
    list.head->next = list.head;                      //合并后设置list为空
    list.head->prev = list.head;
}
