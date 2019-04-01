#include <iostream>
#include "SLlist.h"
#include "SLnode.h"
using namespace std;

int main()
{
    SLlist<int> alist;
    int arr[5]={1,2,3,4,5};
    alist.create(5,arr);
    alist.moveCurToHead();
    alist.insertBehind(9);
    alist.print();
    cout << endl;
    alist.insertInHead(8);
    alist.print();
    cout << endl;
    alist.insertInTail(6);
    alist.print();
    cout << endl;
    alist.deleteBehind();
    alist.print();
    cout << endl;
    alist.deleteHead();
    alist.print();
    cout << endl;
    alist.deleteTail();
    alist.print();
    cout << endl;
    cout << alist.findx(3);
    cout << endl;
    cout << alist.getCurdata();
    cout << endl;
    cout << alist.getK(4);
    cout << endl;
    alist.storeInCur(7);
    alist.print();
    cout << endl;
    alist.moveCurToNext();
    alist.storeInCur(8);
    alist.print();
    cout << endl;
    return 0;
}
