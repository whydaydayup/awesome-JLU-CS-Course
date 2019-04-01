//《数据结构（C++版）（第3版）》 作者：叶核亚
//7.3   图的遍历
//非连通图的深度优先搜索遍历和广度优先搜索遍历
//7.4   最小生成树
//7.5   最短路径

//#include "SeqList.h"                                       //顺序表类（见2.2.2节）
#include "SeqQueue.h"                                      //顺序循环队列类
#include "Matrix.h"                                        //矩阵类（见例5.1）

template <class T>
class AbstractGraph                                        //抽象图类 
{
  protected:
    const static int MAX_WEIGHT = 9999;//0x7fffffff;              //最大权值（表示无穷大∞）
    virtual int vertexCount()=0;                           //返回顶点数，纯虚函数，由子类实现
    virtual T& getVertex(int i)=0;                         //返回顶点vi元素引用
    virtual int weight(int i, int j)=0;                    //返回<vi,vj>边的权值
    virtual int next(int i, int j=-1)=0;                   //返回顶点v在w后的下一个邻接顶点序号，j=-1，返回第0个邻接顶点序号

  public:
    void DFSTraverse(int i);                               //非连通图的深度优先搜索遍历，从顶点vi出发
    void BFSTraverse(int i);                               //非连通图的广度优先搜索遍历，从顶点vi出发

    void minSpanTree();                                    //Prim算法，构造带权无向图的最小生成树 
    void shortestPath(int i);                              //Dijkstra算法，求带权图顶点vi的单源最短路径
    void shortestPath();                                   //Floyd算法，求带权图每对顶点之间的最短路径

  private:
    void depthfs(int i, SeqList<bool> &visited);           //从顶点vi出发深度优先搜索遍历一个连通分量
    void breadthfs(int i, SeqList<bool> &visited);         //从顶点vi出发广度优先搜索遍历一个连通分量

    //实验7
  public:
    int pathLength(int i, int j);                          //返回从顶点vi到vj的路径长度；当vi=vj时，返回0；当vi与vj不连通时，返回-1
    void printPathAll(int i, int j);                       //输出顶点之间的所有路径及其路径长度
    void printPathAll(int i);                              //输出从顶点vi出发的所有遍历路径，采用回溯法
    bool stronglyConnected();                              //判断一个无（有）向图是否为（强）连通图
    bool isTree();                                         //判断一个无向图是否为一棵树
    bool isCyclePath(int vertexs[]);                       //判断由顶点序列表示的一条路径是否为回路
};
//其中，参数i、j指定图的顶点序号，0≤i、j<顶点数，i≠j；若i、j指定顶点序号超出范围，则抛出序号越界异常。


template <class T>
void AbstractGraph<T>::DFSTraverse(int i)                  //非连通图的深度优先搜索遍历，从顶点vi出发
{
    int n=this->vertexCount();                             //顶点数    
    if (i>=0 && i<n)
    {    
/*        bool *visited = new bool[n];                       //访问标记数组
        for (int j=0; j<n; j++)                            //设置标记
            visited[j]=false;*/
        SeqList<bool> visited(n,false);                     //访问标记顺序表，n个元素，初值为false（未访问）
        int j=i;
        do
        {   if (!visited[j])                               //若顶点vj未被访问
            {   cout<<"{ ";
                depthfs(j, visited);                       //从vj出发深度优先搜索遍历一个连通分量
                cout<<"} ";
            }
            j = (j+1) % n;                                 //在其他连通分量中寻找未被访问顶点
        } while (j!=i);
        cout<<endl;
//        delete[] visited;
    }
    else  throw out_of_range("顶点序号错误，不能遍历图。");
}

//从顶点vi出发深度优先搜索遍历一个连通分量，递归算法
template <class T>
void AbstractGraph<T>::depthfs(int i, SeqList<bool> &visited)
{ 
    cout<<this->getVertex(i)<<" ";                         //访问顶点vi
    visited[i] = true;                                     //置已访问标记
    for (int j=next(i); j!=-1;  j=next(i,j))               //j依次获得vi的所有邻接顶点
        if (!visited[j])                                   //若邻接顶点vj未被访问
            depthfs(j, visited);                           //从vj出发的深度优先搜索遍历，递归调用
}

template <class T>
void AbstractGraph<T>::BFSTraverse(int i)                  //非连通图的广度优先搜索遍历，从顶点vi出发
{
    int n=this->vertexCount();                             //顶点数
    if (i>=0 && i<n)
    {    
        SeqList<bool> visited(n,false);                    //访问标记顺序表，n个元素值为false（未访问）
        int j=i;
        do
        {   if (!visited[j])                               //若顶点vj未被访问
            {   cout<<"{ ";
                breadthfs(j, visited);                     //从顶点vj出发广度优先搜索遍历一个连通分量
                cout<<"} ";
            }
            j = (j+1) % n;                                 //在其他连通分量中寻找未被访问顶点
        } while (j!=i);
        cout<<endl;
    }
    else  throw out_of_range("顶点序号错误，不能遍历图。");
}
    
