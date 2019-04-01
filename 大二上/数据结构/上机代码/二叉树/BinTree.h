#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "BinTreenode.h"
#include "Stack.h"
using namespace std;
template <typename T>
class BinTree
{
private:
    BinTreenode<T>* root;
    BinTreenode<T>* create()
    {
        BinTreenode<T>* t(nullptr);
        T ch;
        cout << "请输入结点data值:(‘#’为输入结束符)" << endl;
        cin >> ch;
        if(ch=='#')
        {
            return nullptr;
        }
        else
        {
            t = new BinTreenode<T>(ch);
            t->setleft(create());
            t->setright(create());
            return t;
        }
    }
    void preTraverse(BinTreenode<T>* t)const;
    void middleTraverse(BinTreenode<T>* t)const;
    void postTraverse(BinTreenode<T>* t)const;
 public:
    BinTree(BinTreenode<T>* temproot=nullptr): root(temproot) { }
    ~BinTree() { clearBintree(root); }
    void CreateBinTree(){
        root=create();
    }
    void clearBintree(BinTreenode<T>* t) //删除结点t及其左右子树
    {
        if(t!=nullptr)
        {
            clearBintree(t->getleft());
            clearBintree(t->getright());
            delete t;
        }
    }
    BinTreenode<T>* getroot() { return root; }
    void setroot(BinTreenode<T>* t)  { root = t; }
    bool isEmpty() { return root==nullptr; }
    void preTraverse()
    {
        preTraverse(root);
    }
    void middleTraverse()const
    {
        middleTraverse(root);
    }
    void postTraverse()const
    {
        postTraverse(root);
    }
    BinTreenode<T>* findfather(BinTreenode<T>* t,BinTreenode<T>* p);
    BinTreenode<T>* finditem(BinTreenode<T>* t,const T& item)const;
};
template <typename T>
void BinTree<T>::preTraverse(BinTreenode<T>* t)const
{
    if(t!=nullptr)
    {
        std::cout << t->getdata() << std::endl;
        preTraverse(t->getleft());
        preTraverse(t->getright());
    }
}
template <typename T>     //非递归中根遍历
void BinTree<T>::middleTraverse(BinTreenode<T>* t)const
{
    if(t==nullptr)
        return;
    Stack<BinTreenode<T>*> astack(100);
    while(t!=nullptr || !astack.isEmpty())
    {
        while(t!=nullptr)
        {
            astack.push(t);
            t = t->getleft();
        }
        if(astack.isEmpty())
            return;
        astack.pop(t);
        cout << t->getdata() << endl;
        t = t->getright();
    }
}
template <typename T>
void BinTree<T>::postTraverse(BinTreenode<T>* t)const
{
    if(t!=nullptr)
    {
        postTraverse(t->getleft());
        postTraverse(t->getright());
        std::cout << t->getdata() << std::endl;
    }
}
template <typename T>
BinTreenode<T>* BinTree<T>::findfather(BinTreenode<T>* t,BinTreenode<T>* p)
{
    BinTreenode<T>* q;
    if(t==nullptr||p==nullptr)
        return nullptr;
    if(t->getleft()==p || t->getright()==p)
        return t;
    q = findfather(t->getleft(),p);
    if(q!=nullptr)   //若t为p的父节点,则返回t
        return q;
    else             //否则分别在t的左右子树中查找
        return findfather(t->getright(),p);
}
template <typename T>
BinTreenode<T>* BinTree<T>::finditem(BinTreenode<T>* t,const T& item)const
{
    BinTreenode<T>* p(nullptr);
    BinTreenode<T>* q(nullptr);
    if(t==nullptr)
        return nullptr;
    if(t->getdata()==item)
        return t;
    p=finditem(t->getleft(),item);
    if(p!=nullptr)
       return p;
    else
    {
        q = finditem(t->getright(),item);
        return q;
    }
}
#endif // BINTREE_H
