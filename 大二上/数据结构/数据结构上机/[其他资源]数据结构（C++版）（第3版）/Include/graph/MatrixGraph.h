//《数据结构（C++版）（第3版）》 作者：叶核亚
//7.2.1   图的邻接矩阵表示和实现
//使用矩阵类Matrix对象作为成员变量

#include "SeqList.h"                                       //顺序表类（2.2.2节）
//#include "Matrix.h"                                      //矩阵类（例5.1）
#include "Triple.h"                                        //矩阵的三元组类，表示边（5.2.2节）
#include "AbstractGraph.h"                                 //抽象图类（7.3节）

template <class T>
class MatrixGraph : public AbstractGraph<T>                //邻接矩阵表示的带权图类，继承抽象图类 
{
  private:
    int n;                                                 //顶点数
    SeqList<T> verlist;                                    //顺序表对象，存储图的顶点集合，长度为n
    Matrix mat;                                            //矩阵对象，存储图的邻接矩阵

  public:
    MatrixGraph();                                         //构造空图，顶点数为0
    MatrixGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount);//以顶点集合和边集合构造图
    ~MatrixGraph(){}                                       //析构函数（默认，可省略），执行~Matrix()、~SeqList<T>()

    int vertexCount();                                     //返回顶点数
    T& getVertex(int i);                                   //返回第i个顶点元素
    void setVertex(int i, T x);                            //设置第i个顶点元素为x
    int weight(int i, int j);                              //返回<vi,vj>边的权值
    int next(int i, int j=-1);                             //返回vi在vj后的下一个邻接顶点序号
    friend ostream& operator<<<>(ostream& out, MatrixGraph<T> &);    //输出图的顶点集合和邻接矩阵
    int insertVertex(T x);                                 //插入元素值为x的顶点，返回顶点序号
    void insertEdge(int i, int j, int weight);             //插入一条权值为weight的边〈vi,vj〉
    void insertEdge(Triple edge);                          //插入一条边
    void removeVertex(int i);                              //删除顶点vi及其关联的边
    void removeEdge(int i, int j);                         //删除边〈vi,vj〉
    void removeEdge(Triple edge);                          //删除一条边

//    void shortestPath();                                   //Floyd算法，求带权图每对顶点之间的最短路径

    //实验7
    bool directed;                                         //成员变量，取值为true表示有向图，false无向图
    int degree(int i);                                     //返回顶点vi的度
    int indegree(int i);                                   //返回顶点vi的入度
    int outdegree(int i);                                  //返回顶点vi的出度
    int edgeCount();                                       //返回图的边数
    int cost();                                            //返回带权图的代价 
    int minWeight();                                       //返回边的最小权值
    Triple minWeightEgde();                                //返回最小权值的边
    bool isComplete();                                     //判断是否完全图
    MatrixGraph createComplete(T vertices[], int vertexCount); //以顶点集合构造一个完全图

    MatrixGraph(MatrixGraph<T> &graph);                    //拷贝构造函数
    MatrixGraph<T>& operator=(MatrixGraph<T> &graph);      //重载=赋值运算符，深拷贝
    bool operator==(MatrixGraph<T> &graph);                //比较相等
    bool isSubgraph(MatrixGraph<T> &graph);                //判断是否子图
    bool isSpanSubgraph(MatrixGraph<T> &graph);            //判断是否生成子图
};
//其中，函数参数i、j指定图的顶点在顶点顺序表中的序号，0≤i、j<顶点数，i≠j；若i、j指定顶点序号超出范围，则抛出序号越界异常。

//（2）构造和析构
template <class T>
MatrixGraph<T>::MatrixGraph()                              //构造空图，顶点数为0
{                                                          //此处执行SeqList<T>()、Matrix()
    this->n = 0;
}

