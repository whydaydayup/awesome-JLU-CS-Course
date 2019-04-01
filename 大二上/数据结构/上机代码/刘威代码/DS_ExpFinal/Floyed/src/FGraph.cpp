#include "FGraph.h"
#include <iostream>
#include <limits>
#include <queue>

using namespace std;

FGraph::FGraph()
{
    cout<<"VertexNum:"<<endl;
    cin>>VertexNum;
    cout<<"Pairs:"<<endl;
    int p;
    cin>>p;
    for(int i=0;i<VertexNum;i++)
    {
        for(int j=0;j<VertexNum;j++)
        {
            if(i==j)
            {
                Array[i][j]=0;
            }else
            {
                Array[i][j]=INT_MAX;
            }
        }
    }
    for(int i=0;i<p;i++)
    {
        char m,n;
        cin>>m>>n;
        Array[CharToNum(m)][CharToNum(n)]=1;
        Array[CharToNum(n)][CharToNum(m)]=1;
    }
    ShowArray();
    if(p>VertexNum-1)
    {
        cout<<"不是自由树";
    }
}

FGraph::~FGraph()
{
    //dtor
}

void FGraph::ShowArray()
{
    cout<<endl<<"  ";
    for(char c='A';c<'A'+VertexNum;c++)
        cout<<c<<"\t";
    cout<<endl;
    for(int i=0;i<VertexNum;i++)
    {
        cout<<char('A'+i)<<" ";
        for(int j=0;j<VertexNum;j++)
        {
            if(Array[i][j]==INT_MAX)
            {
                cout<<"/"<<"\t";
            }else
            {
                cout<<Array[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}

void FGraph::ShowPath()
{
    cout<<endl<<"  ";
    for(char c='A';c<'A'+VertexNum;c++)
        cout<<c<<"\t";
    cout<<endl;
    for(int i=0;i<VertexNum;i++)
    {
        cout<<char('A'+i)<<" ";
        for(int j=0;j<VertexNum;j++)
        {
            if(Path[i][j]!=-1)
            {
                cout<<char('A'+Path[i][j])<<"\t";
            }else
            {
                cout<<Path[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}

void FGraph::Floyed()
{
    /**Init Matrix*/
    for(int i=0;i<VertexNum;i++)
    {
        for(int j=0;j<VertexNum;j++)
        {
            if(i!=j&&Array[i][j]!=INT_MAX)
            {
                Path[i][j]=i;
            }else
            {
                Path[i][j]=-1;
            }
        }
    }

    /**Floyed*/
    for(int k=0;k<VertexNum;k++)
    {
        for(int i=0;i<VertexNum;i++)
        {
            if(i!=k)
            {
                for(int j=0;j<VertexNum;j++)
                {
                    if(j!=k&&j!=i&&Array[i][k]<INT_MAX&&Array[k][j]<INT_MAX&&Array[i][k]+Array[k][j]<Array[i][j])
                    {
                        Array[i][j]=Array[i][k]+Array[k][j];
                        Path[i][j]=Path[k][j];
                    }
                }
            }
        }
    }

    /**Get MaxMinDis*/
    MaxMinDis=0;
    for(int i=0;i<VertexNum;i++)
    {
        for(int j=0;j<VertexNum;j++)
        {
            if(Array[i][j]!=INT_MAX&&Array[i][j]>MaxMinDis)
            {
                MaxMinDis=Array[i][j];
            }
        }
    }
}

int FGraph::CharToNum(char c)
{
    return c-'A';
}