template <class T>
void AbstractGraph<T>::breadthfs(int i, SeqList<bool> &visited)    //从顶点vi出发广度优先搜索遍历一个连通分量
{
    SeqQueue<int> que;                                     //创建空队列
    cout<<this->getVertex(i)<<" ";
    visited[i] = true;
    que.enqueue(i);                                        //访问过的顶点vi序号入队
    while (!que.empty())                                 //当队列不空时循环
    {
        i = que.dequeue();                                 //出队
        for (int j=next(i,-1); j!=-1;  j=next(i,j))        //j依次获得vi的所有邻接顶点
            if (!visited[j])                               //若顶点vj未访问过
            {
                cout<<this->getVertex(j)<<" ";             //访问顶点
                visited[j] = true;
                que.enqueue(j);                            //访问过的顶点vj序号入队
            }
    }
}

//7.4.2   最小生成树的构造算法Prim 没有用
int indexMinWeight(Triple egdes[], int start, int end)     //求最小权值的边位置
{
    int min=start;                                         //min记住当前最小值位置
    if (start>=0 && end>=0 && start<=end)
    {
        int minweight = egdes[start].value;                //求最小权值
        for (int i=start+1; i<end; i++)                    //寻找当前最小权值的边的顶点
            if (egdes[i].value < minweight)
            {
                minweight = egdes[i].value;                //更新最小权值
                min = i;                                   //保存当前最小权值边的终点序号
            }
    }
    return min;
}
//不能用模板，因为T的重载<运算符定义为比较行列，不比较边的权值，此时需要两种比较规则

//Prim算法，构造带权无向图的最小生成树，输出最小生成树的各边及代价
template <class T>
void AbstractGraph<T>::minSpanTree()
{
    int n=this->vertexCount(), i=0;
    SeqList<Triple> mst(n-1);                              //mst存储MST的边集合，边数为顶点数-1
    for (int j=i; j<n-1; j++)                              //初始化mst，从v0出发构造MST
        mst.insert(Triple(i, j+1, weight(i,j+1)));         //保存顶点v0到其他各顶点的边

    for (i=0; i<n-1; i++)                                  //选出构成MST的n-1条边
    {
//        cout<<"mst数组：";
//        print(mst,n-1);                                    //显示mst数组的变化过程
//       int min = indexMinWeight(mst,i,n-1);                  
        int  minweight=MAX_WEIGHT, min=i;                  //求最小权值的边，记住最小权值及边的下标
        for (int j=i; j<n-1; j++)
            if (mst[j].value < minweight)                  //若存在更小值，则更新最小值变量               
            {
                minweight = mst[j].value;
                min = j; 
            }
        Triple temp = mst[i];                             //交换最小权值的边，表示该边加入TE集合
        mst[i] = mst[min];
        mst[min] = temp;

        int tv = mst[i].column;                            //刚并入TV的顶点
        for (int j=i+1; j<n-1; j++)                        //调整mst[i+1]及其后元素为权值更小的边
        {
            int v = mst[j].column;                         //原边在V-TV中的终点
            if (weight(tv,v)<mst[j].value)                 //若有权值更小的边(tv,v)，则用(tv,v)边替换原边
            {
                mst[j].value = weight(tv,v);
                mst[j].row = tv;
            }
        }
    }
    cout<<"最小生成树的边集合：";
    int mincost=0;
    for (i=0; i<n-1; i++)                                  //输出最小生成树的边集合和代价 
    {
        cout<<mst[i]<<" ";
        mincost += mst[i].value;
    }
    cout<<"，最小代价为"<<mincost<<endl;
}

template <class T>
void print(T table[], int n)                               //输出数组的n个元素
{
    for (int i=0; i<n; i++)
        cout<<table[i]<<" ";
    cout<<endl;
}

