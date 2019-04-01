#ifndef QUEUE_H
#define QUEUE_H
#include "SLnode.h"
template <class T>
class Queue
{
private:
    SLnode<T>* first;
    SLnode<T>* tail;
public:
    Queue() { first = tail = NULL; }
    ~Queue() { clearQueue();  }
    void clearQueue();
    bool deletefirst();
    void inserttail(const T& item);
    bool peekfirst(T& item);
    bool isEmpty() { return first==NULL; }
};
template <class T>
void Queue<T>::clearQueue()
{
    tail = first;
    while(tail!=NULL)
    {
        first = first->next;
        delete tail;
        tail = first;
    }
}
template <class T>
void Queue<T>::inserttail(const T& item)
{
    if(isEmpty())
    {
        first = tail = new SLnode<T>(item,NULL);
    }
    else
    {
        tail->next = new SLnode<T>(item,NULL);
        tail = tail->next;
    }
}
template <class T>
bool Queue<T>::deletefirst()
{
    if(isEmpty())
    {
        return false;
    }
    else
    {
        SLnode<T>* temp(first);
        first = first->next;
        delete temp;
        if(isEmpty())
            tail = NULL;
        return true;
    }
}
template <class T>
bool Queue<T>::peekfirst(T& item)
{
    if(isEmpty())
        return false;
    item = first->data;
    return true;
}
#endif // QUEUE_H
