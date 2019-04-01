//《数据结构（C++版）（第3版）》 作者：叶核亚
//5.2.2   稀疏矩阵的压缩存储
//1. 稀疏矩阵非零元素的三元组类

#include<iostream>
using namespace std;

class Triple                                               //稀疏矩阵非零元素的三元组类
{
  public:
    int row, column, value;                                //行号、列号、元素值

    Triple(int row=0, int column=0, int value=0)           //构造稀疏矩阵三元组
    {
        if (row>=0 && column>=0)
        {
            this->row = row;                               //行号
            this->column = column;                         //列号
            this->value = value;                           //元素值
        }
        else throw invalid_argument("稀疏矩阵元素三元组的行/列序号非正数。");  //抛出无效参数异常
    }

    friend ostream& operator<<(ostream& out, Triple &t)   //输出三元组
    {
        out<<"("<<t.row<<","<<t.column<<","<<t.value<<")";
        return out;
    }

    //根据三元组位置比较两个三元组相等与大小，与元素值无关，约定三元组排序次序
    bool operator==(Triple &t)                            //比较三元组是否相等，识别对象，仅比较（行、列）
    {
        return this->row==t.row && this->column==t.column;
    }
    bool operator!=(Triple &t)
    {
        return !(*this==t);
    }

    bool operator>(Triple &t)                             //比较三元组大小，约定排序次序，仅比较（行、列）
    {
        return this->row>t.row || this->row==t.row && this->column>t.column;     //行主序
    }
    bool operator>=(Triple &t)
    {
        return this->row>t.row || this->row==t.row && this->column>=t.column;
    }
    bool operator<(Triple &t)
    {
        return this->row<t.row || this->row==t.row && this->column<t.column;
    }
    bool operator<=(Triple &t)
    {
        return this->row<t.row || this->row==t.row && this->column<=t.column;
    }

    Triple symmetry()                                     //返回行列对称元素
    {                                                     //以下先执行构造函数、拷贝构造函数，再执行析构
        return Triple(this->column, this->row, this->value);
    }
};
