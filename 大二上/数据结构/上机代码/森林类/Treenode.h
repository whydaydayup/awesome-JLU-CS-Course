#ifndef TREENODE_H
#define TREENODE_H
template <typename T>
class Treenode
{
private:
    T data;
    Treenode<T>* firstchild;
    Treenode<T>* nextbrother;
public:
    Treenode(T tempdata,Treenode<T>* tempchild=nullptr,Treenode<T>* tempbrother=nullptr)
            :data(tempdata),firstchild(tempchild),nextbrother(tempbrother) {}
    ~Treenode()
    {
        delete firstchild;
        delete nextbrother;
    }
    void setdata(T tempdata) { data = tempdata; }
    void setfirstchild(Treenode<T>* tempchild) { firstchild = tempchild; }
    void setnextbrother(Treenode<T>* tempbrother) { nextbrother = tempbrother; }
    T getdata()const { return data; }
    Treenode<T>* getfirstchild()const { return firstchild; }
    Treenode<T>* getnextbrother()const { return nextbrother; }
};
#endif // TREENODE_H
