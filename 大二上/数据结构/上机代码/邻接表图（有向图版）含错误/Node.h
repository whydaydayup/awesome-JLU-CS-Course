#ifndef NODE_H
#define NODE_H
class Node
{
private:
    int vername;
    Node* link;
public:
    Node(int tempvername=0,Node* templink=nullptr):vername(tempvername),
                link(templink) { }
    void setvername(int tempvername) { vername = tempvername; }
    void setlink(Node* templink) { link = templink; }
    int getvername() { return vername; }
    Node* getlink() { return link; }
};
#endif // NODE_H
