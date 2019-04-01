//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2.2   顺序表
//2. 顺序表的浅拷贝与深拷贝
//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.1】  顺序表的浅拷贝与深拷贝。

#include "SeqList.h"                                        //顺序表类

//输出顺序表所有元素，仅当T是指针类型，形式为“(,)”，空表返回()
template <class T>
void print(SeqList<T> &list)
{
    cout<<"(";
    int n=list.count();
    if (n>0)
        cout<<*list[0];
    for (int i=1; i<n; i++)
        cout<<", "<<*list[i];
    cout<<")"<<endl;
}

int main()
{
    //教材第39～40页
    //（5） 模板参数T的实际参数必须支持深拷贝
    int values[5]={1,2,3,4,5};   
    SeqList<int*> lista;                                   //SeqList元素类型是int*
    for (int i=0; i<5; i++)
        lista.insert(i, &values[i]);                       //插入数组元素地址
    cout<<"lista："<<lista;
    print(lista);                                          //顺序表存储结构见教材图2.8（a）

    SeqList<int*> listb(lista);                            //执行深拷贝构造函数
    cout<<"listb："<<listb;
    print(listb);                                          //顺序表深拷贝后的存储结构见教材图2.8（a）

    int *p = lista[0];
    *p=9;                                                  //修改lista元素，对listb有影响
    int x=6;
    lista.insert(&x);                                      //执行插入、删除操作，对其他list没有影响
//    listb.remove(3);                                     //删除元素，没有释放元素所占存储单元
    cout<<"\nlista[0]=9，lista尾插入"<<x<<"，listb删除元素"<<*listb.remove(3)<<"、"<<*listb.remove(4)<<endl;
    cout<<"lista："; print(lista);
    cout<<"listb："; print(listb);                         //顺序表存储结构见教材图2.8（b）

    system("pause");
    return 0;
}
/*
程序运行结果如下：
lista：(0029F874, 0029F878, 0029F87C, 0029F880, 0029F884)
(1, 2, 3, 4, 5)
listb：(0029F874, 0029F878, 0029F87C, 0029F880, 0029F884)
(1, 2, 3, 4, 5)

lista[0]=9，lista尾插入6，listb删除元素4、5
lista：(9, 2, 3, 4, 5, 6)
listb：(9, 2, 3)

*/