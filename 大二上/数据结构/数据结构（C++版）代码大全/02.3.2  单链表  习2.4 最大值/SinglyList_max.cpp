//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习2.4】求单链表元素的最大值。
//建立反序单链表。

#include "Array.h"                                         //对数组的操作，见教材例1.3
#include "SeqList.h"                                       //顺序表类
#include "SinglyList.h"                                    //单链表类

template <class T>
T max(SeqList<T> &list)                                    //返回顺序表list元素的最大值，T必须重载>运算符
{
    T maxValue = list[0];                                  //maxValue记住当前最大值，执行T的=
    for (int i=1; i<list.count(); i++)
        if (list[i] > maxValue)                            //T必须重载>运算符
            maxValue = list[i];                            //执行T的=
    return maxValue;                                       //执行T的拷贝构造函数
}  
/*
//调用list.get(i)函数，可行，效率低
template <class T>
T max(SinglyList<T> &list)                                 //返回单链表list元素的最大值，T必须重载>运算符
{
    if (list.empty())
        throw invalid_argument("单链表为空，不能计算。");  //抛出无效参数
    T maxvalue = list.get(0);                              //获得单链表第0个元素
    for (int i=1; i<list.count(); i++)
        if (list.get(i) > maxvalue)                        //T必须重载>运算符
            maxvalue = list.get(i);                        //执行T的=
    return maxvalue;                                       //执行T的拷贝构造函数
}
*/

/*//遍历单链表，效率提高，时间复杂度是O(n)。
//要求具有list单链表的head成员变量的访问权限。且算法与单链表的存储结构有关，单链表带与不带头结点，算法实现不同。
template <class T>
T max(SinglyList<T> &list)                                 //返回单链表list元素的最大值，T必须重载>运算符
{
    if (list.empty())
        throw invalid_argument("单链表为空，不能计算。");  //抛出无效参数
    T maxvalue = list.head->next->data;                    //要求单链表head成员变量的访问权限声明为public
    for (Node<T> *p=list.head->next->next;  p!=NULL;  p=p->next)
        if (p->data > maxvalue)
            maxvalue = p->data;
    return maxvalue;                                       //执行T的拷贝构造函数
}*/

//以迭代方式遍历单链表，效率提高，时间复杂度是O(n)。
//可以不具有list单链表的head成员变量的访问权限。且与单链表的存储结构无关，带与不带头结点，算法相同。
template <class T>
T max(SinglyList<T> &list)                                 //返回list单链表的最大值，T必须重载>运算符
{
    Node<int> *p=list.first();                             //获得单链表第0个元素，O(1)
    int maxvalue=p->data;
    while (p!=NULL)
    {
        if (p->data > maxvalue)
            maxvalue = p->data;
        p=list.next(p);                                    //获得p结点的后继结点，O(1)
    }
    return maxvalue;
}

template <class T>
void create(SinglyList<T> &list, T value[], int n)         //由指定数组提供元素创建反序单链表
{
    for (int i=0; i<n; i++)
        list.head->next = new Node<T>(value[i], list.head->next);
}

int main()
{
    const int N=10, SIZE=100;
    int value[N]={0};
    random(value,N,SIZE);                                  //生成随机数序列，声明在Array.h中

//    SeqList<int> lista(value, N); 
//    cout<<"顺序表lista："<<lista<<"最大值："<<max(lista)<<endl;

    SinglyList<int> lista;
//    int value[N]={10,9,8,7,6,5,4,3,2,1};
    create(lista, value, N); 
    cout<<"单链表lista："<<lista<<"最大值："<<max(lista)<<endl;


    system("pause");
    return 0;
}
/*
程序运行结果如下：
单链表lista：(64, 62, 58, 78, 24, 69, 0, 34, 67, 41)
最大值：78

*/
