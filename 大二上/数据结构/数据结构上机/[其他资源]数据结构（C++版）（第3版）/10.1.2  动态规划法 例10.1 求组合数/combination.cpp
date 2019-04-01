//10.1.2   动态规划法
//【例10.1】采用动态规划法求组合数。
//【试10.2】采用回溯法求指定集合的所有子集。
//【例10.3】采用回溯法输出从n个元素中选择m个的所有组合。

#include <iostream>
using namespace std;

//【例10.1】采用动态规划法求组合数。
//① 分治法求组合数
int combine(int m, int n)                                  //返回组合数Cmn，分治策略递归算法
{
    if (n>0 && (m==0 || m==n))                             //边界条件，直接解决问题，没有递归调用
        return 1;
    if (m>0 && n>m)                                        //下一句分解成2个子问题，递归调用，返回各子问题合并后的解
        return combine(m-1, n-1) + combine(m, n-1); 
    throw invalid_argument("组合数参数错误。");            //抛出无效参数异常
}

//② 动态规划法求组合数
int** createYanghui(int n)                                 //求n行杨辉三角，返回三角形的动态二维数组首地址
{
    if (n<=0)
        return NULL;
    int **yanghui = new int*[n];                           //申请n个一维数组(n行)，元素类型为int*
    for (int i=0; i<n; i++)
    {
        yanghui[i] = new int[i+1];                         //为每行申请i+1个元素的一维数组，类型为int
        yanghui[i][0] = yanghui[i][i] = 1;                 //每行首尾值为1
        for (int j=1; j<i; j++)        
            yanghui[i][j] = yanghui[i-1][j-1]+yanghui[i-1][j];
                                 //第i行j列元素为其上一行（i-1）前两个元素（j-1、j）之和
    }
    return yanghui;                                        //返回二维数组首地址
}

void print(int **yanghui, int n)                           //输出三角形的动态二维数组
{
    cout<<"杨辉三角："<<endl;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<=i; j++)
            cout<<yanghui[i][j]<<" ";
        cout<<endl;
    }
}

int combination(int** yanghui, int m, int n)               //从杨辉三角二维数组获得组合数Cmn返回，O(1)
{
    if (n>0 && (m==0 || m==n))
        return 1;
    if (m>0 && n>m && yanghui!=NULL)
        return yanghui[n][m];
    throw invalid_argument("组合数参数错误。");            //抛出无效参数异常
}

//【试10.2】采用回溯法求指定集合的所有子集。
template <class T>
void printSubset(T set[], int n)                           //输出set集合（n个元素）的所有子集
{
    bool *x = new bool[n];                                 //初值为true
    printSubset(set, n, 0, x);
    cout<<endl;
}

template <class T>
void printSubset(T set[], int n, int i, bool x[])          //递归回溯
{
    if (i<n)
    {
        x[i]=false;
        printSubset(set, n, i+1, x);
        x[i]=true;
        printSubset(set, n, i+1, x);
    }
    else
        printX(set, n, x);
}

template <class T>
void printX(T set[], int n, int x[])                      //输出set的一个解，形式为“(,)”；子集，形式为“{,}”
{
    cout<<"(";                                           //输出set的一个解，形式为“(,)”
    if (n>0)
    {
        cout<<x[0];
        for (int i=1; i<n; i++)
            cout<<","<<x[i];
    }
    cout<<") ";
}

template <class T>
void printX(T set[], int n, bool x[])                      //输出set的一个解，形式为“(,)”；子集，形式为“{,}”
{
    cout<<"{";                                             //输出set的一个子集，形式为“{,}”
    bool first=true;
    for (int i=0; i<n; i++)
        if (x[i])
        {
            if (!first)
                cout<<",";
            else
                first = !first;
            cout<<set[i];
        }
    cout<<"} ";
}

//【例10.3】采用回溯法输出从n个元素中选择m个元素的所有组合。
template <class T>
void printCombined(T set[], int m, int n)                  //输出从set集合的n个元素中选择m个元素的所有组合
{
    bool *x = new bool[n];                                 //一个n元组，初值全为true，解向量
    printCombined(set, m, n, x, 0, 0);
    cout<<endl;
}

//从set集合的n个元素中选择m个元素的所有组合，x[]表示一个n元组（解向量），递归回溯
//求x[i]元素值，0≤i<n；j计数x[]中取值为1的元素个数，0≤j<m，约束条件
template <class T>
void printCombined(T set[], int m, int n, bool x[], int i, int j)
{
    if (i<n)
    { 
        if (j+n-i>m)                                       //限界剪枝，仅当j加剩余n-i个选择可能得到解时，搜索子树
        {
            x[i]=false;                                    //左子树取值
            printCombined(set, m, n, x, i+1, j);           //求x[i+1]元素值，j没变，递归调用
        }
        if (j<m)                                           //约束剪枝，仅当满足约束条件时，搜索子树
        {
            x[i]=true;                                     //右子树取值
            printCombined(set, m, n, x, i+1, j+1);         //求x[i+1]元素值，j+1，递归调用
        }
    }
    else
        printX(set, n, x);                                 //递归结束，遍历一条从根到叶子的路径，得到一个解输出
}