//以顶点集和边集构造一个图，参数分别指定顶点集、顶点数、边集、边数。
//若vertices==NULL或vertexCount≤0，则空图，没有顶点；若edges==NULL或edgeCount≤0，则没有边
template <class T>
MatrixGraph<T>::MatrixGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount)
    : verlist(vertices, vertexCount),              	       //声明执行SeqList<T>(T value[], int n) 
      mat(vertexCount*2)                    	           //声明执行Matrix(int rows)构造函数
{ 
    this->n = vertexCount;                                 //顶点数
    for (int i=0; i<n; i++)                                //初始化邻接矩阵，主对角线元素为0，其他为最大权值
        for (int j=0; j<n; j++)
            this->mat.set(i, j, (i==j ? 0 : MAX_WEIGHT));

    if (vertices!=NULL && vertexCount>0 && edges!=NULL)
        for (int j=0; j<edgeCount; j++)                    //插入edges边数组中的所有边
            this->insertEdge(edges[j]);
}

//（3） 获得顶点数属性和存取元素
template <class T>
int MatrixGraph<T>::vertexCount()                          //返回图的顶点数，同顺序表长度
{
    return this->n;                                        //同this->verlist.count()
}

template <class T>
T& MatrixGraph<T>::getVertex(int i)                        //返回第i个顶点元素
{
    return this->verlist[i];                               //返回顺序表第i个元素，若i表示序号无效则抛出异常
}

template <class T>
void MatrixGraph<T>::setVertex(int i, T x)                 //设置第i个顶点元素为x
{
    this->verlist[i] = x;                                  //设置顺序表第i个元素为x，若i表示序号无效则抛出异常
}

template <class T>
int MatrixGraph<T>::weight(int i, int j)                   //返回<vi,vj>边的权值，用于图的最小生成树、最短路径等算法
{
    return this->mat.get(i,j);                             //返回矩阵(i,j)元素值，若i、j表示序号无效则抛出异常
}

//（4）输出
template <class T>
ostream& operator<<(ostream& out, MatrixGraph<T> &graph)   //输出图的顶点集合和邻接矩阵
{
    out<<"顶点集合："<<graph.verlist<<"邻接矩阵：\n";
    for (int i=0; i<graph.n; i++)
    {
        int w;
        for(int j=0; j<graph.n; j++)
            if ((w=graph.weight(i,j))==MatrixGraph<T>::MAX_WEIGHT) 
                out<<setw(6)<<"∞";
            else out<<setw(6)<<w;
        out<<"\n";
    }
    return out;
}

//（5）插入、删除边
template <class T>
void MatrixGraph<T>::insertEdge(int i, int j, int weight)  //插入一条权值为weight的边〈vi,vj〉
{
    if (i!=j)
    {
        if (weight<=0 || weight>MAX_WEIGHT)                //边的权值容错
            weight=MAX_WEIGHT;
        this->mat.set(i,j,weight);                         //若i、j指定序号无效则抛出异常
    }
    else  throw invalid_argument("边的起点与终点序号相同，图不能插入自身环。");
}
template <class T>
void MatrixGraph<T>::insertEdge(Triple edge)               //插入一条边
{
    this->insertEdge(edge.row, edge.column, edge.value);
}

template <class T>
void MatrixGraph<T>::removeEdge(int i, int j)              //删除边〈vi,vj〉，若i==j，则不操作
{ 
    if (i!=j)
        this->mat.set(i, j, MAX_WEIGHT);                   //设置该边的权值为∞。若i、j指定序号无效则抛出异常
}
template <class T>
void MatrixGraph<T>::removeEdge(Triple edge)               //删除边
{ 
    this->removeEdge(edge.row, edge.column);
}

//（6）插入顶点
//插入元素值为x的顶点，返回顶点序号。若邻接矩阵容量不足，则扩充容量2倍，复制原矩阵元素；扩充部分初值为最大权值，主对角线值为0
template <class T>
int MatrixGraph<T>::insertVertex(T x)
{
    this->verlist.insert(x);                               //在顶点顺序表最后插入一个元素，顺序表自动扩容
    this->n++;                                             //顶点数加1
    if (n > mat.getRows())                                 //若邻接矩阵容量不够，
        this->mat.setRowsColumns(n*2, n*2);                //则矩阵扩容2倍，复制原矩阵元素
    
    for (int i=0; i<n-1; i++)                              //初始化增加的一行一列值，主对角线值为0，其余为最大权值
        this->mat.set(i, n-1, MAX_WEIGHT);
    for (int j=0; j<n-1; j++) 
        this->mat.set(n-1, j, MAX_WEIGHT);
    this->mat.set(n-1, n-1, 0);
    return n-1;                                            //返回插入顶点序号
}

