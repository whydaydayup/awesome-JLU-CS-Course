//《数据结构（C++版）（第3版）》 作者：叶核亚
//7.2.2   图的邻接表表示和实现
//使用矩阵行的单链表对象作为成员变量

#include "LinkedMatrix.h"                                  //行的单链表存储的矩阵类（见5.2.2节），包含SeqList.h、Triple.h
#include "AbstractGraph.h"                                 //抽象图类（见7.3节）

template <class T>
class AdjListGraph : public AbstractGraph<T>               //邻接表表示的带权图类，继承抽象图类 
{
  private:
    int n;                                                 //顶点数
    SeqList<T> verlist;                                    //顺序表对象，存储图的顶点集合，长度为n
    LinkedMatrix adjlist;                                  //行的单链表存储的矩阵对象，图的邻接表

  public:
    AdjListGraph();                                        //构造空图，顶点数为0
    AdjListGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount);//以顶点集和边集构造一个图
    ~AdjListGraph(){}                                      //析构函数（默认，可省略），执行~LinkedMatrix()、~SeqList<T>()

    int vertexCount();                                     //返回顶点数
    T& getVertex(int i);                                   //返回第i个顶点元素
    void setVertex(int i, T x);                            //设置第i个顶点元素为x
    int weight(int i, int j);                              //返回<vi,vj>边的权值
    int next(int i, int j=-1);                             //返回vi在vj后的下一个邻接顶点序号
    friend ostream& operator<<<>(ostream& out, AdjListGraph<T>&);    //输出图的顶点集合和邻接表
    int insertVertex(T x);                                 //插入元素值为x的顶点，返回顶点序号
    void insertEdge(int i, int j, int weight);        	   //插入一条权值为weight的边〈vi,vj〉
    void insertEdge(Triple edge);                          //插入一条边
    void removeVertex(int i);                   	       //删除顶点vi及其关联的边
    void removeEdge(int i, int j);               	       //删除边〈vi,vj〉
    void removeEdge(Triple edge);                          //删除边
}; 

//（1） 图的构造函数
template <class T>
AdjListGraph<T>::AdjListGraph()                            //构造空图，顶点数为0
{                                                          //此处执行SeqList<T>()、LinkedMatrix()
    this->n = 0;
}

//以顶点集和边集构造一个图，参数分别指定顶点集、顶点数、边集、边数
template <class T>
AdjListGraph<T>::AdjListGraph(T vertices[], int vertexCount, Triple edges[], int edgeCount)
    : verlist(vertices, vertexCount),                      //声明执行SeqList<T>(T value[], int n)
      adjlist(vertexCount,vertexCount,edges,edgeCount)     //声明执行LinkedMatrix(int rows, int columns, Triple elem[], int n)
{
    this->n = vertexCount;
}

//存取元素和属性，以下3个函数声明同图的邻接矩阵
template <class T>
int AdjListGraph<T>::vertexCount()                         //返回图的顶点数，同顺序表长度
{
    return this->n;                                        //同this->verlist.count()
}

template <class T>
T& AdjListGraph<T>::getVertex(int i)                       //返回第i个顶点元素
{
    return this->verlist[i];                               //返回顺序表第i个元素，若i指定序号无效则抛出异常
}

template <class T>
void AdjListGraph<T>::setVertex(int i, T x)                //设置第i个顶点元素为x
{
    this->verlist[i] = x;                                  //设置顺序表第i个元素为x，若i指定序号无效则抛出异常
}

//（2）输出
template <class T>
ostream& operator<<(ostream& out, AdjListGraph<T> &graph)   //输出图的顶点集合和邻接表
{
    out<<"顶点集合："<<graph.verlist<<"邻接表：\n"<<graph.adjlist;
    return out;
}

//（2）插入、删除边
template <class T>
void AdjListGraph<T>::insertEdge(int i, int j, int weight) //插入一条权值为weight的边〈vi,vj〉
{
    if (i!=j)
    {
        if (weight<=0 || weight>=MAX_WEIGHT)      	       //边的权值容错
            weight=0;
        this->adjlist.set(i,j,weight);                     //设置第i条边单链表中<vi,vj>边的权值
                      //当i、j有效时，若0<weight<∞，插入边或替换边的权值；若weight==0，删除该边
    }
    else  throw invalid_argument("边的起点与终点序号相同，图不能插入自身环。");   //抛出无效参数异常
}
template <class T>
void AdjListGraph<T>::insertEdge(Triple edge)              //插入一条边。同图的邻接矩阵
{
    this->insertEdge(edge.row, edge.column, edge.value);
}

