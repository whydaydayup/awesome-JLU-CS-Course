#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <windows.h>
#include "Student.h"
#include "StudentStuct.h"
#include "Search.h"
#include "Sort.h"
using namespace std;

class StudentList
{
private:
    Student* head;//头指针
    Student* tail;//尾指针
    int studentcount;//学生人数计数器
    string f;//文件路径字符串
    bool flag;
    //成绩数据辅助数组
    int allscore[10];
    int maxscore[10];
    int minscore[10];
    int averscore[10];
public:
    StudentList(Student* temphead=nullptr,Student* temptail=nullptr,int tempcount=0,string tf="studentmessage.txt",bool tflag=false)
                      :head(temphead),tail(temptail),studentcount(tempcount),f(tf),flag(tflag)
    {
        for(int m=0;m<10;++m)
        {
            allscore[m] = 0;
            maxscore[m] = 0;
            minscore[m] = 0;
            averscore[m] = 0;
        }
    }
    ~StudentList() { clearList(); }
    /****************************************************************/
    Student* gethead() { return head; }
    void sethead(Student* ahead) { head = ahead; }
    int getstudentcount() { return studentcount; }
    /********************************打印平均成绩********************************/
    void displayaverscore()
    {
        system("cls");
        cout << "当前表中各科平均分为:  "<<endl;
        for(int m=0;m<10;++m)
            cout << "科目" << m+1 << "：" << averscore[m] << endl;
        cout << endl;
        system("pause");
    }
    void displayaverscore(int k)
    {
        system("cls");
        cout << "该科目平均分为:  " << averscore[k] << endl;
        system("pause");
    }
    /*******************************打印最低分*********************************/
    void displayminscore()
    {
        system("cls");
        cout << "当前表中各科最低分为:  "<<endl;;
        for(int m=0;m<10;++m)
            cout << "科目" << m+1 << "：" << minscore[m] << endl;
        cout << endl;
        system("pause");
    }
    void displayminscore(int k)
    {
        system("cls");
        cout << "该科目最低分为:  " << minscore[k] << endl;
        system("pause");
    }
    /*******************************打印最高分*********************************/
    void displaymaxscore()
    {
        system("cls");
        cout << "当前表中各科最高分为:  "<<endl;
        for(int m=0;m<10;++m)
            cout << "科目" << m+1 << "：" << maxscore[m] << endl;
        cout << endl;
        system("pause");
    }
    void displaymaxscore(int k)
    {
        system("cls");
        cout << "该科目最高分为:  " << maxscore[k] << endl;
        system("pause");
    }
    /*********************************清空链表*******************************/
    void clearList()
    {
        Student* current(head);
        while(head!=nullptr)//delete
        {
            head = head->getnext();
            delete current;
            current = head;
        }
        head = nullptr;
        current = nullptr;
        tail = nullptr;
        studentcount = 0;
        for(int m=0;m<10;++m)
        {
            minscore[m] = 0;
            maxscore[m] = 0;
            allscore[m] = 0;
        }
    }
    /*********************************修改学生信息*******************************/
    void changemessage()
    {
        system("cls");
        cout << "请输入要修改的学生学号：" << endl;
        int tempID(0);
        cin >> tempID;
        //查找该结点
        Student* tempp(head);
        int acount(0);
        for(int j=0;j<studentcount;++j)
        {
            if(tempp->getstudentID()==tempID)
                break;
            acount++;
            tempp = tempp->getnext();
        }
        int k(acount);
        Student* current(nullptr);
        //移动current到指定位置
        if(k>studentcount/2)
        {
            current = tail;
            for(int i=studentcount-1;i>k;--i)
                current = current->getprev();
        }
        if(k<=studentcount/2)
        {
            current = head;
            for(int i=0;i<k;++i)
                current = current->getnext();
        }
        cout << "学号每人固定,不可更改. 请按如下提示回复：" << endl;
        cout << "回复1: 修改学生姓名" << endl;
        cout << "回复2: 修改科目成绩" << endl;
        string stra;
        cin >> stra;
        while(stra!="1"&&stra!="2")
        {
            cout << "回复格式错误！请按如下提示回复：" << endl;
            cout << "回复1: 修改学生姓名" << endl;
            cout << "回复2: 修改科目成绩" << endl;
        }
        if(stra=="1")
        {
            cout << "请输入新的学生姓名：";
            string temps;
            cin >> temps;
            current->setname(temps);
            cout << "修改完成." << endl;
        }
        if(stra=="2")
        {
            string aflag("1");
            int number1(0);
            while(aflag=="1")
            {
                cout << "科目编号0-9,请输入想要修改的科目编号: ";
                cin >> number1;
                while(number1<0||number1>9)
                {
                    cout << "编号输入错误,请重新输入: ";
                    cin >> number1;
                }
                cout << "请输入该科目新成绩(0-100):" << endl;
                int number2(0);
                cin >> number2;
                while(number2<0||number2>100)
                {
                    cout << "成绩输入错误,请重新输入(0-100): ";
                    cin >> number2;
                }
                for(int m=0;m<10;++m)
                   allscore[m] -= current->getsubject()[m];
                current->getsubject()[number1] = number2;
                for(int m=0;m<10;++m)
                   allscore[m] += current->getsubject()[m];
                for(int m=0;m<10;++m)
                   averscore[m] = allscore[m] / studentcount;
                traverse_getmaxmin();
                cout << "继续修改其他科目成绩请回复1,否则回复其他" << endl;
                cin >> aflag;
            }
        }
        this->outFileInOrder(f);
        system("pause");
    }
    /*********************************工具函数*******************************/
    void traverse_getmaxmin()   //遍历链表求最高分和最低分(仅在删除函数中使用)
    {
        for(int m=0;m<10;++m)
        {
            maxscore[m] = head->getsubject()[m];
            minscore[m] = head->getsubject()[m];
        }
        Student* tempp(head->getnext());
        while(tempp!=nullptr)
        {
            for(int m=0;m<10;++m)
            {
                if(tempp->getsubject()[m] < minscore[m])
                    minscore[m] = tempp->getsubject()[m];
                if(tempp->getsubject()[m] > maxscore[m])
                    maxscore[m] = tempp->getsubject()[m];
            }
            tempp = tempp->getnext();
        }
    }
    /********************************删除学生信息********************************/
    void deletestudent()
    {
        system("cls");
        cout << "请输入要删除的学生学号：" << endl;
        int tempID(0);
        cin >> tempID;
        //查找该结点
        Student* tempp(head);
        int acount(0);
        for(int j=0;j<studentcount;++j)
        {
            if(tempp->getstudentID()==tempID)
                break;
            acount++;
            tempp = tempp->getnext();
        }
        int k(acount);
        Student* current(nullptr);
        //移动current到指定位置
        if(k==0)
        {
            current = head;
            head = head->getnext();
            head->setprev(nullptr);
            for(int m=0;m<10;++m)
                allscore[m] -= current->getsubject()[m];
            delete current;
            studentcount--;
            for(int m=0;m<10;++m)
                averscore[m] = allscore[m] / studentcount;
            traverse_getmaxmin();
            return;
        }
        if(k==(studentcount-1))
        {
            current = tail;
            tail = tail->getprev();
            tail->setnext(nullptr);
            for(int m=0;m<10;++m)
                allscore[m] -= current->getsubject()[m];
            delete current;
            studentcount--;
            for(int m=0;m<10;++m)
                averscore[m] = allscore[m] / studentcount;
            traverse_getmaxmin();
            return;
        }
        if(k>studentcount/2)
        {
            current = tail;
            for(int i=studentcount-1;i>k;--i)
                current = current->getprev();
        }
        if(k<=studentcount/2)
        {
            current = head;
            for(int i=0;i<k;++i)
                current = current->getnext();
        }
        //判断k
        current->getprev()->setnext(current->getnext());
        current->getnext()->setprev(current->getprev());
        for(int m=0;m<10;++m)
                allscore[m] -= current->getsubject()[m];
        delete current;
        studentcount--;
        for(int m=0;m<10;++m)
                averscore[m] = allscore[m] / studentcount;
        traverse_getmaxmin();
        this->outFileInOrder(f);
        system("pause");
    }
    /*******************************插入学生信息（调用交互式输入函数）*********************************/
    void insertstudent()
    {
        interaction();
    }
    /*******************************正序写回文件*********************************/
    void outFileInOrder(const string& str)
    {
        ofstream outfile(str);
        Student* current(head);
        if(outfile.is_open())
        {
            for(int i=0;i<studentcount;++i)
            {
                outfile << current->getstudentID() << " ";
                outfile << current->getname() << " ";
                for(int j=0;j<10;++j)
                    outfile << current->getsubject()[j] << " ";
                current = current->getnext();
                outfile << endl;
            }
        }
        else
        {
            cout << "打开文件失败！" << endl;
            return;
        }
    }
    /*********************************倒序写回文件*******************************/
    void outFileReverse(const string& str)
    {
        ofstream outfile(str);
        Student* current(tail);
        if(outfile.is_open())
        {
            for(int i=0;i<studentcount;++i)
            {
                outfile << current->getstudentID() << " ";
                outfile << current->getname() << " ";
                for(int j=0;j<10;++j)
                    outfile << current->getsubject()[j] << " ";
                current = current->getprev();
            }
        }
        else
        {
            cout << "打开文件失败！" << endl;
            return;
        }
    }
    /********************************交互式输入函数********************************/
    void interaction()
    {
        system("cls");
        string stopflag("1");
        while(stopflag!="0")
      {
        cout << "请输入学生的学号(注意:学号唯一且不可更改):" << endl;
        cout << "格式为:入学年份/班号/班内编号,入学年份允许范围为1990-2017,"
        "班号允许范围为01-99,班内编号允许范围为01-99" << endl;
        int aID(0);
        cin >> aID;
        while(aID>20179999 || aID<19900101)
        {
            cout << "学号格式错误,请重新按照格式要求输入:" << endl;
            cout << "格式为:入学年份/班号/班内编号,入学年份允许范围为1990-2017,"
            "班号允许范围为01-99,班内编号允许范围为01-99" << endl;
            cin >> aID;
        }
        cout << "格式正确,若想继续请回复0,返回修改请回复其他:" << endl;
        string aflag("0");
        cin >> aflag;
        while(aflag!="0")
        {
            cout << "请输入学生的学号(注意:学号唯一且不可更改):" << endl;
            cout << "格式为:入学年份/班号/班内编号,入学年份允许范围为1990-2017,"
            "班号允许范围为01-99,班内编号允许范围为01-99" << endl;
            cin >> aID;
            while(aID>20179999 || aID<19900101)
            {
               cout << "学号格式错误,请重新按照格式要求输入:" << endl;
               cout << "格式为:入学年份/班号/班内编号,入学年份允许范围为1990-2017,"
               "班号允许范围为01-99,班内编号允许范围为01-99" << endl;
               cin >> aID;
            }
            cout << "格式正确,若想继续请回复0,返回修改请回复其他:" << endl;
            cin >> aflag;
        }
        /*****************************/
        cout << "请输入学生的姓名：" << endl;
        string tempstr;
        cin >> tempstr;
        cout << "若想返回修改请回复1,继续请回复0:" << endl;
        cin >> aflag;
        while(aflag!="0")
        {
             cout << "请输入学生的姓名：" << endl;
             cin >> tempstr;
             cout << "若想继续请回复0,返回修改请回复其他:" << endl;
             cin >> aflag;
        }
        /********************************/
        int grade[10]={0};
        cout << "请输入学生十门课程的成绩:(无成绩请用0代替,成绩许可范围为0-100)" << endl;
        for(int i=0;i<10;++i)
        {
            cout << "第" << i+1 << "门课程成绩:  ";
            cin >> grade[i];
            while(grade[i]>100||grade[i]<0)
            {
                cout << "成绩输入有误！范围限定0-100.请重新输入: ";
                cin >> grade[i];
            }
        }
        /***********************************/
        //如果此时链表为空
        if(head==nullptr)
        {
            head = new Student(aID,tempstr);
            head->setsubject(grade);
            head->settotalscore();
            head->setaveragescore();
            tail = head;
            studentcount++;
            for(int m=0;m<10;++m)  //第一个人上擂台
            {
                minscore[m] = head->getsubject()[m];
                maxscore[m] = head->getsubject()[m];
                allscore[m] = 0;
            }
            for(int m=0;m<10;++m)
            {
                allscore[m] += head->getsubject()[m];
                if(head->getsubject()[m] < minscore[m])
                    minscore[m] = head->getsubject()[m];
                if(head->getsubject()[m] > maxscore[m])
                    maxscore[m] = head->getsubject()[m];
            }
            for(int m=0;m<10;++m)
            {
                averscore[m] = allscore[m] / studentcount;
            }
        }
        //如果此时链表不为空
        else
        {
            //检索应插入的位置
            Student* tempp1(nullptr);
            if(aID < head->getstudentID())
            {
                tempp1 = new Student(aID,tempstr);
                tempp1->setsubject(grade);
                tempp1->settotalscore();
                tempp1->setaveragescore();
                tempp1->setnext(head);
                head->setprev(tempp1);
                head = tempp1;
                studentcount++;
                for(int m=0;m<10;++m)
                {
                    allscore[m] += tempp1->getsubject()[m];
                    if(tempp1->getsubject()[m] < minscore[m])
                        minscore[m] = tempp1->getsubject()[m];
                    if(tempp1->getsubject()[m] > maxscore[m])
                        maxscore[m] = tempp1->getsubject()[m];
                }
                for(int m=0;m<10;++m)
                {
                    averscore[m] = allscore[m] / studentcount;
                }
            }
            else if(aID > tail->getstudentID())
            {
                tempp1 = new Student(aID,tempstr);
                tempp1->setsubject(grade);
                tempp1->setprev(tail);
                tempp1->settotalscore();
                tempp1->setaveragescore();
                tail->setnext(tempp1);
                tail = tempp1;
                studentcount++;
                for(int m=0;m<10;++m)
                {
                    allscore[m] += tempp1->getsubject()[m];
                    if(tempp1->getsubject()[m] < minscore[m])
                        minscore[m] = tempp1->getsubject()[m];
                    if(tempp1->getsubject()[m] > maxscore[m])
                        maxscore[m] = tempp1->getsubject()[m];
                }
                for(int m=0;m<10;++m)
                {
                    averscore[m] = allscore[m] / studentcount;
                }
            }
            else
            {
                Student* tempp2(head);
                while(true)
                {
                    if(tempp2->getstudentID()<aID && tempp2->getnext()->getstudentID()>aID)
                    {
                        //则应插在tempp2和tempp2的next之间
                        tempp1 = new Student(aID,tempstr);
                        tempp1->setsubject(grade);
                        tempp1->settotalscore();
                        tempp1->setaveragescore();
                        tempp1->setprev(tempp2);
                        tempp1->setnext(tempp2->getnext());
                        tempp2->setnext(tempp1);
                        tempp1->getnext()->setprev(tempp1);
                        studentcount++;
                        for(int m=0;m<10;++m)
                        {
                            allscore[m] += tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] < minscore[m])
                                minscore[m] = tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] > maxscore[m])
                                maxscore[m] = tempp1->getsubject()[m];
                        }
                        for(int m=0;m<10;++m)
                        {
                            averscore[m] = allscore[m] / studentcount;
                        }
                        break;
                    }
                    tempp2 = tempp2->getnext();

                }
            }
        }
        cout << "若不再继续录入其他学生信息请回复0,否则请回复其他:  ";
        cin >> stopflag;
      }
    }
    /********************************读取文件********************************/
    void readfile()
    {
        ifstream infile("studentmessage.txt");
        if(infile.is_open())
        {
            if(infile.eof())
            {
                cout << "本地文件为空！" << endl;
                return;
            }
            else
            {
                int tempID(0);
                string tempstr;
                int tempsub[10]={0};
              while(!infile.eof())
              {
                infile >> tempID >> tempstr;
                for(int j=0;j<10;++j)
                    infile >> tempsub[j];
                //如果此时链表为空
                if(head==nullptr)
                {
                    head = new Student(tempID,tempstr);
                    head->setsubject(tempsub);
                    head->settotalscore();
                    head->setaveragescore();
                    tail = head;
                    studentcount++;
                    for(int m=0;m<10;++m)  //第一个人上擂台
                    {
                        minscore[m] = head->getsubject()[m];
                        maxscore[m] = head->getsubject()[m];
                        allscore[m] = 0;
                    }
                    for(int m=0;m<10;++m)
                    {
                        allscore[m] += head->getsubject()[m];
                        if(head->getsubject()[m] < minscore[m])
                            minscore[m] = head->getsubject()[m];
                        if(head->getsubject()[m] > maxscore[m])
                            maxscore[m] = head->getsubject()[m];
                    }
                    for(int m=0;m<10;++m)
                    {
                        averscore[m] = allscore[m] / studentcount;
                    }
                }
                //如果此时链表不为空
                else if(head!=nullptr)
                {
                    //cout << "1" << endl;
                    //检索应插入的位置
                    Student* tempp1(nullptr);
                    if(tempID < head->getstudentID())
                    {
                        //cout << "2" << endl;
                        tempp1 = new Student(tempID,tempstr);
                        tempp1->setsubject(tempsub);
                        tempp1->settotalscore();
                        tempp1->setaveragescore();
                        tempp1->setnext(head);
                        head->setprev(tempp1);
                        head = tempp1;
                        studentcount++;
                        for(int m=0;m<10;++m)
                        {
                            allscore[m] += tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] < minscore[m])
                                minscore[m] = tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] > maxscore[m])
                                maxscore[m] = tempp1->getsubject()[m];
                        }
                        for(int m=0;m<10;++m)
                        {
                            averscore[m] = allscore[m] / studentcount;
                        }
                     }
                    if(tempID > tail->getstudentID())
                    {
                        //cout << "3" << endl;
                        tempp1 = new Student(tempID,tempstr);
                        tempp1->setsubject(tempsub);
                        tempp1->setprev(tail);
                        tempp1->settotalscore();
                        tempp1->setaveragescore();
                        tail->setnext(tempp1);
                        tail = tempp1;
                        studentcount++;
                        for(int m=0;m<10;++m)
                        {
                            allscore[m] += tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] < minscore[m])
                                minscore[m] = tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] > maxscore[m])
                                maxscore[m] = tempp1->getsubject()[m];
                        }
                        for(int m=0;m<10;++m)
                        {
                            averscore[m] = allscore[m] / studentcount;
                        }
                    }
                    if(tempID < tail->getstudentID() && tempID > head->getstudentID())
                    {
                        //cout << "4" << endl;
                        Student* tempp2(head);
                        while(true)
                        {
                             //cout <<"5" << endl;
                             if(tempp2->getstudentID() < tempID && tempp2->getnext()->getstudentID() > tempID)
                             {
                                 //则tempp1应插在tempp2和tempp2的next之间
                                 tempp1 = new Student(tempID,tempstr);
                                 tempp1->setsubject(tempsub);
                                 tempp1->settotalscore();
                                 tempp1->setaveragescore();
                                 tempp1->setprev(tempp2);
                                 tempp1->setnext(tempp2->getnext());
                                 tempp2->setnext(tempp1);
                                 tempp1->getnext()->setprev(tempp1);
                                 studentcount++;
                                 for(int m=0;m<10;++m)
                                 {
                                    allscore[m] += tempp1->getsubject()[m];
                                    if(tempp1->getsubject()[m] < minscore[m])
                                        minscore[m] = tempp1->getsubject()[m];
                                    if(tempp1->getsubject()[m] > maxscore[m])
                                        maxscore[m] = tempp1->getsubject()[m];
                                 }
                                 for(int m=0;m<10;++m)
                                 {
                                     averscore[m] = allscore[m] / studentcount;
                                 }
                                 break;
                             }
                             tempp2 = tempp2->getnext();

                        }
                    }

            }
        }
        }
        }
        else
        {
            cout <<"打开本地文件失败！" << endl;
        }
        infile.close();
    }
    /*******************************重载读取文件函数，读取指定路径********************************/
    void readfile(const string& str)
    {
        f=str;
        flag=true;
        ifstream infile(str);
        if(infile.is_open())
        {
            if(infile.eof())
            {
                cout << "本地文件为空！" << endl;
                return;
            }
            else
            {
                int tempID(0);
                string tempstr;
                int tempsub[10]={0};
              while(!infile.eof())
              {
                infile >> tempID >> tempstr;
                for(int j=0;j<10;++j)
                    infile >> tempsub[j];
                //如果此时链表为空
                if(head==nullptr)
                {
                    head = new Student(tempID,tempstr);
                    head->setsubject(tempsub);
                    head->settotalscore();
                    head->setaveragescore();
                    tail = head;
                    studentcount++;
                    for(int m=0;m<10;++m)  //第一个人上擂台
                    {
                        minscore[m] = head->getsubject()[m];
                        maxscore[m] = head->getsubject()[m];
                        allscore[m] = 0;
                    }
                    for(int m=0;m<10;++m)
                    {
                        allscore[m] += head->getsubject()[m];
                        if(head->getsubject()[m] < minscore[m])
                            minscore[m] = head->getsubject()[m];
                        if(head->getsubject()[m] > maxscore[m])
                            maxscore[m] = head->getsubject()[m];
                    }
                    for(int m=0;m<10;++m)
                    {
                        averscore[m] = allscore[m] / studentcount;
                    }
                }
                //如果此时链表不为空
                else if(head!=nullptr)
                {
                    //cout << "1" << endl;
                    //检索应插入的位置
                    Student* tempp1(nullptr);
                    if(tempID < head->getstudentID())
                    {
                        //cout << "2" << endl;
                        tempp1 = new Student(tempID,tempstr);
                        tempp1->setsubject(tempsub);
                        tempp1->settotalscore();
                        tempp1->setaveragescore();
                        tempp1->setnext(head);
                        head->setprev(tempp1);
                        head = tempp1;
                        studentcount++;
                        for(int m=0;m<10;++m)
                        {
                            allscore[m] += tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] < minscore[m])
                                minscore[m] = tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] > maxscore[m])
                                maxscore[m] = tempp1->getsubject()[m];
                        }
                        for(int m=0;m<10;++m)
                        {
                            averscore[m] = allscore[m] / studentcount;
                        }
                     }
                    if(tempID > tail->getstudentID())
                    {
                        //cout << "3" << endl;
                        tempp1 = new Student(tempID,tempstr);
                        tempp1->setsubject(tempsub);
                        tempp1->setprev(tail);
                        tempp1->settotalscore();
                        tempp1->setaveragescore();
                        tail->setnext(tempp1);
                        tail = tempp1;
                        studentcount++;
                        for(int m=0;m<10;++m)
                        {
                            allscore[m] += tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] < minscore[m])
                                minscore[m] = tempp1->getsubject()[m];
                            if(tempp1->getsubject()[m] > maxscore[m])
                                maxscore[m] = tempp1->getsubject()[m];
                        }
                        for(int m=0;m<10;++m)
                        {
                            averscore[m] = allscore[m] / studentcount;
                        }
                    }
                    if(tempID < tail->getstudentID() && tempID > head->getstudentID())
                    {
                        //cout << "4" << endl;
                        Student* tempp2(head);
                        while(true)
                        {
                             //cout <<"5" << endl;
                             if(tempp2->getstudentID() < tempID && tempp2->getnext()->getstudentID() > tempID)
                             {
                                 //则tempp1应插在tempp2和tempp2的next之间
                                 tempp1 = new Student(tempID,tempstr);
                                 tempp1->setsubject(tempsub);
                                 tempp1->settotalscore();
                                 tempp1->setaveragescore();
                                 tempp1->setprev(tempp2);
                                 tempp1->setnext(tempp2->getnext());
                                 tempp2->setnext(tempp1);
                                 tempp1->getnext()->setprev(tempp1);
                                 studentcount++;
                                 for(int m=0;m<10;++m)
                                 {
                                    allscore[m] += tempp1->getsubject()[m];
                                    if(tempp1->getsubject()[m] < minscore[m])
                                        minscore[m] = tempp1->getsubject()[m];
                                    if(tempp1->getsubject()[m] > maxscore[m])
                                        maxscore[m] = tempp1->getsubject()[m];
                                 }
                                 for(int m=0;m<10;++m)
                                 {
                                     averscore[m] = allscore[m] / studentcount;
                                 }
                                 break;
                             }
                             tempp2 = tempp2->getnext();

                        }
                    }

            }
        }
        }
        }
        else
        {
            cout <<"打开本地文件失败！" << endl;
        }
        infile.close();
    }
    /*******************************正序打印********************************/
    void displayInorder()
    {
        system("cls");
        if(studentcount==0)
        {
            cout << "表为空！" << endl;
            return;
        }
        cout << "当前共有学生：" << studentcount << "个" << endl;
        cout << "   学号     姓名      科目1  科目2  科目3  科目4  科目5  科目6  科目7  科目8  科目9  科目10  总成绩  平均成绩" <<endl;
        Student* tempp(head);
        for(int i=0;i<studentcount;++i)
        {
            cout << tempp->getstudentID() << "    " << tempp->getname() << "       ";
            for(int j=0;j<10;++j)
                cout << tempp->getsubject()[j] << "     ";
            cout << tempp->gettotalscore() << "     " << tempp->getaveragescore() ;
            cout << endl;
            tempp = tempp->getnext();
        }
        system("pause");
    }
    /*******************************倒序打印********************************/
    void displayReverse()
    {
        system("cls");
        if(studentcount==0)
        {
            cout << "表为空！" << endl;
            return;
        }
        cout << "当前共有学生：" << studentcount << "个" << endl;
        cout << "   学号     姓名      科目1  科目2  科目3  科目4  科目5  科目6  科目7  科目8  科目9  科目10  总成绩  平均成绩" <<endl;
        Student* tempp(tail);
        for(int i=0;i<studentcount;++i)
        {
            cout << tempp->getstudentID() << "    " << tempp->getname() << "       ";
            for(int j=0;j<10;++j)
                cout << tempp->getsubject()[j] << "     ";
            cout << tempp->gettotalscore() << "     " << tempp->getaveragescore() ;
            cout << endl;
            tempp = tempp->getprev();
        }
        system("pause");
    }
    /*******************************打印组合函数*********************************/
    void display()
    {
        system("cls");
        cout<<"请选择浏览学生信息的顺序（1.正序；2.倒序）：";
        int n=0;
        cin>>n;
        while(n!=1&&n!=2)
        {
            cout<<"输入有误，请重新输入！"<<endl;
            cin>>n;
        }
        if(n==1)
        {
            this->displayInorder();
            if(flag==false)
                this->outFileInOrder("studentmessage.txt");
            if(flag==true)
                this->outFileInOrder(f);
        }
        if(n==2)
        {
            this->displayReverse();
            if(flag==false)
                this->outFileReverse("studentmessage.txt");
            if(flag==true)
                this->outFileReverse(f);
        }
    }
    /*********************************读取文件组合函数*******************************/
    void read_file()
    {
        system("cls");
        string str;
        cout<<"请输入文件所在路径：";
        cin>>str;
        this->clearList();
        this->readfile(str);
        system("pause");
    }
    /********************************科目数据统计组合函数********************************/
    void substatistics()
    {
        system("cls");
        cout<<"请输入统计科目的内容（1.最高分；2.最低分；3.平均分）:";
        int n=0;
        cin>>n;
        while(n!=1&&n!=2&&n!=3)
        {
            cout<<"输入有误，请重新输入：";
            cin>>n;
        }
        if(n==1)
        {
            cout<<"请输入要查询的科目代码（1-10）或全部科目（0）：";
            int i=-1;
            cin>>i;
            while(i<0||i>10)
            {
                cout<<"输入有误，请重新输入：";
                cin>>i;
            }
            if(i==0)
            {
                this->displaymaxscore();
            }
            else
            {
                this->displaymaxscore(i-1);
            }
        }
        if(n==2)
        {
            cout<<"请输入要查询的科目代码（1-10）或全部科目（0）：";
            int i=-1;
            cin>>i;
            while(i<0||i>10)
            {
                cout<<"输入有误，请重新输入：";
                cin>>i;
            }
            if(i==0)
            {
                this->displayminscore();
            }
            else
            {
                this->displayminscore(i-1);
            }
        }
        if(n==3)
        {
            cout<<"请输入要查询的科目代码（1-10）或全部科目（0）：";
            int i=-1;
            cin>>i;
            while(i<0||i>10)
            {
                cout<<"输入有误，请重新输入：";
                cin>>i;
            }
            if(i==0)
            {
                this->displayaverscore();
            }
            else
            {
                this->displayaverscore(i-1);
            }
        }
    }
    /********************************查询学生信息组合函数*********************************/
    void searchstudent()
    {
        system("cls");
        StudentStruct astruct(this->getstudentcount());
        astruct.readtostruct(this->gethead());
        cout<<"请输入要查询的信息（1.学号；2.姓名）：";
        int n=0;
        cin>>n;
        while(n!=1&&n!=2)
        {
            cout<<"输入有误，请重新输入：";
            cin>>n;
        }
        if(n==1)
        {
            ID_ExactSearch(astruct);
        }
        if(n==2)
        {
            cout<<"请输入查询方式（1.精确查询；2.模糊查询）：";
            int m=0;
            cin>>m;
            while(m!=1&&m!=2)
            {
                cout<<"输入有误，请重新输入：";
                cin>>m;
            }
            if(m==1)
            {
                Name_ExactSearch(astruct);
            }
            if(m==2)
            {
                Name_FuzzySearch(astruct);
            }
        }
    }
    /*********************************成绩排序组合函数*********************************/
    void gradesort()
    {
        system("cls");
        StudentStruct astruct(this->getstudentcount());
        astruct.readtostruct(this->gethead());
        cout<<"请输入所需排序成绩的科目（科目1-10，总成绩11）：";
        int i;
        cin>>i;
        while(i<1||i>11)
        {
            cout<<"输入错误，请重新输入：";
            cin>>i;
        }
        switch(i)
        {
        case 1:Sort(1,astruct);break;
        case 2:Sort(2,astruct);break;
        case 3:Sort(3,astruct);break;
        case 4:Sort(4,astruct);break;
        case 5:Sort(5,astruct);break;
        case 6:Sort(6,astruct);break;
        case 7:Sort(7,astruct);break;
        case 8:Sort(8,astruct);break;
        case 9:Sort(9,astruct);break;
        case 10:Sort(10,astruct);break;
        case 11:Sort(11,astruct);break;
        }
    }
};
#endif // STUDENTLIST_H

