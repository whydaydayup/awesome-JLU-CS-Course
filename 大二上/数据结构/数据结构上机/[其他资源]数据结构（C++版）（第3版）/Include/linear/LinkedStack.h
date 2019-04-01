//《数据结构（C++版）（第3版）》 作者：叶核亚
//4.1.3   链式栈
//用单链表作为成员变量实现栈。

#include "SinglyList.h"                                    //单链表类（第2章）

template <class T>
class LinkedStack                                          //链式栈类
{
  private:
    SinglyList<T> list;                                    //使用单链表存储栈元素

  public:
    LinkedStack(){}                                        //默认构造空栈，执行SinglyList<T>()，可省略
    ~LinkedStack(){}                                       ///默认析构，执行~SinglyList<T>()，可省略
    bool empty()                                           //判断是否空栈
    {
        return this->list.empty();
    }

    void push(T x)                                         //入栈
    {
        this->list.insert(0, x);                           //单链表头插入元素x
    }  

    T pop()                                                //出栈，返回栈顶元素，若栈空则抛出异常
    {
        if (!empty())
            return this->list.remove(0);                   //单链表头删除，返回栈顶元素
        throw logic_error("空栈，不能执行出栈操作");
    }

    T get()                                                //返回栈顶元素（未出栈），若栈空则抛出异常
    {
        if (!empty())
            return this->list.get(0);
        throw logic_error("空栈，不能获得栈顶元素"); 
    }

    friend ostream& operator<<<>(ostream& out, LinkedStack<T>&stack) //输出栈
    {
        out<<"LinkedStack: "<<stack.list;
        return out;
    }
};
