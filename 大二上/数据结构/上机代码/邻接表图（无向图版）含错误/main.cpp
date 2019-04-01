#include <iostream>
#include <windows.h>
#include "Graph.h"
#include "Edgenode.h"
#include "Vertex.h"
using namespace std;

void ShowMenu(int i)
{
    switch(i)
    {
    case 0:
        cout<<endl
        <<"1) 创建无向图（顶点数_边数）"<<endl
        <<"2) 打印图"<<endl
        <<"3）查询权值（从_到_）"<<endl
        <<"4）插入边（从_到_权值）"<<endl
        <<"5）删除边（从_到_）"<<endl
        <<"6）输出第一个邻接顶点（目标顶点）"<<endl
        <<"7）深度优先遍历（起始顶点）"<<endl
        <<"8）广度优先遍历（起始顶点）"<<endl
        <<"9）显示全部连通分量"<<endl
        <<"10）显示连通分量个数"<<endl
        <<"0）退出"<<endl;
        break;
    }
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Graph* G;

    ShowMenu(0);

    int operation=0;
    cin>>operation;

    while(operation)
    {
        int x,y,z;
        switch(operation)
        {
        case 1:
            cin>>x>>y;
            G=new Graph;
            G->create(x,y);
            G->ShowGraph();
            break;
        case 2:
            G->ShowGraph();
            break;
        case 3:
            cin>>x>>y;
            cout << G->getweight(x,y);
            break;
        case 4:
            cin>>x>>y>>z;
            G->insertEdge(x,y,z);
            G->ShowGraph();
            break;
        case 5:
            cin>>x>>y;
            G->deleteEdge(x,y);
            G->ShowGraph();
            break;
        case 6:
            cin>>x;
            cout << G->findFirstadj(x);
            break;
        case 7:
            cin>>x;
            G->depthFirstTraverse(x);
            break;
        case 8:
            cin>>x;
            G->broadFirstTraverse(x);
            break;
        case 9:
            G->findcomponent();
            break;
        case 10:
            cout << G->countcomponent();
            break;
        }

        ShowMenu(0);
        cin>>operation;
    }

    return 0;
}
