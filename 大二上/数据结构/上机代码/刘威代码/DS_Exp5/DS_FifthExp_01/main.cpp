#include <iostream>
#include <windows.h>
#include <Graph.h>

using namespace std;

void ShowMenu(int i);

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Graph* G;
    //G->RandomGenerate();
    //G->ShowGraph();

    ShowMenu(0);

    int operation=0;
    cin>>operation;

    while(operation)
    {
        int x,y,z;
        int* visited=new int[G->VertexNum];
        switch(operation)
        {
        case 1:
            cin>>x>>y;
            G=new Graph(x,y);
            G->RandomGenerate();
            G->ShowGraph();
            break;
        case 2:
            G->ShowGraph();
            break;
        case 3:
            cin>>x>>y;
            if(G->GetCost(x,y)==-1)
            {
                cout<<endl<<"不存在边！"<<endl;  //Edge Not Exist
            }else
            {
                cout<<endl<<G->GetCost(x,y)<<endl;
            }
            break;
        case 4:
            cin>>x>>y>>z;
            G->InsertEdge(x,y,z);
            G->ShowGraph();
            break;
        case 5:
            cin>>x>>y;
            G->DelEdge(x,y);
            G->ShowGraph();
            break;
        case 6:
            cin>>x;
            if(G->GetFirstAdjacent(x)!=NULL)
            {
                cout<<endl<<G->GetFirstAdjacent(x)->VerAdj<<endl;
            }else
            {
                cout<<endl<<"不存在！"<<endl;   //Not Exist
            }
            break;
        case 7:
            cin>>x;
            for(int i=0;i<G->VertexNum;i++)
            {
                visited[i]=0;
            }
            G->DFS(x,visited);
            x=1;
            for(int i=0;i<G->VertexNum;i++)
            {
                if(visited[i]==0)
                {
                    x=0;

                    break;
                }
            }
            if(x)
            {
                cout<<endl<<"已遍历所有点"<<endl; //All Visited
            }else
            {
                cout<<endl<<"未遍历所有点"<<endl; //Not All Visited
            }
            break;
        case 8:
            cin>>x;
            for(int i=0;i<G->VertexNum;i++)
            {
                visited[i]=0;
            }
            G->BFS(x,visited);
            x=1;
            for(int i=0;i<G->VertexNum;i++)
            {
                if(visited[i]==0)
                {
                    x=0;

                    break;
                }
            }
            if(x)
            {
                cout<<endl<<"已遍历所有点"<<endl; //All Visited
            }else
            {
                cout<<endl<<"未遍历所有点"<<endl; //Not All Visited
            }
            break;
        case 9:
            G->AllComponent();
            break;
        }

        ShowMenu(0);
        cin>>operation;
    }

    return 0;
}

void ShowMenu(int i)
{
    switch(i)
    {
    case 0:
        cout<<endl
        <<"1) 创建图（顶点数_边数）"<<endl
        <<"2) 打印"<<endl
        <<"3）查询权值（从_到）"<<endl
        <<"4）插入边（从_到_权值）"<<endl
        <<"5）删除边"<<endl
        <<"6）输出第一个邻接顶点"<<endl
        <<"7）深度优先遍历"<<endl
        <<"8）广度优先遍历"<<endl
        <<"9）显示连通分量"<<endl
        <<"0）退出"<<endl;
        break;
    }
}
