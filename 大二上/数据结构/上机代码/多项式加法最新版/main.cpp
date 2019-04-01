#include <iostream>
#include "SLlist.h"
#include "SLnode.h"
using namespace std;
int main()
{
    cout << "测试数据:" << endl;
    cout << "3" << endl;
    cout << "1 2 1 1 1 3"<<endl;
    cout << "4" << endl;
    cout << "1 3 1 2 1 1 1 4"<<endl;
    cout << "*****************************" <<endl;
    SLlist<int> alist;
    SLlist<int> blist;
    int tempcoef(0);
    int tempexp(0);
    cout << "please input term numbers of the first polynomial:" << endl;
    int n(0);
    cin >> n;
    while(n<0)
    {
        cout << "input false n!"<<endl;
        cin>>n;
    }
    cout << "please input all coefs and exps of the terms:" << endl;
    for(int i=0;i<n;++i)
    {
        cin >> tempcoef >> tempexp;
        alist.create(tempcoef,tempexp);
    }
    cout << "please input the term numbers of another polynomial:" <<endl;
    cin >> n;
    while(n<0)
    {
        cout << "input false n!"<<endl;
        cin>>n;
    }
    cout << "please input all coefs and exps of the terms:" << endl;
    for(int j=0;j<n;++j)
    {
        cin >> tempcoef >> tempexp;
        blist.create(tempcoef,tempexp);
    }
    SLnode<int>* headcptr(NULL);
    SLnode<int>* prc(NULL);
    headcptr = alist.add(blist);
    cout << "the result is:" <<endl;
    while(headcptr!=NULL)
    {
        prc = headcptr->next;
        cout << headcptr->data <<" "<< headcptr->exp << " ";
        delete headcptr;     //输出结果的同时析构
        headcptr = prc;
    }
    return 0;
}
