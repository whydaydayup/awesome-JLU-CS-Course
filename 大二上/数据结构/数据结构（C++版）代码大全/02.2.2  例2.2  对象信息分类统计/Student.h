//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例2.2】对象信息分类统计与查找。
//学生信息

#include <iostream>
using namespace std;
#include "string.h"

struct Student
{
    char name[20];                                         //姓名
    double score;                                          //某门课程成绩
    friend ostream& operator<<(ostream& out, Student &stu) //重载输出流对象
    {
        out<<"("<<stu.name<<","<<stu.score<<")";
        return out;
    }
    //重载==关系运算符，比较两个Student对象是否相等，定义为仅比较name，意按name识别Student对象
    bool operator==(Student &stu)
    {
        return strcmp(this->name,stu.name)==0;   //调用string.h中函数比较两串是否相等
                //不能this->name==stu.name，意为比较字符数组首地址是否相等
    }
};

/*
    //重载>=关系运算符，比较两个Student对象大小，定义为比较Student的score域的大小
    bool operator>=(Student &stu)
    {
        return this->score >= stu.score;
    }
    bool operator<(Student &stu)                           //重载<关系运算符
    {
        return this->score < stu.score;
    }
*/