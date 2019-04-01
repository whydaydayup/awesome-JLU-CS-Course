#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;
class Student
{
private:
    int studentID;
    string name;
    int totalscore;
    int averagescore;
    //双向链表
    Student* prev;
    Student* next;
    int subject[10];//成绩数组
public:
    Student(int tempID=0,string tempname=" ",int temptotal=0,
            int tempaverage=0,Student* tempnext=nullptr,
            Student* tempprev=nullptr):studentID(tempID),
            name(tempname),totalscore(temptotal),averagescore(tempaverage),
            prev(tempprev),next(tempnext) { }
    void setstudentID(int tempID) { studentID = tempID; }
    void setname(string tempname) { name = tempname; }
    void settotalscore(int temptotal) { totalscore = temptotal; }
    void settotalscore()
    {
        for(int i=0;i<10;++i)
        {
            totalscore += subject[i];
        }
    }
    void setaveragescore(int tempaverage) { averagescore = tempaverage; }
    void setaveragescore() { averagescore = totalscore/10; }
    void setnext(Student* tempnext) { next = tempnext; }
    void setprev(Student* tempprev) { prev = tempprev; }
    void setsubject(int* tempsubject)
    {
        for(int i=0;i<10;++i)
            subject[i] = tempsubject[i];
    }
    int getstudentID()const { return studentID; }
    string getname()const { return name; }
    int gettotalscore()const { return totalscore; }
    int getaveragescore()const { return averagescore; }
    Student* getnext()const { return next; }
    Student* getprev()const { return prev; }
    int* getsubject() { return subject; }

};
#endif // STUDENT_H