//迭代回溯？？
//从set集合的n个元素中选择m个元素的所有组合，x[]表示一个n元组（解向量）
//求x[i]元素值，0≤i<n；j计数x[]中取值为1的元素个数，0≤j<m，约束条件
template <class T>
void combine(T set[], int m, int n)                  //输出从set集合的n个元素中选择m个元素的所有组合
{
    int *x = new int[n];                                 //一个n元组，未初始化，解向量
    int i=0;
    while (i<n)
    { 
        int j=0;
        if (j+n-i>m)                                       //限界剪枝，仅当j加剩余n-i个选择可能得到解时，搜索子树
        {
            x[i++]=0;                                    //左子树取值
        }
        if (j<m)                                           //约束剪枝，仅当满足约束条件时，搜索子树
        {
            x[i++]=1;                                     //右子树取值
            j++;         //求x[i+1]元素值，j+1，递归调用
        }
        else
            i--;
        if (i==n)
            printX(set, n, x);                             //遍历一条从根到叶子的路径，得到一个解输出
    }
    cout<<endl;
}
/*
        if (x[i]<=n)
            if (i==n)                            //求得一个解
            {
                count++;
                print(n);
            }
            else x[++i]=0;
        else i--;
    }
}
*/
int main()
{
/*    //例10.1 ② 动态规划法求组合数
    int m=2, n=5;
    int** yanghui = createYanghui(n+1);
    print(yanghui, n+1);
    cout<<"组合数combination("<<m<<","<<n<<")="<<combination(yanghui, m, n)<<endl;
*/

    //10.1.4 回溯法 图10.12子集
    //【思考题10-1】输出一个集合（n个元素）的所有子集。
    int n=4;
    char set[]={'A','B','C','D','E'};
    bool x[]={1,1,1,1,1}; 
    printX(set, n, x);
    cout<<"集合的所有子集：";
    printSubset(set, n);

    //【例10.3】采用回溯法输出从n个元素中选择m个的所有组合。
    int** yanghui = createYanghui(n+1);                    //获得n+1行杨辉三角，见例10.1
    for (int m=0; m<=n; m++)
    {
        cout<<"C("<<m<<","<<n<<")="<<combination(yanghui, m, n)<<"，组合：";  //从杨辉三角获得组合数 ，见例10.1
        printCombined(set, m, n);                           //递归回溯
//？？        combine(set, m, n);                                 //迭代回溯
    }

    system("pause");
    return 0;
}


/*
杨辉三角：
1 
1 1 
1 2 1 
1 3 3 1 
1 4 6 4 1 
1 5 10 10 5 1 

{A,B,C} 集合
所有子集：{} {C} {B} {B,C} {A} {A,C} {A,B} {A,B,C} 
C(3,0)=1，组合：{} 
C(3,1)=3，组合：{C} {B} {A} 
C(3,2)=3，组合：{B,C} {A,C} {A,B} 
C(3,3)=1，组合：{A,B,C} 


{A,B,C,D} 集合
所有子集：{} {D} {C} {C,D} {B} {B,D} {B,C} {B,C,D} {A} {A,D} {A,C} {A,C,D} {A,B} {A,B,D} {A,B,C} {A,B,C,D} 
C(4,0)=1，组合：{} 
C(4,1)=4，组合：{D} {C} {B} {A} 
C(4,2)=6，组合：{C,D} {B,D} {B,C} {A,D} {A,C} {A,B} 
C(4,3)=4，组合：{B,C,D} {A,C,D} {A,B,D} {A,B,C} 
C(4,4)=1，组合：{A,B,C,D} 

{A,B,C,D,E} 集合
所有子集：{} {E} {D} {D,E} {C} {C,E} {C,D} {C,D,E} {B} {B,E} {B,D} {B,D,E} {B,C} {B,C,E} {B,C,D} {B,C,D,E} {A} {A,E} {A,D} {A,D,E} {A,C} {A,C,E} {A,C,D} {A,C,D,E} {A,B} {A,B,E} {A,B,D} {A,B,D,E} {A,B,C} {A,B,C,E} {A,B,C,D} {A,B,C,D,E} 
C(5,0)=1，组合：{} 
C(5,1)=5，组合：{E} {D} {C} {B} {A} 
C(5,2)=10，组合：{D,E} {C,E} {C,D} {B,E} {B,D} {B,C} {A,E} {A,D} {A,C} {A,B} 
C(5,3)=10，组合：{C,D,E} {B,D,E} {B,C,E} {B,C,D} {A,D,E} {A,C,E} {A,C,D} {A,B,E} {A,B,D} {A,B,C} 
C(5,4)=5，组合：{B,C,D,E} {A,C,D,E} {A,B,D,E} {A,B,C,E} {A,B,C,D} 
C(5,5)=1，组合：{A,B,C,D,E} 


*/


