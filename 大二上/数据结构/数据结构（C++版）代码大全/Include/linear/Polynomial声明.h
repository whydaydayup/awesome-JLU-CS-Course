//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.4   线性表的应用：多项式的表示及运算
//2.4.1   一元多项式的表示及运算

#include "SortedSinglyList.h"                            //排序单链表

//多项式类，继承排序单链表类，提供多项式相加含义的两条排序单链表的合并运算（+=、+）
//T必须重载+=运算符 
template <class T>
class Polynomial : public SortedSinglyList<T> 
{
  public:
    Polynomial(){}                                    //构造函数，自动执行基类构造函数SortedSinglyList<T>()
    Polynomial(T terms[], int n):SortedSinglyList(terms, n){}
                                                      //构造函数，由项数组指定多项式各项值，声明调用基类构造函数SortedSinglyList<T>(T[], int)
    void print();                                     //输出多项式
    void operator+=(Polynomial<T> &poly);             //*this与poly多项式相加，两条单链表相加合并
    Polynomial<T> operator+(Polynomial<T> &poly);     //返回*this与poly相加后的多项式
};
