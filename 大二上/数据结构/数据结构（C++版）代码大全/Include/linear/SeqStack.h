//《数据结构（C++版）（第3版）》 作者：叶核亚
//4.1.2  顺序栈类
//第3版，使用顺序表作为栈的成员变量实现栈。

#include "SeqList.h"                                       //顺序表类（第2章）

template <class T>
class SeqStack                                             //顺序栈类
{
  private:
    SeqList<T> list;                                       //使用顺序表存储栈元素

  public:
    SeqStack(){}                                           //默认构造空栈，执行SeqList<T>()，默认容量，可省略
    ~SeqStack(){}                                          ///默认析构，执行~SeqList<T>()，可省略
    bool empty()                                           //判断是否空栈
    {
        return this->list.empty();
    }

    void push(T x)                                         //入栈
    {
        this->list.insert(x);                              //顺序表尾插入元素x，自动扩充容量
    }  

    T pop()                                                //出栈，返回栈顶元素，若栈空则抛出异常
    {
        if (!empty())
            return this->list.remove(list.count()-1);      //顺序表尾删除，返回栈顶元素
        throw logic_error("空栈，不能执行出栈操作");       //抛出逻辑错误异常
    }

    T get()                                                //返回栈顶元素（未出栈），若栈空则抛出异常
    {
        if (!empty())
            return this->list.get(list.count()-1);         //执行T的拷贝构造函数
        throw logic_error("空栈，不能获得栈顶元素"); 
    }

    friend ostream& operator<<<>(ostream& out, SeqStack<T>&stack) //输出栈
    {
        out<<"SeqStack: "<<stack.list;
        return out;
    }
};
