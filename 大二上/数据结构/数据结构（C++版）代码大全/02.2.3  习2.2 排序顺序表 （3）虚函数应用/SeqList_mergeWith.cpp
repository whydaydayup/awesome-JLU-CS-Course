//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2.2   顺序表 2. 顺序表的浅拷贝与深拷贝
//2.2.3   排序顺序表
//10.  虚函数与滞后联编
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.2】  ☆☆排序顺序表。
//（3） 虚函数应用

#include "SortedSeqList.h"                                 //排序顺序表类，包含"Array.h"

int main()
{
    const int N=7, SIZE=100; 
    int values[N]={0};
    random(values,N,SIZE);                                 //声明在例1.3 Array.h中

    //10.  虚函数与滞后联编，教材第47页
    //设SeqList类声明insert(T x)为virtual虚函数  
    SeqList<int> lista(values, N), listb(lista), listc, listd;
    SortedSeqList<int> slist1(lista), slist2(slist1), slist3;      //slist1(lista)由顺序表构造排序顺序表
    cout<<"lista(listb)：  "<<lista<<"slist1(slist2)："<<slist1;

//    lista += slist1;                                       //基类+=子类，首尾相连，合并连接
//    slist1 += listb;                                       //子类+=基类，排序顺序表插入合并，仍然排序
//    cout<<"lista+=slist1： "<<lista<<"slist1+=listb： "<<slist1;
  
//    cout<<"listb+slist2：  "<<(listb+slist2)<<"slist2+listb：  "<<(slist2+listb);  //后者可能有运行错

    //当子类没有覆盖+时，
//    listc = slist2 + listb;          
//    slist3 = slist2 + listb;        //子类没有覆盖+时，编译错，+的返回值类型为SeqList<T>，不能接受子类实例，无法转换

    //当子类覆盖+时，
    listc = listb + slist2;           //执行SeqList的+，返回SeqList实例，赋值给SeqList对象
    listd = slist2 + listb;           //执行SortedSeqList的+，返回SortedSeqList实例，赋值给SeqList对象
    slist3 = slist2 + listb;          //执行SortedSeqList的+，返回SortedSeqList实例，赋值给SortedSeqList对象
    cout<<"listc=listb+slist2："<<listc<<"listd=slist2+listb："<<listd<<"slist3=slist2+listb："<<slist3;

    system("pause");
    return 0;
}

/*
//程序运行结果及分析见习题解答2.2。
（1）SortedSeqList子类继承+，程序运行结果如下。
lista(listb)：  (41, 67, 34, 0, 69, 24, 78)
slist1(slist2)：(0, 24, 34, 41, 67, 69, 78)
lista+=slist1： (41, 67, 34, 0, 69, 24, 78, 0, 24, 34, 41, 67, 69, 78) //顺序表
slist1+=listb： (0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78) //排序顺序表
listb+slist2：  (41, 67, 34, 0, 69, 24, 78, 0, 24, 34, 41, 67, 69, 78) //顺序表
slist2+listb：  (0, 24, 34, 41, 67, 69, 78, 41, 67, 34, 0, 69, 24, 78) //排序顺序表，结果错误

以下声明结果同上。
SeqList<T>& SeqList<T>::operator+=(SeqList<T> &list)

（2）SortedSeqList子类覆盖+，程序运行结果如下。
lista(listb)：  (41, 67, 34, 0, 69, 24, 78)
slist1(slist2)：(0, 24, 34, 41, 67, 69, 78)
listc=listb+slist2：(41, 67, 34, 0, 69, 24, 78, 0, 24, 34, 41, 67, 69, 78)
listd=slist2+listb：(0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78)  //排序顺序表，结果正确
slist3=slist2+listb：(0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78) //排序顺序表，结果正确

*/
    
