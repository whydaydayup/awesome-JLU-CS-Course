//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例5.5】 稀疏矩阵的三元组行的单链表。
//用顺序表作为行指针数组，SeqList的get(i)返回T& ?? 未调试

#include "Triple.h"                                        //矩阵三元组类
#include "SeqList.h"                                       //顺序表类（第2章）
#include "SortedSinglyList.h"                              //排序单链表类（第2章）

class LinkedMatrix                                         //三元组行的单链表存储的矩阵类 
{
  private:
    int rows, columns;                                     //矩阵行数、列数

    void init(int rows, int columns);                      //构造零矩阵，指定行数和列数

  public:
    SeqList<SortedSinglyList<Triple>*> rowlist;            //行指针顺序表，元素是指向排序单链表对象的指针

    LinkedMatrix(int rows=0);                              //构造零矩阵，指定行数，行列数相同
    LinkedMatrix(int rows, int columns);                   //构造零矩阵，指定行数和列数
    LinkedMatrix(int rows, int columns, Triple elem[], int n);  //由三元组数组指定初值
    ~LinkedMatrix();                                       //析构函数

    friend ostream& operator<<<>(ostream& out, LinkedMatrix&);//输出矩阵
    int get(int i, int j);                                 //返回第i行j列元素值
    void set(int i, int j, int x);                         //设置第i行j列元素值为x
    void set(Triple e);                                    //按三元组设置元素
    void setRowsColumns(int rows, int columns);            //设置矩阵行列数

    //以下实验5，未完成
    LinkedMatrix(LinkedMatrix &mat);                       //拷贝构造函数，深拷贝
    LinkedMatrix& operator=(LinkedMatrix &mat);            //重载=赋值，深拷贝，自动扩容
    bool operator==(LinkedMatrix &mat);                    //比较两个同阶矩阵是否相等
    void operator+=(LinkedMatrix &mat);                    //当前矩阵与mat矩阵相加
    LinkedMatrix operator+(LinkedMatrix &mat);             //返回当前矩阵与mat相加后的矩阵
    void operator*=(LinkedMatrix &mat);                    //当前矩阵与mat矩阵相乘，未实现
    LinkedMatrix operator*(LinkedMatrix &mat);             //返回当前矩阵与mat相乘后的矩阵
    LinkedMatrix transpose();                              //返回当前矩阵的转置矩阵
    bool isUpTriangular();                                 //判断当前矩阵是否为上三角矩阵
    bool isSymmetric();                                    //判断当前矩阵是否为对称矩阵
};

//（1）构造与析构
void LinkedMatrix::init(int rows, int columns)             //初始化
{
    if (rows>=0 && columns>=0)
    {
        this->rows = rows;
        this->columns = columns;
        for (int i=0; i<rows; i++)
            this->rowlist.insert(new SortedSinglyList<Triple>(true)); //顺序表尾插入，元素为指向空排序单链表（升序）的指针
    }
    else throw invalid_argument("矩阵行或列数为负数异常"); //抛出无效参数异常
}

LinkedMatrix::LinkedMatrix(int rows)                       //构造零矩阵，指定行数，行列数相同
{                                      //此处自动执行构造函数SeqList<T>()，SeqList.n=0，元素未初始化
    this->init(rows, rows);
}

LinkedMatrix::LinkedMatrix(int rows, int columns)          //构造零矩阵，指定行数和列数
{                                      //此处自动执行构造函数SeqList<T>()，SeqList.n=0，元素未初始化
    this->init(rows, columns);
}

//以三元组序列构造矩阵，参数分别指定矩阵的行数、列数、三元组序列、三元组序列长度
LinkedMatrix::LinkedMatrix(int rows, int columns, Triple elem[], int n)
{                                                //此处自动执行构造函数SeqList<T>()，SeqList.n=0
    this->init(rows, columns);
    for (int i=0; i<n; i++)
        this->set(elem[i]);
}

LinkedMatrix::~LinkedMatrix()                              //析构函数
{
    for (int i=0; i<this->rows; i++)
        this->rowlist[i]->~SortedSinglyList<Triple>();     //析构排序单链表，默认执行基类~SinglyList<Triple>()
}                            //此处执行~SeqList<T>()释放顺序表占用的一维数组

//（2） 输出
ostream& operator<<(ostream& out, LinkedMatrix &mat)       //输出稀疏矩阵
{
    for (int i=0; i<mat.rows; i++)
        out<<i<<" -> "<<(*mat.rowlist[i]);                 //输出第i条排序单链表
    return out;
}

//（3） 存取元素
//返回矩阵第i行j列元素值。若i、j指定序号无效则抛出异常。
//算法在第i行排序单链表中顺序查找三元组对象(i,j,0)，由Triple
//的==约定相等规则（仅比较i、j），若查找到返回元素值，否则返回0。
int LinkedMatrix::get(int i, int j)
{
    if (i>=0 && i<this->rows && j>=0 && j<this->columns) 
    {
        Node<Triple>* find = (*this->rowlist[i]).search(Triple(i,j,0));    //排序单链表顺序查找
        return find==NULL ? 0 : find->data.value;
    }
    throw out_of_range("矩阵元素的行或列序号越界异常");
}

//设置第i行j列元素值为x，若i、j指定序号无效则抛出异常。
//若x==0，则删除(i,j,?)结点（如果有）；若x!=0，则在第i条排序单链表中顺序查找三元组(i,j,x)，
//若找到则修改结点元素，否则插入结点
void LinkedMatrix::set(int i, int j, int x) 
{
    if (i>=0 && i<this->rows && j>=0 && j<this->columns) 
    {
        SortedSinglyList<Triple> *list = this->rowlist[i]; //获得第i条排序单链表
        if (x==0) 
            list->removeFirst(Triple(i,j,x));              //排序单链表删除(i,j,?)结点（如果有），顺序查找
        else
        {
            Node<Triple>* find = list->search(Triple(i,j,x));//顺序查找首次出现元素，执行Triple的==
            if (find!=NULL)
                find->data.value = x;                      //若找到，则修改该结点元素
            else list->insert(Triple(i,j,x));  
                //若未找到，则排序单链表插入结点由Triple的>约定插入位置，按i、j排序
        }
    }
    else throw out_of_range("矩阵元素的行或列序号越界异常");
}

void LinkedMatrix::set(Triple e)                           //以三元组设置矩阵元素
{
    this->set(e.row, e.column, e.value);
}

//（4） 设置行列数属性，改变矩阵大小
//设置矩阵行列数，若rows参数指定的行数较大，则将矩阵扩容，并复制原矩阵元素。用于7.2.2节图的邻接表
void LinkedMatrix::setRowsColumns(int rows, int columns)
{
    if (rows > this->rows)                                 //参数指定的行数较大时，矩阵扩容
        for (int i=this->rows; i<rows; i++)
            this->rowlist.insert(new SortedSinglyList<Triple>()); //顺序表尾插入，元素个数加1，自动扩容
    this->rows = rows;
    this->columns = columns;
}

//实验5