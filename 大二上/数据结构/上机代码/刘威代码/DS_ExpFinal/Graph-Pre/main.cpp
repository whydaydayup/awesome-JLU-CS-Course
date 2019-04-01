#include <iostream>
#include <Graph.h>

using namespace std;

int main()
{
    Graph* G=new Graph(10,20);
    G->RandomGenerate();
    G->GeneratePEdgeVec();

    return 0;
}