template <class T>
void AbstractGraph<T>::shortestPath(int i)                 //Dijkstra算法，求带权图中顶点vi的单源最短路径
{
    int n=this->vertexCount();                             //顶点数
    if (i<0 || i>=n)
        return;

    SeqList<int> dist(n);                                  //最短路径长度
    SeqList<int> path(n);                                  //最短路径的终点的前一个顶点
    for (int j=0; j<n; j++)                                //初始化dist和path顺序表
    {
        dist.insert(weight(i,j));
        path.insert((j!=i && dist[j]<MAX_WEIGHT) ? i : -1);
    }
    SeqList<bool> s(n,false);                              //已求出最短路径的顶点集合，n个元素值为false
    s[i] = true;                                           //源点vi在集合S中的标记
    
    for (int j=(i+1)% n; j!=i; j=(j+1)% n)                 //寻找从vi到顶点vj的最短路径，vj在V-S集合中
    {
//        cout<<"\ns数组";   print(s, n);
//        cout<<"path数组";  print(path, n);
//        cout<<"dist数组";  print(dist, n);
        int mindist=MAX_WEIGHT, min=0;
        for (int k=0; k<n; k++)                            //求路径长度最小值及其下标
            if (!s[k] && dist[k]<mindist)
            {
                mindist = dist[k];                         //当前路径长度最小值
                min = k;                                   //当前路径长度最小值下标
            }
        if (mindist==MAX_WEIGHT)                           //若没有其他最短路径则结束；此语句对非连通图是必须的
            break; 

        s[min] = true;                                     //确定一条最短路径(vi,min)，终点min并入集合S
        for (int k=0; k<n; k++)                            //调整从vi到V-S中其他顶点的最短路径及长度
            if(!s[k] && weight(min,k)<MAX_WEIGHT && dist[min]+weight(min,k)<dist[k])
            {
                dist[k] = dist[min] + weight(min,k);       //用更短路径替换
                path[k] = min;                             //最短路径经过min顶点
            }    
    }

//        cout<<"path数组";  print(path, n);
//        cout<<"dist数组";  print(dist, n);
    SeqList<T> pathlist(n-1);                              //顺序表，记录最短路径经过的各顶点
    for (int j=0; j<n; j++)                                //输出从顶点vi到其他顶点的最短路径
        if (j!=i)    
        {
            pathlist.removeAll();
            pathlist.insert(this->getVertex(j));           //顺序表插入最短路径终点vj
            for (int k=path[j]; k!=-1 && k!=i; k=path[k])  //寻找从vi到vj的最短路径
                pathlist.insert(this->getVertex(k));       //顺序表尾插入经过的顶点
            pathlist.insert(this->getVertex(i));           //最短路径起点vi
            pathlist.printPrevious();                      //顺序表反序输出
 
            if (dist[j]<MAX_WEIGHT)                        //路径长度
                cout<<" "<<dist[j]<<"\t";
            else cout<<" ∞\t";
        }
    cout<<endl;
}

template <class T>
void AbstractGraph<T>::shortestPath()                      //Floyd算法，求带权图每对顶点间的最短路径及长度
{
    int n=this->vertexCount();                             //顶点数
    Matrix path(n),dist(n);                                //最短路径及长度矩阵
    for (int i=0; i<n; i++)                                //初始化dist、path矩阵
        for (int j=0; j<n; j++)
        {
            int w=this->weight(i,j);
            dist.set(i,j,w);                               //dist初值是图的邻接矩阵
            path.set(i,j, (i!=j && w<MAX_WEIGHT ? i : -1));
        }
    cout<<"dist"<<dist<<"path"<<path<<endl;

    for (int k=0; k<n; k++)                                //以vk作为其他路径的中间顶点，测试路径长度是否更短
    {
        for (int i=0; i<n; i++)
            if (k!=i)
                for (int j=0; j<n; j++)
                    if (k!=j && i!=j && dist.get(i,j) > dist.get(i,k)+dist.get(k,j))
                    {
                        dist.set(i, j, dist.get(i,k)+dist.get(k,j));
                        path.set(i, j, path.get(k,j));
                    }
        cout<<"用顶点"<<this->getVertex(k)<<"作为其他路径的经过顶点，"<<"dist"<<dist<<"path"<<path<<endl;
    }

    SeqList<T> pathlist(n-1);                              //顺序表，记录最短路径经过的各顶点
    for (int i=0; i<n; i++)                                //输出每对顶点间的最短路径
    {
        for (int j=0; j<n; j++)                            //寻找从vi到vj最短路径经过的顶点
            if (i!=j)
            {
                 pathlist.removeAll();
                 pathlist.insert(this->getVertex(j));      //顺序表插入最短路径终点vj
                 for (int k=path.get(i,j); k!=-1 && k!=i && k!=j; k=path.get(i,k))  
                      pathlist.insert(this->getVertex(k)); //顺序表尾插入经过的顶点
                 pathlist.insert(this->getVertex(i));      //最短路径起点vi
                 pathlist.printPrevious();                 //顺序表反序输出

                 if (dist.get(i,j)<MAX_WEIGHT)             //路径长度
                    cout<<dist.get(i,j)<<"\t";
                 else
                    cout<<"∞\t";
            }
        cout<<endl;
    }
}

