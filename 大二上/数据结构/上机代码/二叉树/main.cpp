#include <iostream>
#include "BinTree.h"
#include "BinTreenode.h"
#include "Stack.h"
using namespace std;

int main()
{
    BinTree<char> tree;
    tree.CreateBinTree();
    tree.preTraverse();
    /*tree.middleTraverse();
    tree.postTraverse();*/
    return 0;
}
