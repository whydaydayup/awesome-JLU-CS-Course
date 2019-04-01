//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例2.2】对象信息分类统计与查找。

#include "Student.h"                                       //学生信息结构
#include "SeqList.h"                                       //顺序表类

//分类统计stulist线性表元素信息，分段信息存于grade数组，n指定grade数组长度，统计结果存于result数组
void groupCount(SeqList<Student> &list, int grade[], int n, int result[])
{
    for (int i=0; i<list.count(); i++)
    {
        Student stu = list[i];                             //获得list的第i个元素，执行Student默认的=
        for (int j=0; j<n-1; j++)
            if (stu.score>=grade[j] && stu.score<grade[j+1]) //判断stu范围
            {   result[j]++;
                break;
            }
    }
}

int main()
{
    Student group[]={{"王红",85},{"张明",75},{"李强",90},{"郑小春",80},{"陈新诺",60},{"吴宁",65},{"崔小兵",70}}; 
    SeqList<Student> list(group,7);                        //由指定数组构造顺序表
    int grade[]={0,60,70,80,90,100};                       //指定分段信息
    const int N=5; 
    int result[N]={0};                                     //存放统计结果
    char* str[]={"不及格","及格","中等","良好","优秀"};    //字符串数组指定分类名称
    groupCount(list, grade, 6, result);                    //分类统计
    cout<<"学生集合："<<list;                              //执行Student的<<
    cout<<"共"<<list.count()<<"人，成绩统计：";
    for (int i=0; i<N; i++)
        cout<<str[i]<<result[i]<<"人，";
    cout<<endl;
    Student key={"郑小春",0};                              //包含关键字值的数据元素，提供查找条件（仅提供name域）
    cout<<"查找"<<key<<"结果："<<list[list.search(key)]<<endl;

    system("pause");
    return 0;
}
/*
程序运行结果如下：
学生集合：((王红,85), (张明,75), (李强,90), (郑小春,80), (陈新诺,60), (吴宁,65), (崔小兵,70))
共7人，成绩统计：不及格0人，及格2人，中等2人，良好2人，优秀1人，
查找(郑小春,0)结果：(郑小春,80)
*/

/*
#include "SinglyLinkedList.h"                         //单链表类
double average(SeqList<Student> &stulist)                 	//求平均值
{
    int n=stulist.length();                      	//顺序表长度
    double sum=0;
    for (int i=0; i<n; i++)
         sum += stulist.get(i).score;            	//此处get(i)返回Student结构类型
    return n>0 ? sum/n: 0;                      	//给出0个元素结果，避免除数为0错误
}
double average(SinglyLinkedList<Student> &stulist)    //求平均值
{
    int n=stulist.length();                           //单链表长度
    if (n>0)
    {
        double sum=0;
        for (int i=0; i<n; i++)
             sum += stulist.get(i).score;             //此处get(i)返回Student结构类型
        return sum/n;
    }
    return 0.0;                                       //给出0个元素的结果，避免除数为0错误
}
*/


