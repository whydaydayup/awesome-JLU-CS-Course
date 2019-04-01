#ifndef BINTREENODE_H
#define BINTREENODE_H
template <typename T>
class BinTreenode
{
private:
    T data;
    BinTreenode<T>* left;
    BinTreenode<T>* right;
public:
    BinTreenode(const T& item,BinTreenode<T>* lp=nullptr,BinTreenode<T>* rp=nullptr):
        data(item),left(lp),right(rp) {}
    BinTreenode<T>* getleft()const
    {
        return left;
    }
    BinTreenode<T>* getright()const
    {
        return right;
    }
    T getdata()const { return data; }
    void setleft(BinTreenode<T>* lp) { left = lp; }
    void setright(BinTreenode<T>* rp)  { right = rp;}
    void setdata(const T& item) { data = item; }
};
#endif // BINTREENODE_H
