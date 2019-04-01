//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2.2   顺序表 2. 顺序表的浅拷贝与深拷贝
//2.2.3   排序顺序表 

#include "SortedSeqList.h"                                 //排序顺序表类，包含"Array.h"

int main()
{
    const int N=10, SIZE=100; 
    int values[N]={0};
    random(values,N,SIZE);                                 //声明在Array.h中

    //教材第45页，7.  多态原则，子类覆盖基类同名成员函数
    //编译时多态
    SeqList<int> lista(values, N);
    lista.insert(0, -1);                                   //基类对象调用基类函数，顺序表插入
    lista.insert(50);                                      //基类对象调用基类函数，顺序表尾插入
    cout<<"lista："<<lista;

    SortedSeqList<int> slist1(values, N);
    slist1.insert(50);                                     //子类对象调用子类函数，排序顺序表插入
//    slist1.insert(0, -1);                                //编译错，子类对象不能调用被覆盖的函数，“SortedSeqList<T>::insert”: 函数不接受 2 个参数

    //教材第42～44页，3～6. 子类的拷贝构造函数和默认赋值
    SortedSeqList<int> slist2(slist1), slist3=slist1, slist4;  //slist2(slist1), slist3=slist1执行拷贝构造函数
    slist4=slist1;                                         //默认赋值，不继承基类的=
    cout<<"slist1："<<slist1<<"slist2："<<slist2<<"slist3："<<slist3<<"slist4："<<slist4;

    //教材第46页，9.  类型的多态，子类对象即是基类对象，赋值相容
    SeqList<int> listb(slist1), listc;                     //listb(slist2)执行拷贝构造函数，参数是子类对象，赋值相容
    listc = slist2;                                        //执行基类的赋值，参数赋值相容
    cout<<"listb(slist1)："<<listb<<"listc=slist2 ："<<listc;
 
    //子类对象即是基类对象，反之则不然。
//    SortedSeqList<int> slist5(lista);                      //编译错，拷贝构造函数参数类型不匹配，SortedSeqList类没有声明SeqList参数的拷贝构造函数
    SortedSeqList<int> slist5(lista);                      //由基类对象构造子类对象，由顺序表构造排序顺序表，没有二义性
               //其中执行slist5.insert(50);覆盖，子类对象调用子类函数，排序顺序表插入
               //子类覆盖基类同名成员函数，无论参数列表是否相同。编译时多态，也称早期联编。
    cout<<"slist5："<<slist5;

    //==的继承性，继承关系，子类比较相等规则相同，可用
    cout<<"lista==listb？"<<(lista==listb)<<endl;          //基类==基类
    cout<<"slist1==listb？"<<(slist1==listb)<<endl;        //子类==基类
    cout<<"listc==slist2？"<<(listc==slist2)<<endl;        //基类==子类
    cout<<"slist1==slist2？"<<(slist1==slist2)<<endl;      //子类==子类

    //教材第46页，8.  子类不能删除基类成员
    //继承[]
    int x = slist1[0]-1;                                    //继承[]运算符
    slist1[0]=x;                                             //子类元素应该只读，不能更改，但重载[]做不到只读

    //教材第45页，7.  多态原则，子类覆盖基类同名成员函数
    //继承[]；覆盖查找、插入、删除
    slist1.insert(x);                                       //子类函数，覆盖基类
    int y = slist1[slist1.count()-1];
    slist1.insert(y);
    slist1.removeFirst(values[0]); 
    cout<<"\nslist1插入"<<x<<"、"<<y<<"，删除"<<values[0]<<endl;
    cout<<"slist1："<<slist1<<"slist2："<<slist2<<"slist3："<<slist3<<"slist4："<<slist4;

    //10.  虚函数与滞后联编
    //（2） 运行时多态，滞后联编与虚函数
    //当insert(int)声明为虚函数，以下正确。+=、+可继承
    lista += slist1;                                       //连接，基类.+=(子类)，执行基类函数，参数是子类对象
    cout<<"lista += slist1;\nlista："<<lista;
    slist2 += listb;                                       //排序合并，子类.+=(基类)，执行子类函数，参数是基类对象
    cout<<"slist2 += listb;\nslist2："<<slist2;
    slist3 += slist4;                                      //排序合并，子类.+=(子类)，执行子类函数，参数是子类对象
    cout<<"slist3 += slist4;\nslist3："<<slist3;

//    cout<<"lista + slist1："<<(lista + slist1);            //基类+子类，执行基类函数，参数是子类对象
    //【思考题2-2】+继承，存在错误
//    cout<<"slist2 + listb："<<(slist2 + listb);            //子类+基类，继承，执行基类函数，参数是基类对象，逻辑错
//    cout<<"slist3 + slist4："<<(slist3 + slist4);          //子类+子类，继承，执行基类函数，参数是子类对象，逻辑错

    //子类重定义+，覆盖
//    cout<<"slist2 + listb："<<(slist2 + listb);            //子类+基类，执行子类函数，参数是基类对象
//    cout<<"slist3 + slist4："<<(slist3 + slist4);          //子类+子类，执行子类函数，参数是子类对象

//    slist4.无法调用析构函数。

    system("pause");
    return 0;
}
/*
    //教材第45页，编译时多态，一种运行结果如下：
lista：(-1, 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 50)     //顺序表尾插入50
slist1：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)        //排序顺序表插入50
slist2：(0, 24, 34, 41, 58, 62, 64, 67, 69, 78)            //排序顺序表深拷贝


运行结果如下：
lista：(-1, 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 50)
slist1：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist2：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist3：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist4：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
listb(slist1)：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
listc=slist2 ：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist5：(-1, 0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
lista==listb？0
slist1==listb？1
listc==slist2？1
slist1==slist2？1

slist1插入-1、78，删除41
slist1：(-1, -1, 24, 34, 50, 58, 62, 64, 67, 69, 78, 78)
slist2：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist3：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)
slist4：(0, 24, 34, 41, 50, 58, 62, 64, 67, 69, 78)

//??
lista += slist1;
lista：(-1, 58, 62, 64, 5, 45, 81, 27, 50, -1, -1, 24, 34, 67, 69, 78, 78)
slist2 += listb;
slist2：(0, 5, 24, 27, 34, 41, 45, 58, 62, 64, 67, 69, 78, 81)
slist3 += slist4;
slist3：(0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78)

lista + slist1：(-1, 58, 62, 64, 5, 45, 81, 27, 50, -1, -1, 24, 34, 67, 69, 78, 78)
slist2 + listb：(0, 24, 34, 41, 67, 69, 78, 58, 62, 64, 5, 45, 81, 27)          //【思考题2-2】+继承，存在错误
slist3 + slist4：(0, 24, 34, 41, 67, 69, 78, 0, 24, 34, 41, 67, 69, 78)         //【思考题2-2】+继承，存在错误

    //子类重定义+，覆盖
slist2 + listb：(0, 5, 24, 27, 34, 41, 45, 58, 62, 64, 67, 69, 78, 81)
slist3 + slist4：(0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78)

*/
