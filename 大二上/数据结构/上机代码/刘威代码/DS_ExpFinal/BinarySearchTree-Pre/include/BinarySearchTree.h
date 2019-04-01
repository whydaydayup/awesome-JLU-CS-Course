#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    Node(){Left=NULL;Right=NULL;}
    Node(T d){data=d;Left=NULL;Right=NULL;}
    T data;
    Node* Left;
    Node* Right;
};

template <class T>
class BinarySearchTree
{
    public:
        BinarySearchTree();
        virtual ~BinarySearchTree();
        Node<T>* root;
        void Create();
        Node<T>* CreateTree();
        void PreOrder(Node<T>* p);
        void InOrder(Node<T>* p);
        void PostOrder(Node<T>* p);
        void LevelOrder();
        Node<T>* Find(T data);
        Node<T>* GetSection(T data);
        void Insert(T data);
        void DeleteByData(T data);
        void DeleteByPtr(Node<T>* p);
    protected:

    private:
        bool Compare(T a,T b);  //True when a>b
        Node<T>* GetFather(Node<T>* s);
};

#endif // BINARYSEARCHTREE_H
