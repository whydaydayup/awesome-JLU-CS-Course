//《数据结构（C++版）（第3版）》 作者：叶核亚
//4.2.2   顺序队列
//3. 顺序循环队列类

#include <iostream>
using namespace std;

template <class T>
class SeqQueue                                             //顺序循环队列类
{
  private:
    T *element;                                            //动态数组存储队列的数据元素
    int length;                                            //队列的数组容量
    int front, rear;                                       //队列首尾下标

  public:
    SeqQueue();                                            //构造空队列
    ~SeqQueue();                                           //析构函数 

    bool empty();                                          //判断是否空队列
    void enqueue(T x);                                     //入队
    T dequeue();                                           //出队，返回队头元素
    friend ostream& operator<<<>(ostream& out, SeqQueue<T> &que); //输出队列
};

template <class T>
SeqQueue<T>::SeqQueue()                                    //构造空队列
{
    this->length = 32;                                     //默认数组容量
    this->element = new T[this->length];
    this->front = this->rear = 0;                          //设置空队列
}

template <class T>
SeqQueue<T>::~SeqQueue()                                   //析构函数
{
    delete []this->element;
}

template <class T>
bool SeqQueue<T>::empty()                                  //判断队列是否为空，若空返回true
{
    return this->front==this->rear;
}

template <class T>
void SeqQueue<T>::enqueue(T x)                             //入队，尾插入，O(1)
{
    if (front==(rear+1) % length)                          //若队列满，则扩充数组容量
    {
        T *temp = this->element;  
        this->element = new T[this->length*2];
        int j=0;
        for (int i=front;  i!=rear;  i=(i+1)%length)       //按队列元素次序复制数组元素
            this->element[j++] = temp[i];
        this->front = 0;
        this->rear = j;
        this->length *=2;
    }
    this->element[this->rear] = x;
    this->rear = (rear+1) % length;
}

template <class T>
T SeqQueue<T>::dequeue()                                   //出队，返回队头元素，若队列空则抛出异常。头删除，O(1)
{
    if (!empty())
    {
        T x = this->element[front];
        this->front = (front+1) % length;
        return x;
    }
    throw out_of_range("空队列，不能执行出队操作");
}

template <class T>
ostream& operator<<(ostream& out, SeqQueue<T> &que)        //输出队列
{
    out<<"SeqQueue: (";
    for (int i=que.front;  i!=que.rear;  i=(i+1) % que.length)
        out<<que.element[i]<<" ";
    out<<")"<<endl;
    return out;
}
