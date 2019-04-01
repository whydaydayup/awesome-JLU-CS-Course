#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <list>
#include <algorithm>
#include <windows.h>
#include "Graph.h"

#define MAX_COST 50
#define MIN_COST 10

using namespace std;

bool Compare(PowerEdge* x,PowerEdge* y);

Graph::Graph()
{
    VertexNum=0;
    EdgeNum=0;
    Head=NULL;
}

Graph::Graph(int vn,int en)
{
    VertexNum=vn;
    EdgeNum=en;
    Head=new Vertex*[VertexNum];
    for(int i=0;i<VertexNum;i++)
    {
        Head[i]=new Vertex(i);
    }
}

Graph::~Graph()
{
    //dtor
}

void Graph::RandomGenerate()
{
    srand(time(0));
    for(int i=0;i<EdgeNum;i++)
    {
        int from=(rand()%VertexNum);
        int to=(rand()%VertexNum);
        while(from==to||GetEdge(from,to)!=NULL)
        {
            from=(rand()%VertexNum);
            to=(rand()%VertexNum);
        }
        int cost=(rand()%(MAX_COST-MIN_COST+1))+MIN_COST;
        Edge* e=new Edge(to,cost);
        Vertex* v=Head[from];
        Edge* p=v->adjacent;
        if(p==NULL)
        {
            v->adjacent=e;
        }else
        {
            while(p->link!=NULL)
            {
                p=p->link;
            }
            p->link=e;
        }
    }
}

void Graph::ShowGraph()
{
    cout<<endl;
    for(int i=0;i<VertexNum;i++)
    {
        Vertex* v=Head[i];
        cout<<'['<<v->VerName<<']';
        Edge* e=v->adjacent;
        while(e!=NULL)
        {
            cout<<"->"<<e->VerAdj<<'('<<e->cost<<')';
            e=e->link;
        }
        cout<<endl;
    }
}

Edge* Graph::GetEdge(int f,int t)
{
    Vertex* v=Head[f];
    Edge* e=v->adjacent;
    while(e!=NULL)
    {
        if(t==e->VerAdj)
        {
            return e;
        }
        e=e->link;
    }
    return NULL;
}

int Graph::GetCost(int f,int t)
{
    Edge* e=GetEdge(f,t);
    if(e!=NULL)
    {
        return e->cost;
    }else return -1;
}

void Graph::InsertEdge(int f,int t,int c)
{
    if(GetEdge(f,t)!=NULL)
    {
        cout<<endl<<"Edge Exists"<<endl;  //Edge Exists
    }else
    {
        Vertex* v=Head[f];
        Edge* eo=v->adjacent;
        Edge* en=new Edge(t,c);
        v->adjacent=en;
        en->link=eo;
    }
}

void Graph::DelEdge(int f,int t)
{
    Edge* e=GetEdge(f,t);
    if(e==NULL)
    {
        cout<<endl<<"Edge Not Exist"<<endl; //Edge Not Exist
    }else
    {
        Vertex* v=Head[f];
        Edge* p=v->adjacent;
        if(p!=e)
        {
            while(p->link!=e)
            {
                p=p->link;
            }
            p->link=e->link;
        }else
        {
            v->adjacent=e->link;
        }
        delete e;
    }
}

Edge* Graph::GetFirstAdjacent(int f)
{
    return Head[f]->adjacent;
}

void Graph::DFS(int f,int* visited)
{
    cout<<'['<<f<<']'<<' ';
    visited[f]=1;
    Vertex* v=Head[f];
    Edge* e=v->adjacent;
    while(e!=NULL)
    {
        if(visited[e->VerAdj]!=1)
        {
            DFS(e->VerAdj,visited);
        }
        e=e->link;
    }
}

void Graph::BFS(int f,int* visited)
{
    queue<int>* q=new queue<int>();
    cout<<'['<<f<<']'<<' ';
    visited[f]=1;
    //Vertex* v=Head[f];
    //Edge* e=v->adjacent;
    q->push(f);
    while(!q->empty())
    {
        int v=q->front();
        q->pop();
        Edge* p=Head[v]->adjacent;
        while(p!=NULL)
        {
            if(visited[p->VerAdj]!=1)
            {
                cout<<'['<<p->VerAdj<<']'<<' ';
                visited[p->VerAdj]=1;
                q->push(p->VerAdj);
            }
            p=p->link;
        }
    }
}

