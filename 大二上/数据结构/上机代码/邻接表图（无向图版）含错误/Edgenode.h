#ifndef EDGENODE_H
#define EDGENODE_H
class Edgenode
{
private:
    int veradj;
    int weight;
    Edgenode* link;
public:
    Edgenode(int tempveradj=0,int tempweight=0,Edgenode* templink=nullptr)
              :veradj(tempveradj),weight(tempweight),link(templink) {}
    ~Edgenode() { delete link; }
    int getveradj()const { return veradj; }
    int getweight()const { return weight; }
    Edgenode* getlink()const { return link; }
    void setveradj(int tempveradj) { veradj = tempveradj; }
    void setweight(int tempweight) { weight = tempweight; }
    void setlink(Edgenode* templink) { link = templink; }
};
#endif // EDGENODE_H

