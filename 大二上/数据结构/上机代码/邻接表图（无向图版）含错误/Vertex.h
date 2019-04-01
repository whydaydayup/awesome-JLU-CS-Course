#ifndef VERTEX_H
#define VERTEX_H
#include "Edgenode.h"
class Vertex
{
private:
    int vername;
    Edgenode* adjacent;
public:
    Vertex(int tempvername=0,Edgenode* tempadjacent=nullptr)
             :vername(tempvername),adjacent(tempadjacent) {}
    ~Vertex() { delete adjacent; }
    void setvername(int tempvername) { vername = tempvername; }
    void setadjacent(Edgenode* tempadjacent) {adjacent = tempadjacent; }
    int getvername()const { return vername; }
    Edgenode* getadjacent()const { return adjacent; }
};
#endif // VERTEX_H

