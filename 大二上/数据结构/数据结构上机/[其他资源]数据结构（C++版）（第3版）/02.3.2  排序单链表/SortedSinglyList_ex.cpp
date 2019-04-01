//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.3.2   单链表
//5.  单链表的浅拷贝与深拷贝
//6.  排序单链表

#include "Array.h"
#include "SortedSinglyList.h"                              //排序单链表类

int main()
{
    const int N=7, SIZE=100; 
    int value[N]={0};
    int value2[N]={0};
    random(value,N,SIZE);                                  //声明在Array.h中
    random(value2,N,SIZE);

    SortedSinglyList<int> slist1(value, N,false);                //默认升序
    SortedSinglyList<int> slist2(slist1), slist3=slist1, slist4;  //slist2(slist1), slist3=slist1执行拷贝构造函数
    slist4=slist1;                                           //默认赋值，不继承基类的=
    cout<<"slist1："<<slist1<<"slist2："<<slist2<<"slist3："<<slist3<<"slist4："<<slist4;
    cout<<"slist1.getCount()="<<slist1.count()<<endl;

    int x = slist1.get(0)-1;                                //支持get(i)
    slist1.insert(x);                                       //子类函数，覆盖基类
    int y = slist1.get(slist1.count()-1);
    slist1.insert(y);
    slist1.remove(value[0]); 
    cout<<"slist1插入"<<x<<"、"<<y<<"，删除"<<value[0]<<endl;
    cout<<"slist1："<<slist1<<"slist2："<<slist2<<"slist3："<<slist3<<"slist4："<<slist4;
//    slist1.set(0,100);                                    //不支持该操作
//    slist1.insert(0,50);                                  //编译错，“SortedSinglyList<T>::insert”: 函数不接受 2 个参数

    SinglyList<int> lista(value2, N),listb(lista);
    lista.insert(0,-1);                                    //基类对象调用基类函数，单链表插入
    lista.insert(50);                                      //基类对象调用基类函数，单链表尾插入
    SinglyList<int> listc(slist2), listd;                  //listb(list2)执行SinglyList<T>拷贝构造函数，由子类对象构造基类对象，参数赋值相容
    listd = slist2;                                        //执行基类的赋值，参数赋值相容
    cout<<"lista："<<lista<<"listb："<<listb<<"listc："<<listc<<"listd："<<listd;

    //==的继承性，继承关系
    cout<<"slist2==listb？"<<(slist2==listb)<<endl;        //子类==基类
    cout<<"listb==slist2？"<<(listb==slist2)<<endl;        //基类==子类
    cout<<"slist2==slist3？"<<(slist2==slist3)<<endl;      //子类==子类

    SortedSinglyList<int> slist5(lista);                 //由基类对象构造子类对象，由单链表构造排序单链表，没有二义性
               //其中执行slist5.insert(50);覆盖，子类对象调用子类函数，排序单链表插入
               //子类覆盖基类同名成员函数，无论参数列表是否相同。编译时多态，也称早期联编。
    cout<<"slist5："<<slist5;

    SortedSinglyList<int> slist6(lista, false);             //由基类对象构造子类对象，降序，由单链表构造排序单链表，没有二义性
    cout<<"slist6："<<slist6;


    //虚函数与运行时覆盖。运行时多态，也称滞后联编。
    lista += slist1;                               //连接，基类+=子类，执行基类函数，参数是子类对象
    cout<<"lista += slist1;\nlista："<<lista;
/*    //一种情况，如果子类继承，没有覆盖，则以下调用语法正确，语义都是连接。mergeWith()可声明为虚函数
    slist2 += listb;                               //连接，子类.mergeWith(基类)，执行基类函数，参数是基类对象
    cout<<"slist2 += listb;\nslist2："<<slist2<<"listb："<<listb;
    slist3.mergeWith(slist4);                              //连接，子类.mergeWith(子类)，执行基类函数，参数是子类对象
    cout<<"slist3.mergeWith(slist4);\nslist3："<<slist3<<"slist4："<<slist4;
*/
    //另一种情况，如果子类声明覆盖，则以下语法，语义多义。
//    slist2.mergeWith(listb);                               //编译错，覆盖，SortedSinglyList<T>::mergeWith 不支持SinglyList<T>类型参数
//    cout<<"slist2.mergeWith(listb);\nslist2："<<slist2;
    slist3 += slist4;                              //归并排序，子类 += 子类，执行子类函数，参数是子类对象。是否虚函数，结果相同
    cout<<"slist3 += slist4;\nslist3："<<slist3<<"slist4："<<slist4;

    system("pause");
    return 0;
}

