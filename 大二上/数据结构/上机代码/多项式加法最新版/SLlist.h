//SLlist.h
#ifndef SLLIST_H
#define SLLIST_H
#include <iostream>
#include "SLnode.h"
using namespace std;
template <class T>
class SLlist
{
private:
    SLnode<T>* head;
    SLnode<T>* tail;
    SLnode<T>* current;
    int length;
public:
    SLlist(SLnode<T>* ahead=NULL,SLnode<T>* atail=NULL,SLnode<T>*acurrent=NULL
     ,int alenth=0):head(ahead),tail(atail),current(acurrent),length(alenth) {}
    ~SLlist()
    {
        if(head != NULL)   //若此时链表已空，则不必再人工操作
        {
            if(head->next==NULL)   //只有一个节点
            {
                delete head;
                tail = head = current = NULL;
            }
            else
            {
                while(head==NULL)
                {
                    tail = head->next;
                    delete head;
                    head = tail;
                }
                current = NULL;
            }
        }
    }
    void create(int tempcoef,int tempexp);   //所有的添加操作都委托至create函数
    SLnode<T>* add(SLlist<T>& another);
    bool deleteBehind();
    bool deleteHead();
    bool deleteTail();
    T getCurdata() const;
    int findx(const T& x);
    bool moveCurToNext();
    bool moveCurToHead();
};
template <class T>
void SLlist<T>::create(int tempcoef,int tempexp)
{
    SLnode<T>* temp(NULL);
    temp = new SLnode<T>(tempcoef,tempexp);
    length++;
    if(head==NULL)     //如果是空表
    {
        head = temp;
        current = head;
        tail = head;
    }
    else
    {
        SLnode<T>* ptr(head);
        while(ptr!=NULL)
        {
            if(head->exp < temp->exp)    //如果比头结点都大
            {
                temp->next = head;
                head = temp;
                break;
            }
            if(ptr->exp==temp->exp)      //(比头结点小前提下)若指数相等，则系数相加即可
            {
                ptr->data += temp->data;
                delete temp;
                temp =NULL;
                break;
            }
            if(temp->exp < ptr->exp)
            {
                if(ptr->next==NULL)      //说明temp此时是最小的那个
                {
                    ptr->next = temp;
                    tail = temp;
                    break;
                }
                else
                {
                    if(temp->exp > ptr->next->exp)   //如果比前一项小，比后一项大，那么就插在这
                    {
                        temp->next = ptr->next;
                        ptr->next = temp;
                        break;
                    }
                }
            }
            ptr = ptr->next;
        }
    }
}
template <class T>
SLnode<T>* SLlist<T>::add(SLlist<T>& another)
{
    SLnode<T>* pra(head);
    SLnode<T>* prb(another.head);
    SLnode<T>* chead(NULL);
    SLnode<T>* temp(NULL);
    while(pra!=NULL && prb!=NULL)
    {
        if(pra->exp==prb->exp)
        {
            if(pra->data+prb->data==0)
            {
                pra = pra->next;
                prb = prb->next;
            }
            else
            {
                if(chead==NULL)
                {
                    chead = new SLnode<T>(pra->data+prb->data,pra->exp);
                    temp = chead;
                }
                else
                {
                    temp->next = new SLnode<T>(pra->data+prb->data,pra->exp);
                    temp = temp->next;
                }
                pra = pra->next;
                prb = prb->next;
            }

        }
         else if(pra->exp < prb->exp)
        {
            if(chead==NULL)
            {
                chead = new SLnode<T>(prb->data,prb->exp);
                temp = chead;
            }
            else
            {
                temp->next = new SLnode<T>(prb->data,prb->exp);
                temp = temp->next;
            }
            prb = prb->next;
        }
        else if(pra->exp > prb->exp)
        {
            if(chead==NULL)
            {
                chead = new SLnode<T>(pra->data,pra->exp);
                temp = chead;
            }
            else
            {
                temp->next = new SLnode<T>(pra->data,pra->exp);
                temp = temp->next;
            }
            pra = pra->next;
        }
    }
    //此时把剩下的那个有序链表后续所有节点复制到chead中
    while(prb!=NULL)
    {
        temp->next = new SLnode<T>(prb->data,prb->exp);
        temp = temp->next;
        prb = prb->next;
    }
    while(pra!=NULL)
    {
        temp->next = new SLnode<T>(pra->data,pra->exp);
        temp = temp->next;
        pra = pra->next;
    }
    return chead;
}

template <class T>
bool SLlist<T>::deleteBehind()
{
    if(current->next==NULL || head==NULL)
        return false;
    SLnode<T>* temp(NULL);
    temp = current->next->next;
    delete current->next;
    current->next = temp;
    if(temp==NULL)        //说明current指向的是倒数第二个节点,此时要动尾节点
        tail = current;
    length--;
    return true;
}
template <class T>
bool SLlist<T>::deleteHead()
{
    if(head==NULL)
        return false;
    if(head==tail)         //说明此时只有一个节点
    {
        delete head;
        head = tail = current = NULL;
        length--;
        return true;
    }
    //若多于一个节点
    SLnode<T>* temp(NULL);
    temp = head->next;
    delete head;
    head = temp;
    length--;
    return true;
}
template <class T>
bool SLlist<T>::deleteTail()
{
    if(tail==NULL)
        return false;
    if(head==tail)         //说明此时只有一个节点
    {
        delete tail;
        head = tail = current = NULL;
        length--;
        return true;
    }
    SLnode<T>* temp(head);
    while(temp->next!=tail)   //移动temp至指向链表倒数第二个节点
    {
        temp = temp->next;
    }
    delete tail;
    temp->next = NULL;
    tail = temp;
    length--;
    return true;
}
template <class T>
T SLlist<T>::getCurdata() const
{
    if(current==NULL)
        return false;
    return current->data;
}
template <class T>
int SLlist<T>::findx(const T& x) //默认只有一个节点的值为x
{                                //若有多个节点:整个链表遍历一遍，将值为x的元素
    SLnode<T>* temp(head);       //复制到一个新链表中，再输出新链表
    int i(1);
    for(i=1;i<=length;++i)
    {
        if(temp->data==x)
        {
            break;
        }
        if(temp->next==NULL)     //如果i为0，则查找失败
        {
            i=0;
            break;
        }
        temp = temp->next;
    }
    return i;
}
template <class T>
bool SLlist<T>::moveCurToNext()
{
    if(current == NULL)
        return false;
    current = current->next;
    return true;
}
template <class T>
bool SLlist<T>::moveCurToHead()
{
    current = head;
    return true;
}

#endif // SLLIST_H
