//2.2.2   顺序表 2. 顺序表的浅拷贝与深拷贝
//2.2.3   排序顺序表
//10.  虚函数与滞后联编
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.2】  ☆☆排序顺序表。

#include "SortedSeqList.h"                                 //排序顺序表类，包含"Array.h"

int main()
{
    const int N=10, SIZE=100; 
    int values[N]={0};
    random(values,N,SIZE);                                 //声明在例1.3 Array.h中

    //（1） 编译时多态解决不了的问题，教材第48页，虚函数的必要性
    //（2） 运行时多态，滞后联编与虚函数
    //SeqList类声明insert(T x)为virtual虚函数与否  
    SeqList<int> *p = new SeqList<int>(values, N);         //p指针指向顺序表对象
    p->insert(50);                                         //执行SeqList类的insert(x)函数，顺序表尾插入
    cout<<"p->new SeqList()：      "<<*p;

    p = new SortedSeqList<int>(values, N);                 //p指针指向排序顺序表对象，赋值相容
    p->insert(50);                                         //执行SeqList类或子类哪个类的insert(x)函数？
    cout<<"p->new SortedSeqList()："<<*p;

    // int search(T key, int start=0); 声明virtual与否
    cout<<"查找50返回序号："<<p->search(50)<<endl;         //执行SeqList类或子类哪个类的search(key)函数？

//    p->insertUnrepeatable(50);                           //编译错，insertUnrepeatable不是SeqList的成员
//程序运行结果及分析见习题解答2.2。




    //二义性问题讨论
    SeqList<int> *q = new SortedSeqList<int>(*p);          //p指针指向排序顺序表对象，执行SortedSeqList(SeqList<T> &list)
                                   //没有二义性问题，因为与SortedSeqList(SortedSeqList<T> &list)构造函数参数列表不同，重载
    cout<<"q->new SortedSeqList()："<<*q;
    q->insert(50);                                         //执行
    cout<<"插入50："<<*q;

    system("pause");
    return 0;
}

/*
程序运行结果。

*/
    
