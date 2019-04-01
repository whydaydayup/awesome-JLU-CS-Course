#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
using namespace std;

class PowerEdge
{
    public:
    PowerEdge(){From=-1;VerAdj=-1;cost=-1;}
    PowerEdge(int f,int v,int c){From=f;VerAdj=v;cost=c;}
    int From;
    int VerAdj;
    int cost;
};

class Edge
{
public:
    Edge(){VerAdj=-1;cost=-1;link=NULL;}
    Edge(int v,int c){VerAdj=v;cost=c;link=NULL;}
    Edge(int v,int c,Edge* e){VerAdj=v;cost=c;link=e;}
    int VerAdj;
    int cost;
    Edge* link;
};

class Vertex
{
public:
    Vertex(int vn){VerName=vn;adjacent=NULL;}
    Vertex(int vn,Edge* e){VerName=vn;adjacent=e;}
    int VerName;
    Edge* adjacent;
};

class Graph
{
    public:
        Graph();
        Graph(int vn,int en);
        virtual ~Graph();
        int VertexNum;
        int EdgeNum;
        Vertex** Head;
        void RandomGenerate();
        void ShowGraph();
        Edge* GetEdge(int f,int t);
        int GetCost(int f,int t);
        void InsertEdge(int f,int t,int c);
        void DelEdge(int f,int t);
        Edge* GetFirstAdjacent(int f);
        void DFS(int f,int* visited);
        void BFS(int f,int* visited);
        void AllComponent();
        vector<PowerEdge*>* PEdgeVector;
        void GeneratePEdgeVec();
    protected:

    private:
        void setColor(unsigned short ForeColor, unsigned short BackColor);
        bool findList(list<int>* l,int f);
};

#endif // GRAPH_H
