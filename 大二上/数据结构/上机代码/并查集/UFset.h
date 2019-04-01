#ifndef UNIONFINDSET
#define UNIONFINDSET
#include <iostream>
using namespace std;
class UnionFindset
{
private:
    int num;
    int* father;
public:
    UnionFindset():num(0),father(nullptr){ }
    ~UnionFindset()
    {
        if(father!=nullptr)
            delete []father;
    }
    void makeset(int x)
    {
        father[x]=0;
    }
    int Find(int x)
    {
        if(father[x]<=0)
            return x;
        father[x] = Find(father[x]);
        return father[x];
    }
    void unionset(int x,int y)
    {
        int fx(0),fy(0);
        fx = Find(x);
        fy = Find(y);
        if(fx==fy)
            return;
        if(father[fx] < father[y])
            father[fy] = fx;
        else
        {
            if(father[fx]==father[fy])
                father[fy]--;
            father[fx] = fy;
        }
    }
    void create(int n)
    {
        father = new int[n];
        int temp(0);
        for(int i=0;i<n;++i)
        {
            cin >> temp;
            father[i] = temp;
        }
    }
    bool ifsame(int x,int y)
    {
        return Find(x)==Find(y);
    }
};
#endif // UNIONFINDSET