void Graph::AllComponent()
{
    int Foreground_Color[4]={FOREGROUND_BLUE|FOREGROUND_GREEN,FOREGROUND_GREEN|FOREGROUND_RED,FOREGROUND_RED|FOREGROUND_BLUE,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE};
    int Background_Color[3]={BACKGROUND_BLUE,BACKGROUND_GREEN,BACKGROUND_RED};
    bool WSM[VertexNum][VertexNum];
    bool markedList[VertexNum];
    Edge* e=NULL;
    int num=0;
    for(int i=0;i<VertexNum;i++)
    {
        markedList[i]=0;
        for(int j=0;j<VertexNum;j++)
            WSM[i][j]=0;
    }
    for(int i=0;i<VertexNum;i++)
    {
        WSM[i][i]=1;
        Edge* e=Head[i]->adjacent;
        while(e!=NULL)
        {
            WSM[i][e->VerAdj]=1;
            e=e->link;
        }
    }
    for(int k=0;k<VertexNum;k++)
    {
        for(int i=0;i<VertexNum;i++)
        {
            if(WSM[i][k]==1)
            {
                for(int j=0;j<VertexNum;j++)
                {
                    WSM[i][j]=WSM[i][j]||WSM[k][j];
                }
            }
        }
    }

    /*for(int i=0;i<VertexNum;i++)
    {
        for(int j=0;j<VertexNum;j++)
        {
            cout<<WSM[i][j]<<" ";
        }
        cout<<endl;
    }*/

    /*************************************************************/
    for(int i=0;i<VertexNum;i++)
    {
        if(!markedList[i])
        {
            num++;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | Foreground_Color[num%4] | Background_Color[num%3]);
            markedList[i]=1;
            list<int>* l=new list<int>();
            l->push_back(i);
            for(int j=0;j<VertexNum;j++)
            {
                if(i!=j&&WSM[i][j]&&WSM[j][i])
                {
                    markedList[j]=1;
                    l->push_back(j);
                }
            }
            cout<<endl<<num<<": ";
            list<int>::iterator it;
            for(it=l->begin();it!=l->end();)
            {
                cout<<'['<<*it<<']';
                if(++it!=l->end())
                {
                    cout<<"->";
                }
            }
            cout<<endl;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    /*************************************************************/

    for(int i=0;i<VertexNum;i++)
        cout<<i<<"\t";

    cout<<endl;

    /*char line[20];

    for(int i=0;i<VertexNum;i++)
    {
        Edge* e=Head[i]->adjacent;
        while(e!=NULL)
        {
            if(e->VerAdj>i)
            {
                line[2*e->VerAdj]='>';
                for(int k=0;k<i;k++)
                {
                    cout<<"    ";
                }
                for(int j=i;j<e->VerAdj;j++)
                {
                    cout<<"--------";

                }
                cout<<endl;
            }else
            {

            }
            e=e->link;
        }
    }*/

    num=0;int colorOrder=0;
    for(int i=0;i<VertexNum;i++)
    {
        markedList[i]=0;
    }
    for(int i=0;i<VertexNum;i++)
    {

        if(!markedList[i])
        {
            num++;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | Foreground_Color[num%4] | Background_Color[num%3]);
            markedList[i]=1;
            list<int>* l=new list<int>();
            l->push_back(i);
            for(int j=0;j<VertexNum;j++)
            {
                if(i!=j&&WSM[i][j]&&WSM[j][i])
                {
                    markedList[j]=1;
                    l->push_back(j);
                }
            }
            //cout<<endl<<num<<": ";
            list<int>::iterator it;

            for(it=l->begin();it!=l->end();it++)
            {
                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | Foreground_Color[num%4] | Background_Color[num%3]);
                /*cout<<'['<<*it<<']';
                if(++it!=l->end())
                {
                    cout<<"->";
                }*/
                //int color=Foreground_Color[(num+1)%4];
                Edge* e=Head[*it]->adjacent;
                while(e!=NULL)
                {

                    if(findList(l,e->VerAdj))
                    {
                        if(e->VerAdj>*it)
                        {
                            //cout<<num;
                            for(int k=0;k<*it;k++)
                            {
                                cout<<"        ";
                            }
                            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | 7+num*0x10);
                            setColor(7,num);
                            for(int j=*it;j<e->VerAdj;j++)
                            {
                                cout<<"--------";
                            }
                            cout<<">";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        }else
                        {
                            //cout<<num;
                            for(int k=0;k<e->VerAdj;k++)
                            {
                                cout<<"        ";
                            }
                            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | 7+num*0x10);
                            setColor(7,num);
                            cout<<"<";
                            for(int j=*it;j>e->VerAdj;j--)
                            {
                                cout<<"--------";
                            }
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        }
                    }else
                    {
                        if(e->VerAdj>*it)
                        {
                            //cout<<num;
                            for(int k=0;k<*it;k++)
                            {
                                cout<<"        ";
                            }
                            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | 7+num*0x10);
                            setColor(10+colorOrder,0);
                            colorOrder++;
                            for(int j=*it;j<e->VerAdj;j++)
                            {
                                cout<<"--------";
                            }
                            cout<<">";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        }else
                        {
                            //cout<<num;
                            for(int k=0;k<e->VerAdj;k++)
                            {
                                cout<<"        ";
                            }
                            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | 7+num*0x10);
                            setColor(10+colorOrder,0);
                            colorOrder++;
                            cout<<"<";
                            for(int j=*it;j>e->VerAdj;j--)
                            {
                                cout<<"--------";
                            }
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        }
                    }
                    cout<<endl;
                    e=e->link;

                }
/*cout<<'['<<*it<<']';
                if(++it!=l->end())
                {
                    cout<<"->";
                }*/
            }
            cout<<endl;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Graph::setColor(unsigned short ForeColor=7, unsigned short BackColor=0)
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE); //获取当前窗口句柄
	SetConsoleTextAttribute(handle, ForeColor+BackColor*0x10); //设置颜色
}

bool Graph::findList(list<int>* l,int f)
{
    list<int>::iterator it;
    for(it=l->begin();it!=l->end();it++)
    {
        if(f==*it)
        {
            return true;
        }
    }
    return false;
}

void Graph::GeneratePEdgeVec()
{
    PEdgeVector=new vector<PowerEdge*>();
    for(int i=0;i<VertexNum;i++)
    {
        Edge* e=Head[i]->adjacent;
        while(e!=NULL)
        {
            PowerEdge* p=new PowerEdge(i,e->VerAdj,e->cost);
            PEdgeVector->push_back(p);
            e=e->link;
        }
    }
    sort(PEdgeVector->begin(),PEdgeVector->end(),Compare);
    vector<PowerEdge*>::iterator it;
    for(it=PEdgeVector->begin();it!=PEdgeVector->end();it++)
    {
        cout<<(*it)->From<<"\t"<<(*it)->VerAdj<<"\t"<<(*it)->cost<<endl;
    }
}

bool Compare(PowerEdge* x,PowerEdge* y)
{
    return x->cost<y->cost;
}