/*
程序运行结果如下：
slist1：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist2：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist3：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist4：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist1插入40、61，删除41
slist1：(40, 61, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist2：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist3：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist4：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
lista：(-1, 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 50)
listb：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
listc：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
slist5：(-1, 0, 5, 24, 27, 34, 41, 45, 50, 58, 61, 62, 64, 67, 69, 78, 81)
slist2==listb？1
listb==slist2？1
slist2==slist3？1
*p：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 50)
*p：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)                        //insert(T x)没有声明virtual
插入50：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 50)
请按任意键继续. . . 
SinglyList析构(-1, 0, 5, 24, 27, 34, 41, 45, 50, 58, 61, 62, 64, 67, 69, 78, 81)
SinglyList析构(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
SinglyList析构(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
SinglyList析构(-1, 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 50)
SinglyList析构(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
SinglyList析构(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
SinglyList析构(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)
SinglyList析构(40, 61, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61)


*p：(41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 50)
*p：(0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81)                       //insert(T x)声明virtual
插入50：(0, 5, 24, 27, 34, 41, 45, 50, 58, 61, 62, 64, 67, 69, 78, 81)



    //+=、+的继承性，继承关系，子类需要运行时覆盖
    cout<<"lista + slist1："<<(lista.mergeWith(slist1);            //基类+子类，执行基类函数，参数是子类对象
//不行    cout<<"slist2 + listb："<<(slist2 + listb);            //子类+基类，继承，参数是基类对象
//不行    cout<<"slist3 + slist4："<<(slist3 + slist4);          //子类+子类，继承，参数是子类对象

    lista += slist1;                                       //基类+=子类，执行基类函数，参数是子类对象
    cout<<"lista += slist1;\nlista："<<lista;
    slist2 += listb;                                       //子类+=基类，继承，参数是基类对象
    cout<<"slist2 += listb;\nslist2："<<slist2;
    slist3 += slist4;                                      //子类+=子类，继承，参数是子类对象
    cout<<"slist3 += slist4;\nslist3："<<slist3;


*/
//？？单链表插入、删除测试？？


/* 2013年9月19日
slist1：(0, 24, 34, 41, 67, 69, 78)
slist2：(0, 24, 34, 41, 67, 69, 78)
slist3：(0, 24, 34, 41, 67, 69, 78)
slist4：(0, 24, 34, 41, 67, 69, 78)
slist1.getCount()=7
slist1插入-1、78，删除41
slist1：(-1, 0, 24, 34, 67, 69, 78, 78)
slist2：(0, 24, 34, 41, 67, 69, 78)
slist3：(0, 24, 34, 41, 67, 69, 78)
slist4：(0, 24, 34, 41, 67, 69, 78)
lista：(-1, 58, 62, 64, 5, 45, 81, 27, 50)
listb：(58, 62, 64, 5, 45, 81, 27)
listc：(0, 24, 34, 41, 67, 69, 78)
listd：(0, 24, 34, 41, 67, 69, 78)
slist2==listb？0
listb==slist2？0
slist2==slist3？1
请按任意键继续. . . 
slist5：(-1, 5, 27, 45, 50, 58, 62, 64, 81)
slist6：(81, 64, 62, 58, 50, 45, 27, 5, -1)
lista.mergeWith(slist1);
lista：(-1, 58, 62, 64, 5, 45, 81, 27, 50, -1, 0, 24, 34, 67, 69, 78, 78)
slist2.mergeWith(listb);                                   //一种情况，子类继承没有覆盖时，则语法正确，语义都是连接。
slist2：(0, 24, 34, 41, 67, 69, 78, 58, 62, 64, 5, 45, 81, 27)
listb：()
slist3.mergeWith(slist4);
slist3：(0, 24, 34, 41, 67, 69, 78, 0, 24, 34, 41, 67, 69, 78)
slist4：()

slist3.mergeWith(slist4);                                  //另一种情况，子类声明覆盖，则语义多义，归并排序。
slist3：(0, 0, 24, 24, 34, 34, 41, 41, 67, 67, 69, 69, 78, 78)
slist4：()

*/