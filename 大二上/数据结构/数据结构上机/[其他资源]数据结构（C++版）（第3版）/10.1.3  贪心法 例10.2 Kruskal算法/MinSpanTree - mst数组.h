//10.1.3   贪心法
//【例10.3】使用最小堆和并查集实现Kruskal算法。

#include "MinHeap.h"                                       //最小堆类
#include "ElementComparator.h"                             //Element对象比较器类
#include "UnionFindSet.h"                                  //并查集类

//最小生成树类，存储一个带权无向图最小生成树的边集合，以及最小代价
class MinSpanTree 
{
  private: 
    Element *mst;                                          //存储最小生成树的边集合
    int vertexCount;                                       //顶点数
    int cost;                                              //最小生成树代价

  public:
    MinSpanTree(int vertexCount, Element edges[], int edgeCount);//构造带权图的最小生成树
    ~MinSpanTree()                                        //析构函数
    {   
        delete this->mst;
    }
    friend ostream& operator<<(ostream& out, MinSpanTree &mstree); //输出最小生成树的边集合和代价
};

    //以Kruskal算法构造带权无向图的最小生成树并求代价，使用最小堆和并查集
    //参数vertexCount指定顶点数，edges数组指定图的所有边（每边只表示一次），edgeCount指定边数
//MinSpanTree::MinSpanTree(AbstractGraphint<T> &graph)
MinSpanTree::MinSpanTree(int vertexCount, Element edges[], int edgeCount)
{
    this->vertexCount = vertexCount;
    this->cost=0;
    Comparator<Element> *comp = new ElementComparator();   //创建比较器对象指针，调用默认构造函数
    MinHeap<Element> minheap(edges, edgeCount, comp);      //使用最小堆存储一个图的所有边，，由*comp比较器对象提供按权值比较边大小的函数

    mst = new Element[vertexCount-1];                      //mst存储最小生成树的边集合，边数为顶点数-1
    UnionFindSet ufset(vertexCount);                       //并查集对象
    cout<<"并查集："<<ufset<<"最小堆："<<minheap;
    int i=0;                                               //最小生成树中当前边的序号
    for (int j=0; j<vertexCount; j++)                      //共选出“顶点数-1”条边
    {
        Element minedge = minheap.removeMin();             //删除最小堆的根，返回权值最小的边
        cout<<"最小边"<<minedge<<"，";
        if (ufset.combine(minedge.row, minedge.column))    //若最小权值边的起点和终点所在的两个集合合并
        {
            this->mst[i++]=minedge;                        //该边加入最小生成树
            this->cost+=minedge.value;                     //计算最小生成树的代价
            cout<<"插入边"<<minedge<<"，并查集："<<ufset;
        }
    }
}

ostream& operator<<(ostream& out, MinSpanTree &mstree)     //输出最小生成树的边集合和代价
{
    out<<"最小生成树的边集合：";
    for (int i=0; i<mstree.vertexCount-1; i++)
        out<<mstree.mst[i]<<" ";
    out<<"，最小代价为"<<mstree.cost<<endl;
    return out;
}

