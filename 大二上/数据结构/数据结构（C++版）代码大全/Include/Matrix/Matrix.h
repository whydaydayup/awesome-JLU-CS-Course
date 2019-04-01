//《数据结构（C++版）（第3版）》 作者：叶核亚
//5.1   数组
//【例5.1】  矩阵类。
//实现数学意义的矩阵类的存储及运算。7.2.1   图的邻接矩阵表示和实现 用
//本章只写图类够用的函数，矩阵运算作为思考题。
//矩阵类必须提供扩充容量功能，图类用，因为，图类没有权限对矩阵中的二维数组重新申请空间。

#include <iostream>
using namespace std;
#include <iomanip>                                         //包含setw(6)设置输出格式

class Matrix                                               //矩阵类
{
  private:
    int rows, columns;                                     //矩阵行数、列数
    int **element;                                         //动态二维数组，存储矩阵元素

    void init(int rows, int columns);                      //申请rows行columns列二维数组，未初始化
    void init(int rows, int columns, int x);               //申请rows行columns列二维数组，元素为x
    void copy(Matrix &mat);                                //复制mat矩阵所有元素到当前矩阵

  public:
    Matrix(int rows=0);                                    //构造rows阶方阵
    Matrix(int rows, int columns);                         //构造rows行columns列矩阵，元素未初始化
    Matrix(int rows, int columns, int x);                  //构造rows行columns列矩阵，元素值为x
    Matrix(int rows, int columns, int values[]);           //构造矩阵，由values一维数组提供元素
//？？    Matrix(int rows, int columns, int **mat);               //以二维数组构造矩阵，不行，不能识别int*与int**
    Matrix(Matrix &mat);                                   //拷贝构造函数，深拷贝，实验5
//??    Matrix(int rows, int columns, Matrix &mat);         //深拷贝，（7.5.2 Floyd算法用）
    Matrix& operator=(Matrix &mat);                        //重载=赋值，深拷贝，自动扩容，实验5
    ~Matrix();                                             //析构函数

    friend ostream& operator<<(ostream& out, Matrix&);     //输出矩阵中所有元素
    void set(int i, int j, int x);                         //设置第i行j列元素值为x
    void setRowsColumns(int rows, int columns);            //设置矩阵行列数，自动扩容
    //思考题5-1
    int getRows();                                         //返回矩阵行数
    int getColumns();                                      //返回矩阵列数
    int get(int i, int j);                                 //返回第i行j列元素值
    //以上教材第5章，第7章用

    //以下实验5
    bool operator==(Matrix &mat);                          //比较两个同阶矩阵是否相等
    void operator+=(Matrix &mat);                          //当前矩阵与mat矩阵相加
    Matrix operator+(Matrix &mat);                         //返回当前矩阵与mat相加后的矩阵
//    void operator*=(Matrix &mat);                          //当前矩阵与mat矩阵相乘，未实现
//    Matrix operator*(Matrix &mat);                         //返回当前矩阵与mat相乘后的矩阵
    Matrix transpose();                                    //返回当前矩阵的转置矩阵
    bool isUpTriangular();                                 //判断当前矩阵是否为上三角矩阵
    bool isSymmetric();                                    //判断当前矩阵是否为对称矩阵
};

//（1）构造与析构
void Matrix::init(int rows, int columns)                   //申请rows行columns列二维数组，未初始化
{
    if (rows>=0 && columns>=0)
    {
        this->rows = rows;
        this->columns = columns;
//        this->element = new int[rows][columns];          //编译错
        this->element = new int*[rows];              //先申请存储行信息的一维数组（rows行），元素类型为int*
        for (int i=0; i<rows; i++) 
            this->element[i] = new int[columns];     //再为每行申请一维数组（columns个元素），元素类型为int
    }
    else  throw invalid_argument("矩阵行或列数为负数异常");//抛出无效参数异常
}
void Matrix::init(int rows, int columns, int x)            //申请rows行columns列二维数组，元素为x
{
    this->init(rows, columns);
    for (int i=0; i<rows; i++)                             //初始化所有元素为x
        for (int j=0; j<columns; j++) 
            this->element[i][j] = x;
}

Matrix::Matrix(int rows)                                   //构造rows阶方阵，元素未初始化
{
    this->init(rows, rows);
}
Matrix::Matrix(int rows, int columns)                      //构造rows行columns列矩阵，元素未初始化
{
    this->init(rows, columns);
}
Matrix::Matrix(int rows, int columns, int x)               //构造rows行columns列矩阵，元素为x
{
    this->init(rows, columns, x);
}

//构造矩阵，values一维数按行主序提供rows行columns列矩阵元素
Matrix::Matrix(int rows, int columns, int values[])
{
    this->init(rows, columns);
    for (int i=0; i<rows; i++)
        for (int j=0; j<columns; j++)
            this->element[i][j] = values[i*columns+j];
}

Matrix::~Matrix()                                          //析构函数
{
    for (int i=0; i<rows; i++)                             //释放动态二维数组占用的内存空间
        delete(this->element[i]);                          //先释放每行的一维数组
    delete(this->element);                                 //最后释放存储行信息的一维数组
}

//（2）获得行列数属性和随机存取元素
int Matrix::getRows()                                      //返回矩阵行数
{
    return this->rows;
}
int Matrix::getColumns()                                   //返回矩阵列数
{
    return this->columns;
}

int Matrix::get(int i, int j)                              //返回第i行j列元素值//重载[][]下标未成功？？
{
    if (i>=0 && i<rows && j>=0 && j<columns) 
        return this->element[i][j];
    throw out_of_range("矩阵元素的行或列序号越界异常");
}

