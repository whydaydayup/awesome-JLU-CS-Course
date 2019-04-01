#ifndef SLNODE_H
#define SLNODE_H
#include <iostream>
template <class T>
class SLnode
{
public:
    T data;
    SLnode<T>* next;
    SLnode(SLnode* nextnode=NULL):next(nextnode) {}
    SLnode(const T& item,SLnode* nextnode=NULL):data(item),next(nextnode) {}
};
#endif // SLNODE_H

