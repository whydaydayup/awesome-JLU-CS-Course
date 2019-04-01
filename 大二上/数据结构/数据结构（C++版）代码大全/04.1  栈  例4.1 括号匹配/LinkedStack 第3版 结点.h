//4.1.3   链式栈
//第3版初稿，使用单链表结点作为成员变量实现栈。

#include <iostream>
using namespace std;
#include "Node.h"                                         //单链表结点类（见第2章）

template <class T>
class LinkedStack                                         //链式栈类
{
  private:
    Node<T> *top;                                         //指向栈顶结点的指针

  public:
    LinkedStack();                                        //构造空栈
    ~LinkedStack();                                       //析构
    bool empty();                                       //判断是否空栈
    void push(T x);                                       //入栈
    T pop();                                              //出栈
    T get();                                              //返回栈顶元素，未出栈
    friend ostream& operator<<<>(ostream& out, LinkedStack<T> &stack); //输出栈
};

template <class T>
LinkedStack<T>::LinkedStack()                              //构造空栈
{
    this->top = NULL;                                      //没有头结点
}

template <class T>
LinkedStack<T>::~LinkedStack()                             //析构函数
{
    Node<T> *p=this->top, *q;
    while (p!=NULL)
    {   q = p;
        p = p->next;
        delete q;
    }
    this->top = NULL;
}

template <class T>
bool LinkedStack<T>::empty()                             //判断是否空栈
{
    return this->top==NULL;
}

template <class T>
void LinkedStack<T>::push(T x)                             //入栈，头插入
{
    this->top = new Node<T>(x, this->top);                 //x结点作为新的栈顶结点
}  

template <class T>
T LinkedStack<T>::pop()                                    //出栈，返回栈顶元素，若栈空则抛出异常
{
    if (!empty())
    {
        T x = this->top->data;                             //头删除
        Node<T> *p=this->top;
        this->top = this->top->next;
        delete p;                                          //删除原栈顶结点
        return x;                                          //返回原栈顶元素
    }
    throw out_of_range("空栈，不能出栈");
}

template <class T>
T LinkedStack<T>::get()                                    //返回栈顶元素，若栈空则抛出异常
{
    if (!empty())
        return this->top->data;
    throw out_of_range("空栈，不能获得栈顶元素"); 
}

template <class T>
ostream& operator<<(ostream& out, LinkedStack<T> &stack)   //输出栈
{
    out<<"LinkedStack: (";
    for (Node<T> *p=stack.top;  p!=NULL;  p=p->next)
    {
        out<<p->data;
        if (p->next!=NULL)
            cout<<", ";
    }
    out<<")"<<endl;
    return out;
}
