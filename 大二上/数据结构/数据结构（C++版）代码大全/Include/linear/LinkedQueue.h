//《数据结构（C++版）（第3版）》 作者：叶核亚
//4.2.3   链式队列

#include <iostream>
using namespace std;
#include "Node.h"                                          //单链表结点类（第2章）

template <class T>
class LinkedQueue                                          //链式队列类
{
  private:
    Node<T> *front, *rear;                                 //front、rear分别指向队首和队尾结点

  public:
    LinkedQueue();                                         //构造空队列
    ~LinkedQueue();                                        //析构

    bool empty();                                          //判断是否空队列
    void enqueue(T x);                                     //入队
    T dequeue();                                           //出队
    friend ostream& operator<<<>(ostream& out, LinkedQueue<T> &que); //输出队列
};

template <class T>
LinkedQueue<T>::LinkedQueue()                              //构造空队列
{
    this->front = this->rear = NULL;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()                             //析构函数
{
    Node<T> *p=this->front, *q;
    while (p!=NULL)
    {
        q = p;
        p = p->next;
        delete q;
    }
    this->front = this->rear = NULL;
}

template <class T>
bool LinkedQueue<T>::empty()                               //判断是否空队列
{
    return this->front==NULL && this->rear==NULL;
}

template <class T>
void LinkedQueue<T>::enqueue(T x)                          //入队，O(1)
{
    Node<T> *q = new Node<T>(x);
    if (empty())
        this->front = q;                                   //空队插入
    else 
        rear->next = q;                                    //队列尾插入
    this->rear = q;
}  

template <class T>
T LinkedQueue<T>::dequeue()                                //出队，返回队头元素，若队列空则抛出异常，O(1)
{
    if (!empty())
    {
        T x = front->data;                                 //取得队头元素
        Node<T> *p=front;
        this->front = front->next;                         //删除队头结点
        delete p;
        if (this->front==NULL)                             //空队列时，两指针同步
           this->rear = NULL;
        return x;
    }
    throw out_of_range("空队列，不能执行出队操作");
}

template <class T>
ostream& operator<<(ostream& out, LinkedQueue<T> &que)     //输出队列
{
    out<<"LinkedQueue:  (";
    for (Node<T> *p=que.front;  p!=NULL;  p=p->next)
    {
        out<<p->data;        
        if (p->next!=NULL)
            cout<<", ";
    }
    out<<")"<<endl;
    return out;
}
