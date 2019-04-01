#ifndef TREE_H
#define TREE_H
#include "Treenode.h"
#include "IterateLastOrderNode.h"   //迭代后根遍历辅助结点类
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <typename T>
class Tree
{
private:
    Treenode<T>* root;
public:
    Tree(Treenode<T>* temproot=nullptr):root(temproot) {}
    ~Tree() { cleartree(); }
    void setroot(Treenode<T>* temproot) { root = temproot; }
    Treenode<T>* getroot() { return root; }
    void createtree()     //使用辅助队列来构造树(正确)
    {
        queue<Treenode<T>*> aqueue;
        cout << "是否是空树? 空树请输入0,否则输入1." << endl;
        int flag(1);
        cin >> flag;
        if(flag==0)
            return;
        cout << "请输入根:" << endl;
        int data(0);       //存放当前节点值
        int numbers(0);    //存放当前节点子节点个数
        Treenode<T>* temproot(nullptr);
        Treenode<T>* tempsub(nullptr);
        temproot = new Treenode<T>(data);
        aqueue.push(temproot);
        while(!aqueue.empty())
        {
            temproot = aqueue.front();
            aqueue.pop();
            cout << "请输入当前节点的子节点个数:" << endl;
            cin >> numbers;
            for(int i=0;i<numbers;++i)
            {
                cout << "请输入子节点值:" << endl;
                cin >> data;
                tempsub = new Treenode<T>(data);
                if(i==0) //大孩子
                {
                    temproot->setfirstchild(tempsub);
                    temproot = tempsub;
                }
                else
                {
                    temproot->setnextbrother(tempsub);
                    temproot = tempsub;
                }
                aqueue.push(tempsub);
            }
        }
    }
    void cleartree()
    {
        if(getroot()==nullptr)
            return;
        deleteSubtree(getroot());
        setroot(nullptr);
    }
    void deleteSubtree(Treenode<T>* p)
    {
        if(p!=nullptr)
        {
            Treenode<T>* q(nullptr);
            q = p->getfirstchild();
            Treenode<T>* next(nullptr);
            while(q!=nullptr)
            {
                next = q->getnextbrother();
                deleteSubtree(q);
                q = next;
            }
            delete p;
        }
    }
    /*void createtree() //用构造二叉树的方式构造整棵树(是错误的)
    {
        cout << "please input the data of root node:" << endl;
        int rootdata(0);
        cin >> rootdata;
        setroot(new Treenode<T>(rootdata));
        createSubtree(root);
    }
    void createSubtree(Treenode<T>* t)   //构造以t为根的子树
    {
        int n(0);
        int value(0);
        cout << "please input subnode numbers of current node:" << endl;
        cin >> n;                        //n保存当前节点子节点个数
        Treenode<T>* bigchild(nullptr);  //大孩子
        Treenode<T>* prechild(nullptr);  //thischild的父亲
        Treenode<T>* thischild(nullptr);
        for(int i=1;i<=n;++i)
        {
            cout << "请输入第"<<i<<"个子节点的值" << endl;
            cin >> value;
            if(i==1)           //说明是大孩子节点
            {
                bigchild = new Treenode<T>(value);
                t->setfirstchild(bigchild);
                prechild = bigchild;
            }
            else              //非大孩子结点
            {
                thischild = new Treenode<T>(value);
                prechild->setnextbrother(thischild);
                prechild = thischild;
                createSubtree(thischild);
            }
        }
    }*/
    void recurPreOrder(Treenode<T>* temproot)const  //递归先根遍历
    {
        if(temproot!=nullptr)
        {
            cout << temproot->getdata() << endl;
            Treenode<T>* childtree(nullptr);
            childtree = temproot->getfirstchild();
            while(childtree!=nullptr)
            {
                recurPreorder(childtree);
                childtree = childtree->getnextbrother();
            }
        }
    }
    void iteratePreOrder(Treenode<T>* temproot)const //迭代先根遍历
    {
        if(temproot==nullptr)
            return;
        stack<int> astack;
        Treenode<T>* tempptr(nullptr);
        do
        {
            while(tempptr!=nullptr)
            {
                cout << tempptr->getdata() <<endl;
                astack.push(tempptr);
                tempptr = tempptr->getfirstchild();
            }
            while(tempptr==nullptr && !astack.empty())
            {
                astack.pop(tempptr);
                tempptr = tempptr->getnextbrother();
            }
        }while(!astack.empty());
    }
    void levelOrder(Treenode<T>* temproot)const     //层次遍历
    {
        queue<int> aqueue;
        if(temproot!=nullptr)
        {
            Treenode<T>* tempptr(nullptr);
            aqueue.push(temproot);
            while(!aqueue.empty())
            {
                tempptr = aqueue.front();
                aqueue.pop();
                cout << tempptr->getdata() << endl;
                tempptr = tempptr->getfirstchild();
                while(tempptr!=nullptr)
                {
                    aqueue.push(tempptr);
                    tempptr = tempptr->getnextbrother();
                }
            }
        }
    }
    void recurLastOrder(Treenode<T>* temproot)const  //递归后根遍历
    {
        if(temproot!=nullptr)
        {
            Treenode<T>* thechild(nullptr);
            thechild = temproot->getfirstchild();
            while(thechild!=nullptr)
            {
                recurLastOrder(thechild);
                thechild = thechild->getnextbrother();
            }
            cout << thechild->getdata() <<endl;
        }
    }
    void iterateLastOrder(Treenode<T>* temproot)  //迭代后根遍历
    {
        if(temproot==nullptr)
            return;
        stack<IterateLastOrderNode*> astack;    //辅助工作栈
        IterateLastOrderNode* curAssisNode(nullptr);
        IterateLastOrderNode* leftAssisNode(nullptr);
        IterateLastOrderNode* rightAssisNode(nullptr);
        curAssisNode = new IterateLastOrderNode;
        curAssisNode->setptr(temproot);
        curAssisNode->setflag(0);
        astack.push(curAssisNode);
        int i=0;
        while(!astack.empty())
        {
            curAssisNode = astack.top();
            temproot = curAssisNode->getptr();
            i = curAssisNode->getflag();
            if(i==0)           //说明还未遍历任何子树，准备遍历左子树
            {
                curAssisNode->setflag(1);
                astack.push(curAssisNode);
                if((temproot->getfirstchild())!=nullptr)
                {
                    leftAssisNode = new IterateLastOrderNode(temproot->getfirstchild(),0);
                    leftAssisNode->setflag(0);
                    astack.push(leftAssisNode);
                }
            }
            if(i==1)           //已遍历完左子树，准备遍历右子树
            {
                curAssisNode->setflag(2);
                astack.push(curAssisNode);
                if((temproot->getnextbrother())!=nullptr)
                {
                    rightAssisNode = new IterateLastOrderNode(temproot->getnextbrother(),0);
                    rightAssisNode->setflag(0);
                    astack.push(rightAssisNode);
                }
            }
            if(i==2)           //temproot所指结点的左右子树都遍历完，访问该节点本身
                cout << temproot->getdata() << endl;
        }
    }
};
#endif // TREE_H
