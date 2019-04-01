//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2.2   顺序表
//2. 顺序表的浅拷贝与深拷贝
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.1】  顺序表的浅拷贝与深拷贝。

#include "SeqList.h"                                        //顺序表类

int main()
{
    //教材第37～38页
    //（2） 何时执行拷贝构造函数和赋值运算
    //① 当声明对象时，构造函数的参数是该类对象或赋值。例如：
    int values[5]={1,2,3,4,5};   
    SeqList<int> lista(values,5), listd(5);                //执行指定参数列表的构造函数
    SeqList<int> listb(lista), listc=lista;                //声明时两者都执行拷贝构造函数
    listd=lista;                                           //赋值时执行=赋值运算
    cout<<"lista："<<lista<<"listb："<<listb<<"listc："<<listc<<"listd："<<listd<<endl;
                   //顺序表浅拷贝的存储结构见教材图2.6（a）；顺序表深拷贝的存储结构见教材图2.7

    //（3） 顺序表浅拷贝存在问题
    //（4） 顺序表的深拷贝
    lista.remove(0); 
    cout<<"lista.remove(0)\nlista："<<lista<<"listb："<<listb<<endl;  //顺序表浅拷贝的存储结构见教材图2.6（b）

    //课件思考题第62、64页
    int i=listb.count()-1;
    listb[i]=99;
    listb.insert(-1,-1);
    cout<<"listb["<<i<<"]=99，listb.insert(-1,-1)，"<<"lista.remove(1)="<<lista.remove(1)<<endl;
    cout<<"lista："<<lista<<"listb："<<listb<<"listc："<<listc<<"listd："<<listd<<endl;

    system("pause");
    return 0;
}
/*
程序运行结果如下：
//（2） 何时执行拷贝构造函数和赋值运算
① 执行浅拷贝构造函数，程序运行结果如下，结果有运行错误。
lista：(1, 2, 3, 4, 5)
listb：(1, 2, 3, 4, 5)
listc：(1, 2, 3, 4, 5)
listd：(1, 2, 3, 4, 5)

lista.remove(0)
lista：(2, 3, 4, 5)
listb：(2, 3, 4, 5, 5)

listb[4]=99，listb.insert(-1,-1)，lista.remove(1)=2
lista：(-1, 3, 4)
listb：(-1, 3, 4, 4, 5, 99)
listc：(-1, 3, 4, 4, 5)
listd：(-1, 3, 4, 4, 5)
请按任意键继续. . . 
析构~SeqList(-1, 3, 4, 4, 5)
析构~SeqList(-572662307, -572662307, -572662307, -572662307, -572662307, -572662307)
                          //此处显示运行错误对话框，表示执行析构函数时出现运行错


② 执行深拷贝构造函数，程序运行结果如下，析构释放动态数组。结果正确。
析构~SeqList()
lista：(1, 2, 3, 4, 5)
listb：(1, 2, 3, 4, 5)
listc：(1, 2, 3, 4, 5)
listd：(1, 2, 3, 4, 5)

lista.remove(0)
lista：(2, 3, 4, 5)
listb：(1, 2, 3, 4, 5)

listb[4]=99，listb.insert(-1,-1)，lista.remove(1)=3
lista：(2, 4, 5)
listb：(-1, 1, 2, 3, 4, 99)
listc：(1, 2, 3, 4, 5)
listd：(1, 2, 3, 4, 5)
请按任意键继续. . . 
析构~SeqList(1, 2, 3, 4, 5)
析构~SeqList(-1, 1, 2, 3, 4, 99)
析构~SeqList(1, 2, 3, 4, 5)
析构~SeqList(2, 4, 5)


*/