//（7）删除顶点
template <class T>
void MatrixGraph<T>::removeVertex(int v)                   //删除第v个顶点及其关联的所有边
{
    if (v<0 || v>n)                                        //若v指定顶点序号错误，则不操作
        return;
    this->verlist.remove(v);                               //删除顺序表第v个元素，长度减1
    for (int i=0; i<n; i++)                                //左移一列，this->n为原顶点数
        for (int j=v+1; j<n; j++)
            this->mat.set(i, j-1, mat.get(i,j));
    for (int i=v+1; i<n; i++)                              //上移一行
        for (int j=0; j<n; j++)
            this->mat.set(i-1, j, mat.get(i,j));
    this->n--;                                             //顶点数减1
}    
  
//（8） 获得下一个邻接顶点
//返回vi在vj后的下一个邻接顶点的序号，若j=-1，返回顶点vi的第一个邻接顶点的序号；
//若不存在下一个邻接顶点，则返回-1。用于图的遍历算法
template <class T>
int MatrixGraph<T>::next(int i, int j)
{
    if (i>=0 && i<n && j>=-1 && j<n && i!=j)
        for (int k=j+1; k<n; k++)                    //j=-1时，k从0开始寻找下一个邻接顶点
            if (weight(i,k)>0 && weight(i,k)<MAX_WEIGHT)
                return k;
    return -1;         
}

//7.5   最短路径
//7.5.2   每对顶点间的最短路径
/*正确
template <class T>
void MatrixGraph<T>::shortestPath()                      //Floyd算法，求带权图每对顶点间的最短路径及长度
{
    int n=this->vertexCount();                             //顶点数
    Matrix path(n),dist(this->mat);                        //最短路径及长度矩阵，dist(mat)执行Matrix拷贝构造函数，深拷贝
    for (int i=0; i<n; i++)                                //初始化dist、path矩阵
        for (int j=0; j<n; j++)
        {
//            int w=this->weight(i,j);
//            dist.set(i,j,w);                               //dist初值是图的邻接矩阵
            path.set(i,j, (i!=j && weight(i,j)<MAX_WEIGHT ? i : -1));
        }
//    cout<<"dist"<<dist<<"path"<<path<<endl;

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
//        cout<<"用顶点"<<this->getVertex(k)<<"作为其他路径的经过顶点，"<<"dist"<<dist<<"path"<<path<<endl;
    }

    SeqList<T> pathlist(n-1);                              //顺序表，记录最短路径经过的各顶点
    for (int i=0; i<n; i++)                                //输出每对顶点间的最短路径
    {
        for (int j=0; j<n; j++)
            if (i!=j)
            {
                 pathlist.removeAll();
                 pathlist.insert(this->getVertex(j));      //顺序表插入最短路径终点vj
                 for (int k=path.get(i,j); k!=-1 && k!=i && k!=j; k=path.get(i,k))  //寻找从vi到vj的最短路径经过的顶点
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

/*
未实现
     public boolean removeVertex(E vertex)             //删除顶点vertex及其关联的边
    {
        return this.verlist.remove(vertex);        //删除顺序表中值为vertex的元素
    }
    

？？

//习题7
template <class T>
int AdjMatrixGraph<T>::edgeCount()                         //返回边数
{
    int n=this->vertexlist.length();                       //顶点数
    int count=0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (i!=j && this->adjmatrix[i][j]!=MAX_WEIGHT)
                count++;
    return count;
}

template <class T>
int AdjMatrixGraph<T>::indegree(int i)                     //返回顶点vi的入度
{
    int n=this->vertexlist.length();                       //顶点数
    int degree=0;
    for (int j=0; j<n; j++)                                //第i列上各元素之和是顶点vi的入度
        if (i!=j && this->adjmatrix[j][i]!=MAX_WEIGHT)
            degree++;
    return degree;
}

template <class T>
int AdjMatrixGraph<T>::outdegree(int i)                    //返回顶点vi的出度
{
    int n=this->vertexlist.length();                       //顶点数
    int degree=0;
    for (int j=0; j<n; j++)                                //第i行上各元素之和是顶点vi的出度
        if (i!=j && this->adjmatrix[i][j]!=MAX_WEIGHT)
            degree++;
    return degree;
}

*/