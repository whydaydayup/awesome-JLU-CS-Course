#include <iostream>
#include "UFset.h"
using namespace std;

int main()
{
    UnionFindset aset;
    cout << "请输入元素个数:" << endl;
    int setnumbers(0);
    cin >> setnumbers;
    cout << "请输入所有元素:" << endl;
    aset.create(setnumbers);
    return 0;
}
