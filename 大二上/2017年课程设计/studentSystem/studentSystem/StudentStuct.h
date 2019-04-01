#ifndef STUDENTSTRUCT_H
#define STUDENTSTRUCT_H
#include "Student.h"
class StudentStruct
{
public:
    Student* studentArray;  //示例：studentArray[i].setID(aID);
    int stucount;           //学生计数
    StudentStruct(int tempcount):studentArray(nullptr),stucount(tempcount)
    {
        studentArray = new Student[stucount];
    }
    ~StudentStruct()
    {
        delete []studentArray;
        stucount = 0;
    }
    void readtostruct(Student* temphead)//向结构体数组中拷贝数据
    {
        Student* tempp3(temphead);
        for(int m=0;m<stucount;++m)
        {
            studentArray[m].setstudentID(tempp3->getstudentID());
            studentArray[m].setname(tempp3->getname());
            studentArray[m].setsubject(tempp3->getsubject());
            studentArray[m].settotalscore(); //设置个人总分
            studentArray[m].setaveragescore();
            studentArray[m].setnext(tempp3->getnext());
            studentArray[m].setprev(tempp3->getprev());
            tempp3 = tempp3->getnext();
        }
    }
};
#endif // STUDENTSTRUCT_H