template <class T>
void AdjListGraph<T>::removeEdge(int i, int j)             //删除边〈vi,vj〉，若i==j，则不操作
{ 
    if (i!=j)
        this->adjlist.set(i,j,0);                          //设置矩阵元素为0，即在排序单链表中删除〈vi,vj〉结点。若i、j指定顶点序号错误，则抛出异常。
}
template <class T>
void AdjListGraph<T>::removeEdge(Triple edge)              //删除边。同图的邻接矩阵
{ 
    this->removeEdge(edge.row, edge.column);
}

//（4）插入顶点
template <class T>
int AdjListGraph<T>::insertVertex(T x)                     //插入元素值为x的顶点，返回顶点序号
{
    this->verlist.insert(x);                               //顶点顺序表尾插入x，长度加1，自动扩容
    this->n++;                                             //顶点数加1
    this->adjlist.setRowsColumns(n, n);                    //设置邻接表加一行，其中行指针顺序表自动扩容
    return this->n-1;                                      //返回插入顶点序号
}

//（5）删除顶点
template <class T>
void AdjListGraph<T>::removeVertex(int v)                  //删除第v个顶点及其关联的边
{
    if (v>=0 && v<this->n)
    {
        this->verlist.remove(v);                           //删除顶点顺序表第v个元素，长度减1
        //以下在第v条以外的单链表中删除以v为终点的所有边
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[v];  //获得第v条排序单链表
        for (Node<Triple>* p=list->head->next;  p!=NULL; p=p->next) //遍历第v条边单链表
            this->removeEdge(p->data.symmetry());          //删除与p结点对称的边，即删除以v为终点的边

        this->n--;                                         //顶点数减1
        this->adjlist.rowlist.remove(v);                   //删除行指针数组的第v条单链表
        list->~SortedSinglyList<Triple>();                 //析构第v条排序单链表
        this->adjlist.setRowsColumns(n, n);                //设置矩阵行列数，少一行

        for (int i=0; i<n; i++)                            //遍历每条边单链表，将>v的顶点序号减1
        {
            list = this->adjlist.rowlist[i]; 
            for (Node<Triple>* p=list->head->next; p!=NULL; p=p->next)
            {
                if (p->data.row > v)
                    p->data.row--; 
                if (p->data.column > v)
                    p->data.column--;
            }
        }
    }
    else  throw out_of_range("顶点序号错误，不能删除顶点。");
}
 
//（5） 获得下一个邻接顶点和边的权值属性
//返回vi在vj后的下一个邻接顶点序号，若j=-1，返回顶点vi的第一个邻接顶点的序号；
//若不存在下一个邻接顶点，则返回-1。用于图的遍历算法
template <class T>
int AdjListGraph<T>::next(int i, int j)
{
    if (i>=0 && i<n && j>=-1 && j<n && i!=j)
    {                                                      //以下在第i条边排序单链表中查找终点序号>j的边
        SortedSinglyList<Triple> *list = this->adjlist.rowlist[i];
        for (Node<Triple> *p = list->head->next;  p!=NULL;  p = p->next)
            if (p->data.column > j)
                return p->data.column;                     //返回下一个邻接顶点的序号
    }
    return -1;                                             //没有下一个邻接顶点
}

template <class T>
int AdjListGraph<T>::weight(int i, int j)                  //返回<vi,vj>边的权值，用于图的最小生成树、最短路径等算法
{
    if (i==j)
        return 0;
    int w = this->adjlist.get(i,j);                        //返回矩阵(i,j)元素值，若i、j指定序号无效则抛出异常
    return w!=0 ? w : MAX_WEIGHT;                          //若返回0表示没有边，则边的权值返回∞
}
/*
未实现
     public boolean removeVertex(E vertex)             //删除顶点vertex及其关联的边
    {
        return this.verlist.remove(vertex);        //删除顺序表中值为vertex的元素
    }
    
*/

