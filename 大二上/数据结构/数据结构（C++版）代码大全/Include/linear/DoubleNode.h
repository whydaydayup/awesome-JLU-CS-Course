//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.3   双链表
//1. 双链表结点类

template <class T>
class DoubleNode                                           //双链表结点类，T指定结点的元素类型
{
  public:
    T data;                                                //数据域，保存元素
    DoubleNode<T> *prev, *next;                            //地址域（指针域），分别指向前驱结点和后继结点

    DoubleNode()                                           //构造结点，data域未初始化
    {
        this->prev = this->next = NULL;
    }
    //构造结点，data指定数据元素；prev指定前驱结点地址；next指定后继结点地址，默认空值
    DoubleNode(T data, DoubleNode<T> *prev=NULL, DoubleNode<T> *next=NULL)
    {
        this->data = data;                                 //执行T的=赋值运算
        this->prev = prev;
        this->next = next;
    }
};

//习题2
//不需要声明析构函数~DoubleNode()。
/*
//以下声明错误，
template <class T>
class DoubleNode : public Node<T>                      //双链表结点类，继承单链表结点类
{
    DoubleNode<T> *prev;                               //指向前驱结点的指针域
};

//等价于声明如下：
template <class T>
class DoubleNode                                       //双链表结点类
{
    T data;                                           //继承基类的成员变量
    Node<T> *next;                                    //继承基类的成员变量，该指针域的数据类型错误
    DoubleNode<T> *prev;
};*/
