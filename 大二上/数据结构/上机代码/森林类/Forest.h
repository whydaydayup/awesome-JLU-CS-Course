#ifndef FOREST_H
#define FOREST_H
#include "Treenode.h"
#include "IterateLastOrderNode.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
class Forest
{
private:
    Treenode<T>** treespoint;  //指针数组,每个数组元素存放一个树根的指针
    int treescount;
public:
    Forest(Treenode<T>** temptreespoint=nullptr,int temptreescount=0):
        treespoint(temptreespoint),treescount(temptreescount)  {}
    ~Forest() { clearforest(); }
    void createforest()
    {
        cout << "please input the number of trees in this forest:" << endl;
        cin >> treescount;
        treespoint = new Treenode<T>*[treescount];
        for(int i=0;i<treescount;++i)
            createtree(i);
    }
    void createtree(int position)
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
        treespoint[position] = temproot = new Treenode<T>(data);
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
        /*cout << "please input the rootdata of this tree:" <<endl;
        int rootdata(0);
        cin >> rootdata;
        treespoint[i] = new Treenode(rootdata);
        createSubtree(treespoint[i]);*/
    }
    /*void createSubtree(Treenode<T>* t)   //构造以t为根的子树
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
                createSubtree(bigchild);
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
    void clearforest()
    {
        for(int i=0;i<treescount;++i)
        {
            deleteSubtree(treespoint[i]);
            treespoint[i] = nullptr;
        }
        treescount = 0;
        delete []treespoint;
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
    void RPOforest()           //递归先根遍历森林
    {
        for(int i=0;i<treescount;++i)
        {
            recurPreOrder(treespoint[i]);
        }
    }
    void IPOforest()          //迭代先根遍历森林
    {
        for(int i=0;i<treescount;++i)
        {
            iteratePreOrder(treespoint[i]);
        }
    }
    void LOforest()           //层次遍历森林
    {
        queue<Treenode<T>*> aqueue;
        for(int i=0;i<treescount;++i)
        {
            cout << treespoint[i]->getdata();
            aqueue.push(treespoint[i]);
        }
        Treenode<T>* p(nullptr);
        Treenode<T>* q(nullptr);
        while(!aqueue.empty())
        {
            p = aqueue.front();
            aqueue.pop();
            if(p->getfirstchild()!=nullptr)
            {
                q = p->getfirstchild();
                while(q!=nullptr)
                {
                    cout << q->getdata();
                    aqueue.push(q);
                    q = q->getnextbrother();
                }
            }
        }
    }
    void RLOforest()          //递归后根遍历森林
    {
        for(int i=0;i<treescount;++i)
        {
            recurLastOrder(treespoint[i]);
        }
    }
    void ILOforest()         //迭代后根遍历森林
    {
        for(int i=0;i<treescount;++i)
        {
            iterateLastOrder(treespoint[i]);
        }
    }
    //以下是树中原版代码
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
#endif // FOREST_H
