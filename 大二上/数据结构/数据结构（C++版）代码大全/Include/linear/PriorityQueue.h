//《数据结构（C++版）（第3版）》 作者：叶核亚
//4.3   优先队列

#include "SortedSinglyList.h"                              //排序单链表（升序）类（第2章）
//#include "SortedCirDoublyList.h"                  //按升序排序的循环双链表类

template <class T>
class PriorityQueue                                       //优先队列类，元素按优先级升序排列
{
  private:
    SortedSinglyList<T> list;                              //使用排序单链表存储队列元素
//    SortedCirDoublyList<T> list; 

  public:
    //构造空队列，asc指定升序（true，默认）或降序（false）；list(asc)声明执行成员变量list的构造函数SortedSinglyList(asc)
    PriorityQueue(bool asc=true):list(asc){}
//    ~PriorityQueue(){}                                     //析构，执行~SortedSinglyList()

    bool empty();                                        //判断是否空队列
    void enqueue(T x);                                     //入队
    T dequeue();                                           //出队
    friend ostream& operator<<<>(ostream& out, PriorityQueue<T> &que); //输出队列
};

template <class T>
bool PriorityQueue<T>::empty()                           //判断是否空队列
{
    return this->list.empty();
}

template <class T>
void PriorityQueue<T>::enqueue(T x)                        //入队
{
    this->list.insert(x);                                  //排序单链表插入，由x元素大小确定插入位置
}  

template <class T>
T PriorityQueue<T>::dequeue()                              //出队，返回队头元素，若队列空则抛出异常 
{
    if (!empty())
    {
        T x = this->list.get(0);                           //取得队头元素
        this->list.removeFirst(x);
        return x;
    }
    throw out_of_range("空队列，不能执行出队操作");
}

template <class T>
ostream& operator<<(ostream& out, PriorityQueue<T> &que)   //输出队列
{
    out<<"PriorityQueue:  "<<que.list;
    return out;
}
