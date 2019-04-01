#include "BinarySearchTree.h"
#include <queue>

#define STOP_NODE -1    //Use -1 when int
//#define STOP_NODE '#'    //Use '#' when char

template class BinarySearchTree<int>;
template class BinarySearchTree<char>;

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root=NULL;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    //dtor
}

template <class T>
void BinarySearchTree<T>::Create()
{
    root=CreateTree();
}

template <class T>
Node<T>* BinarySearchTree<T>::CreateTree()
{
    T data;
    cin>>data;
    if(data==STOP_NODE)
    {
        return NULL;
    }else
    {
        Node<T>* p=new Node<T>(data);
        p->Left=CreateTree();
        p->Right=CreateTree();
        return p;
    }
}

template <class T>
void BinarySearchTree<T>::PreOrder(Node<T>* p)
{
    if(p!=NULL)
    {
        cout<<p->data<<' ';
        PreOrder(p->Left);
        PreOrder(p->Right);
    }else
    {
        //cout<<'#';
    }
}

template <class T>
void BinarySearchTree<T>::InOrder(Node<T>* p)
{
    if(p!=NULL)
    {
        InOrder(p->Left);
        cout<<p->data<<' ';
        InOrder(p->Right);
    }else
    {
        //cout<<'#';
    }
}

template <class T>
void BinarySearchTree<T>::PostOrder(Node<T>* p)
{
    if(p!=NULL)
    {
        PostOrder(p->Left);
        PostOrder(p->Right);
        cout<<p->data<<' ';
    }else
    {
        //cout<<'#';
    }
}

template <class T>
void BinarySearchTree<T>::LevelOrder()
{
    if(root!=NULL)
    {
        queue<Node<T>*>* q=new queue<Node<T>*>();
        q->push(root);
        while(!q->empty())
        {
            Node<T>* p=q->front();
            q->pop();
            cout<<p->data<<' ';
            if(p->Left!=NULL)
            {
                q->push(p->Left);
            }
            if(p->Right!=NULL)
            {
                q->push(p->Right);
            }
        }
    }
}

template <class T>
Node<T>* BinarySearchTree<T>::GetSection(T data)    //Get right section to insert data.
{
    Node<T>* p=root;
    Node<T>* pPrev=NULL;
    while(p!=NULL)
    {
        if(data<p->data)    //Call Compare when not operated.
        {
            pPrev=p;
            p=p->Left;
        }else if(data>p->data)
        {
            pPrev=p;
            p=p->Right;
        }else
        {
            return NULL;    //Return NULL when data exists.
        }
    }
    //cout<<pPrev->data<<endl;
    return pPrev;
}

template <class T>
Node<T>* BinarySearchTree<T>::Find(T data)
{
    bool hasFound;
    Node<T>* p=root;
    while(p!=NULL&&!hasFound)
    {
        if(data<p->data)    //Call Compare function when it's not operated.
        {
            p=p->Left;
        }else if(data>p->data)
        {
            p=p->Right;
        }else
        {
            return p;
        }
    }
    return p;
}

template <class T>
void BinarySearchTree<T>::Insert(T data)
{
    if(root==NULL)
    {
        root=new Node<T>(data);
    }else
    {
        Node<T>* p=GetSection(data);
        if(p!=NULL)             //Data does not exist. p is the mid node of the neighbor section.
        {
            if(data<p->data)
            {
                Node<T>* n=new Node<T>(data);
                p->Left=n;
            }else if(data>p->data)
            {
                Node<T>* n=new Node<T>(data);
                p->Right=n;
            }
        }else
        {
            cout<<endl<<"Data Already Exists!"<<endl;
        }
    }
}

template <class T>
void BinarySearchTree<T>::DeleteByData(T data)
{
    Node<T>* p=Find(data);
    if(p==NULL)
    {
        cout<<endl<<"No Such Data!"<<endl;
    }else
    {
        DeleteByPtr(p);
    }
}

template <class T>
void BinarySearchTree<T>::DeleteByPtr(Node<T>* p)
{
    Node<T>* pFather=GetFather(p);
    if(pFather==NULL)
    {
        pFather=new Node<T>();
        pFather->Left=root;
    }
    if(p->Right==NULL)
    {
        Node<T>* t=p->Left;
        if(pFather->Left==p)
        {
            pFather->Left=t;
        }else if(pFather->Right==p)
        {
            pFather->Right=t;
        }
        if(p==root)
        {
            root=t;
        }
        delete p;
    }else if((p->Right)->Left==NULL)
    {
        Node<T>* t=p->Right;
        t->Left=p->Left;
        if(pFather->Left==p)
        {
            pFather->Left=t;
        }else if(pFather->Right==p)
        {
            pFather->Right=t;
        }
        if(p==root)
        {
            root=t;
        }
        delete p;
    }else if((p->Right)->Left!=NULL)
    {
        Node<T>* pnew=p->Right;
        while(pnew->Left!=NULL)
        {
            pnew=pnew->Left;
        }
        (p->Right)->Left=pnew->Right;
        pnew->Left=p->Left;
        pnew->Right=p->Right;
        if(pFather->Left==p)
        {
            pFather->Left=pnew;
        }else if(pFather->Right==p)
        {
            pFather->Right=pnew;
        }
        if(p==root)
        {
            root=pnew;
        }
        delete p;
    }
}

template <class T>
Node<T>* BinarySearchTree<T>::GetFather(Node<T>* s)
{
    if(s!=NULL)
    {
        queue<Node<T>*>* q=new queue<Node<T>*>();
        q->push(root);
        while(!q->empty())
        {
            Node<T>* p=q->front();
            q->pop();
            if(p->Left==s||p->Right==s)
            {
                return p;
            }
            if(p->Left!=NULL)
            {
                q->push(p->Left);
            }
            if(p->Right!=NULL)
            {
                q->push(p->Right);
            }
        }
    }else return NULL;
    return NULL;
}
