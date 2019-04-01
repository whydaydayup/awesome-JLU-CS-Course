//10.1.3   贪心法
//【例10.3】使用最小堆和并查集实现Kruskal算法。
//并查集

class UnionFindSet                                         //并查集类
{
  private:
    SeqList<int> parent;                                   //使用顺序表表示父指针数组

  public:
    //构造有n个元素的并查集对象，集合初始状态是包含n棵树的森林，其父指针数组元素值为-1，
    //表示每棵树只有一个结点。声明调用SeqList<int>(int length, T x)构造函数
    UnionFindSet(int n) : parent(n,-1){} 
    friend ostream& operator<<(ostream& out, UnionFindSet &ufs)//输出并查集所有元素
    {
        out<<ufs.parent;                                   //输出顺序表，形式为“(,)”
        return out;
    }
    int findRoot(int x);                                   //查找并返回元素x所在树的根下标
    bool combine(int x, int y);                            //集合并运算
    int collapsingFind(int x);                             //查找并返回元素x所在树的根下标，同时按照折叠规则压缩路径
};

int UnionFindSet::findRoot(int i)                          //查找并返回元素x所在树的根下标。算法沿着父指针向上寻找直到根
{
    while (parent[i]>=0) 
        i = parent[i];
    return i; 
}

    //查找并返回元素i所在树的根下标，同时按照折叠规则压缩路径
    //算法沿着父指针向上寻找直到根，将从i到根路径上的所有结点都改成根的孩子
int UnionFindSet::collapsingFind(int i)
{
    int root=i;
    while (parent[root]>=0)                                //找到i所在树的根结点下标
        root = parent[root];

    while (root!=i && parent[i]!=root)                     //当i不是根且不是根的孩子时
    {
        int pa = parent[i];
        parent[i]=root;                                    //将i作为root的孩子结点
        i=pa;                                              //向上到i的父结点
    }
    return root;                                           //返回根结点下标
}

    //集合并运算，当i、j不在同一棵树中，则合并结点i和j所在的两棵树，返回true；否则返回false
    //算法首先查找分别获得结点i和j所在树的根，将结点数较多的一棵树的根作为另一棵树根的孩子结点
bool UnionFindSet::combine(int i, int j)
{
//    int rooti=findRoot(i), rootj=findRoot(j);              //rooti、rootj分别获得i和j所在树的根
    int rooti=collapsingFind(i), rootj=collapsingFind(j);  //rooti、rootj分别获得i和j所在树的根
    if (rooti!=rootj)                                      //当i、j不在同一棵树中，则合并i和j所在的两棵树
        if (parent[rooti] <= parent[rootj])                //rooti树结点数（负）较多
        {                                                  //将j所在的树合并到i所在的树
            parent[rooti] += parent[rootj];                //结点数相加
            parent[rootj] = rooti;                         //将rootj作为rooti的孩子，数组元素为父结点下标
        }
        else                                               //将i所在的树合并到j所在的树
        {
            parent[rootj] += parent[rooti];
            parent[rooti] = rootj;
        }
    return rooti!=rootj;                                   //返回合并与否结果
}
