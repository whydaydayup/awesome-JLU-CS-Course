#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BinarySearchTree.h"
#include <queue>
using namespace std;

int main()
{
    int arr[15];
    for(int i=0;i<15;++i)
        arr[i] = 0;
    int temp(0);
    int countarr(0);
    bool flag(true);
    while(countarr<15)
    {
        temp = rand()%(100-1+1)+1;
        for(int i=0;i<countarr;++i)
        {
           if(temp==arr[i])
           {
                flag = false;
                break;
           }

        }
        if(flag==true)
        {
            arr[countarr] = temp;
            countarr++;
            flag = true;
        }
        else
        {
            flag = true;
        }
    }
    for(int i=0;i<15;++i)
        cout << arr[i] << " ";
    cout << endl;
    /*********************2**************************/
    BinarySearchTree<int> atree;
    for(int i=0;i<15;++i)
    {
        atree.Insert(arr[i]);
    }
    atree.InOrder(atree.root);
    cout << endl;
    atree.LevelOrder();
    cout << endl;
    return 0;
}
/*
要产生随机数r， 其范围为 m<=r<=n，可以使用如下公式：
rand()%(n-m+1)+m
*/
