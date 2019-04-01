//4.1.2  顺序栈类
//第3版初稿，使用数组作为栈的成员变量实现栈。

#include <iostream>
using namespace std;

template <class T>
class SeqStack                                             //顺序栈类
{
  private:
    T *element;                                            //动态数组存储栈的数据元素
    int length;                                            //数组容量
    int top;                                               //栈顶元素下标

  public:
    SeqStack();                                            //构造空栈
    ~SeqStack();                                           //析构函数 

    bool empty();                                        //判断是否空栈
    void push(T x);                                        //入栈
    T pop();                                               //出栈
    T get();                                               //返回栈顶元素，未出栈
    friend ostream& operator<<<>(ostream& out, SeqStack<T> &stack);    //输出栈
};

template <class T>
SeqStack<T>::SeqStack()                                    //构造空栈
{
    this->length = 64;                                     //数组容量取默认值
    this->element = new T[this->length];
    this->top = -1;
}

template <class T>
SeqStack<T>::~SeqStack()                                   //析构函数
{
    delete []this->element;
}

template <class T>
bool SeqStack<T>::empty()                                //判断栈是否为空，若空返回true
{
    return this->top==-1;
}

template <class T>
void SeqStack<T>::push(T x)                                //入栈。尾插入
{
    if (this->top==this->length-1)                         //若栈满，则扩充数组容量
    {
        T *temp = this->element;  
        this->element = new T[this->length*2];             //重新申请一个容量更大的数组
        for (int i=0; i<this->length; i++)                 //复制数组元素，O(n)
            this->element[i] = temp[i];
        this->length *=2;
    }
    this->top++;
    this->element[this->top] = x;
}

template <class T>
T SeqStack<T>::get()                                       //返回栈顶元素，未出栈，若栈空则抛出异常
{
    if (!empty())
        return this->element[top];                         //执行T的拷贝构造函数
    throw out_of_range("空栈，不能获得栈顶元素");          //抛出异常
}

template <class T>
T SeqStack<T>::pop()                                       //出栈，返回栈顶元素，若栈空则抛出异常。尾删除
{
    if (!this->empty())
        return this->element[this->top--];                 //先取返回值，再top--
    throw out_of_range("空栈，不能执行出栈操作");          //抛出异常
}

template <class T>
ostream& operator<<(ostream& out, SeqStack<T> &stack)      //输出栈
{
    out<<"SeqStack: (";
    for (int i=0; i<stack.top; i++)
        out<<stack.element[i]<<", ";
    if (!stack.empty())
        out<<stack.element[stack.top];
    out<<")\n";
    return out;
}
