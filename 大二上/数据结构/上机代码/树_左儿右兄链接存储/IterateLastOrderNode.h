#ifndef ITERATELASTORDERNODE_H
#define ITERATELASTORDERNODE_H
template <typename T>
class Treenode;
template <typename T>
class Tree;
class IterateLastOrderNode            //迭代后根遍历辅助结点类
{
private:
    Tree<int>* ptr;
    int flag;
public:
    IterateLastOrderNode(Tree<int>* tempp=nullptr,int aflag=0):ptr(tempp),flag(aflag) {}
    ~IterateLastOrderNode() { delete ptr; }
    Tree<int>* getptr() { return ptr; }
    int getflag() { return flag; }
    void setptr(Tree<int>* tempp) { ptr = tempp; }
    void setflag(int tempflag) { flag = tempflag; }
};
#endif // ITERATELASTORDERNODE_H
