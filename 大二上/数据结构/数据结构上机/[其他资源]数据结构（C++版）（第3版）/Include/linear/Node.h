//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.2   单链表
//1.单链表结点类

template <class T>
class Node                                       //单链表结点类，T指定结点的元素类型
{
  public:
    T data;                                      //数据域，保存数据元素
    Node<T> *next;                               //地址域（指针域），指向后继结点

    Node()                                       //构造结点，data域未初始化
    {
        this->next = NULL;                       //指针赋值
    }
    Node(T data, Node<T> *next=NULL)             //构造结点，data指定数据元素；next指定后继结点地址，默认空值
    {
        this->data = data;                       //执行T的=赋值运算
        this->next = next;                       //指针赋值
    }
};

//【习2.3】  单链表结点类问题讨论。
//不需要声明析构函数~Node()，因为本类没有动态申请存储空间，创建结点在单链表的操作中。
/*
template <class T>
Node<T>::Node(Node<T> node)        //默认拷贝构造函数为浅拷贝
{
    this->data = node.data; 
    this->next = node.next;
}*/
