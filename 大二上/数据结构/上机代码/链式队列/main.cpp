#include <iostream>
#include "SLnode.h"
#include "Queue.h"
using namespace std;

int main()
{
    Queue<int> aqueue;
    for(int i=0;i<6;++i)
    {
        aqueue.inserttail(i);
    }
    aqueue.deletefirst();
    int n(0);
    aqueue.peekfirst(n);
    cout << n <<endl;
    return 0;
}
