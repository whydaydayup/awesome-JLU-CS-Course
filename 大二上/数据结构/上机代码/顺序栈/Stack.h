#ifndef STACK_H
#define STACK_H
//#include <iostream>
//using namespace std;
template <class T>
class Stack
{
private:
    int maxsize;
    T* stackarr;
    int top;
public:
    /*void print()
    {
        for(int i=0;i<=top;++i)
        {
            cout << stackarr[i] << " ";
        }
        cout << endl;
    }*/
    Stack(int themax):maxsize(themax),stackarr(NULL),top(-1)
    {
        stackarr = new T[maxsize];
    }
    ~Stack() { delete[] stackarr; }
    void create(int k,const T& item)
    {
        stackarr[k] = item;
        top++;
    }
    void clearstack()  {  top=-1;}
    bool push(const T& item);
    bool pop();
    bool pop(T& item);
    bool peek(T& item)const;
    bool isEmpty()const { return top==-1;}
    bool isFull()const { return top==maxsize-1;}
};
template <class T>
bool Stack<T>::push(const T& item)
{
    if(isFull())
    {
        return false;
    }
    else
    {
        top++;
        stackarr[top] = item;
    }
    return true;
}
template <class T>
bool Stack<T>::pop()
{
    if(isEmpty())
    {
        return false;
    }
    else
    {
        top--;
    }
    return true;
}
template <class T>
bool Stack<T>::pop(T& item)
{
    if(isEmpty())
    {
        return false;
    }
    else
    {
        item = stackarr[top];
        top--;
    }
    return true;
}
template <class T>
bool Stack<T>::peek(T& item)const
{
    if(isEmpty())
        return false;
    item = stackarr[top];
    return true;
}
#endif // STACK_H
