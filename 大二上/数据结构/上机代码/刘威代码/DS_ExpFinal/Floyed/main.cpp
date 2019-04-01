#include <iostream>
#include <FGraph.h>

using namespace std;

int main()
{
    FGraph* f=new FGraph();
    f->Floyed();
    f->ShowPath();
    cout<<endl<<f->MaxMinDis<<endl;
    return 0;
}