void Matrix::set(int i, int j, int x)                      //设置第i行j列元素值为x
{
    if (i>=0 && i<rows && j>=0 && j<columns) 
        this->element[i][j] = x;
    else throw out_of_range("矩阵元素的行或列序号越界异常");
}

//（3）输出
ostream& operator<<(ostream& out, Matrix &mat)             //输出矩阵所有元素
{
    out<<"矩阵（"<<mat.rows<<"×"<<mat.columns<<"）："<<endl;
    for (int i=0; i<mat.rows; i++)
    {
        for (int j=0; j<mat.columns; j++)
            out<<setw(6)<<mat.element[i][j];               //setw(6)设置输出格式，每数据占用6列
        out<<"\n";
    }
    return out;
}

//设置矩阵行列数，若rows、columns参数指定的行列数较大，则将矩阵扩容，并复制原矩阵元素。增加部分未初始化
//用于7.2.1节图的邻接矩阵
void Matrix::setRowsColumns(int rows, int columns)
{
    if (rows > this->rows || columns > this->columns)      //参数指定的行数或列数较大时
    {
        int rowsold = this->rows, columnsold=this->columns;
        int **temp = this->element;
        this->init(rows, columns);                         //申请rows行columns列矩阵
        for (int i=0; i<rowsold; i++)                      //复制原矩阵元素
            for(int j=0; j<columnsold; j++)
                this->element[i][j] = temp[i][j];
        
        for (int i=0; i<rowsold; i++)                      //释放原动态二维数组占用的内存空间
            delete(temp[i]);
        delete(temp);
    }
}
//以上教材第5章，第7章用


//以下实验5
//（4）复制、拷贝、赋值
void Matrix::copy(Matrix &mat)                             //复制mat矩阵所有元素到当前矩阵
{
    for (int i=0; i<mat.rows; i++) 
        for(int j=0; j<mat.columns; j++)
            this->element[i][j] = mat.element[i][j];
}

Matrix::Matrix(Matrix &mat)                                //拷贝构造函数，深拷贝
{
    this->init(mat.rows, mat.columns);                     //申请rows行columns列矩阵存储空间
    this->copy(mat);                                       //复制mat矩阵所有元素到当前矩阵，两矩阵行列数相同
}
/*//？？
Matrix::Matrix(int rows, int columns, Matrix &mat)         //重载拷贝构造函数，深拷贝（图类用，扩容，？？7.5.2 Floyd算法用）
{
    this->init(rows, columns);                             //申请矩阵rows行columns列存储空间，元素未赋初值
    this->copy(mat);                                       //复制mat矩阵
}*/

Matrix& Matrix::operator=(Matrix &mat)                     //矩阵重载=赋值，深拷贝，自动扩容
{
    if (this->rows < mat.rows || this->columns < mat.columns)//赋值为更大矩阵时，需要扩容
    {
         this->~Matrix();                                  //调用析构函数，释放element数组空间
         this->init(mat.rows, mat.columns);
    }
    for (int i=0; i<this->rows; i++)                       //复制mat矩阵所有元素到当前矩阵
        for(int j=0; j<this->columns; j++)
            this->element[i][j] = mat.element[i][j];
    return *this;                                          //返回当前对象引用
}

//实验5，矩阵运算
bool Matrix::operator==(Matrix &mat)                       //比较两个同阶矩阵是否相等
{
    if (this->rows!=mat.rows || this->columns!=mat.columns)
        return false;
    
    for (int i=0; i<this->rows; i++)
        for (int j=0; j<this->columns; j++)
             if (this->element[i][j]!=mat.element[i][j])
                 return false;
    return true;
}

void Matrix::operator+=(Matrix &mat)                       //当前矩阵与mat矩阵相加，*this+=mat
{
    if (this->rows==mat.rows && this->columns==mat.columns)
        for (int i=0; i<mat.rows; i++)
            for (int j=0; j<mat.columns; j++)
                this->element[i][j] += mat.element[i][j];
    else throw invalid_argument("两个矩阵阶数不同，不能相加");  //抛出无效参数异常
}

Matrix Matrix::operator+(Matrix &mat)                      //返回当前矩阵与mat相加后的矩阵，*this+mat
{
    if (this->rows==mat.rows && this->columns==mat.columns)
    {
        Matrix temp(*this);                                //执行深拷贝
        temp += mat;
        return temp;                                       //执行深拷贝
    }
    throw invalid_argument("两个矩阵阶数不同，不能相加");  //抛出无效参数异常
}

Matrix Matrix::transpose()                                 //返回当前矩阵的转置矩阵
{
    Matrix trans(this->columns, this->rows);               //创建空矩阵
    for (int i=0; i<this->rows; i++)
        for (int j=0; j<this->columns; j++)
            trans.element[j][i]=this->element[i][j]; 
    return trans;                                          //执行深拷贝
}

bool Matrix::isUpTriangular()                              //判断当前矩阵是否为上三角矩阵
{
    if (this->rows!=this->columns)
        return false;
    for (int i=0; i<this->rows; i++)
        for (int j=0; j<i; j++)
            if (this->element[i][j]!=0)                    //下三角元素应为0
                return false;
    return true;
}

bool Matrix::isSymmetric()                                //判断当前矩阵是否为对称矩阵
{
    if (this->rows!=this->columns)
        return false;
    for (int i=0; i<this->rows; i++)
        for (int j=0; j<i; j++)
            if (this->element[i][j]!=this->element[j][i])
                 return false;
    return true;
}


/*
    void fill(int value);                                  //设置所有元素值为value
    void toTranspose();                                      //将当前矩阵转置，不需要了，仍然要创建新矩阵
没有实现重载[][]    
//？？？
   int& operator()(int i,int j)                     //重载函数调用()运算符
    {
       return this->element[i][j];
    }

int Matrix::saddlePoint()       //返回鞍点值
{
}
*/