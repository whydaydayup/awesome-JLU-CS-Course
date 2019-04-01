//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//习图4.3（c）用循环双链表作为成员变量实现队列。

#include "CirDoublyList.h"                                 //循环双链表类

template <class T>
class DoublyQueue                                          //链式队列类
{
  private:
    CirDoublyList<T> list;                                 //使用循环双链表存储队列元素

  public:
    //使用默认构造函数和默认析构函数

    bool empty()                                           //判断是否空队列，O(1)
    {
        return list.empty();
    }

    void enqueue(T x)                                      //入队，O(1)
    {
        list.insert(x);                                    //在循环双链表最后插入x元素结点，O(1)
    }  

    T dequeue()                                            //出队，返回队头元素，若队列空则抛出异常，O(1)
    {
        if (!empty())
             return list.remove(0);                        //删除队头结点，返回队头元素，O(1)
        throw out_of_range("空队列，不能执行出队操作");
    }

    friend ostream& operator<<(ostream& out, DoublyQueue<T> &que) //输出队列
    {
        out<<"DoublyQueue:  "<<que.list;
        return out;
    }
};
