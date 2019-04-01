//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2.3 排序顺序表（升序）。

#include "SeqList.h"                                       //顺序表类
#include "Array.h"                                         //数组排序，第9章

//排序顺序表类（升序），公有继承顺序表类，T必须重载==、!=、>、>=关系运算符
template <class T>
class SortedSeqList : public SeqList<T>
{
  public:
    SortedSeqList(){}                                      //构造空排序顺序表，默认执行SeqList<T>()
    SortedSeqList(T values[], int n);                      //构造排序顺序表，由values排序数组提供元素
//    SortedSeqList(T values[], int n):SeqList<T>(values, n){}   //构造排序顺序表，由values排序数组提供元素，只例8.1用
    SortedSeqList(SortedSeqList<T> &list):SeqList<T>(list){}//默认拷贝构造函数，参数类型赋值相容，可省略
    SortedSeqList(SeqList<T> &list);                       //重载拷贝构造函数，由顺序表构造排序顺序表
//    SortedSeqList<T>& operator=(SortedSeqList<T> &list);   //默认赋值，不继承基类的=，可省略
//    ~SortedSeqList(){}                                     //不能继承基类析构函数，自动执行~SeqList<T>()，可省略

    void insert(T x);                                      //插入，根据元素x大小确定插入位置；运行时覆盖
    int search(T key, int start=0);                         //从start开始查找关键字为key元素；运行时覆盖
    void removeFirst(T key);                               //删除首次出现的关键字为key元素；运行时覆盖
//    void set(int i, T x);                                  //不支持该操作，抛出异常；运行时覆盖
    void insertUnrepeatable(T x);                          //插入不重复元素
    
    //【思考题2-2】
    SortedSeqList<T> operator+(SeqList<T> &list);
//    SortedSeqList<T> operator+(SortedSeqList<T> &list);

    //实验2

    //8.2  基于排序顺序表的二分法查找
    int binarySearch(T key);
    int binarySearch(T key, int begin, int end);

};

//3.  子类不能继承基类的构造函数
//构造排序顺序表，声明执行基类的SeqList<T>(int)构造函数，直接插入排序算法
template <class T>
SortedSeqList<T>::SortedSeqList(T values[], int n): SeqList<T>(n*2)
{
    for (int i=0; i<n; i++)
        this->insert(values[i]);                            //调用本类成员函数，排序插入
}

//7.  多态原则，子类覆盖基类同名成员函数
//从start开始顺序查找首次出现的关键字为key元素，返回元素序号i（0≤i<n），若查找不成功返回-1。
//start≥0，默认0。覆盖基类的同名成员函数，参数列表相同，返回值相同。
//T必须重载==关系运算符，用于查找时识别对象；T必须重载>=，约定对象排序规则。
template <class T>
int SortedSeqList<T>::search(T key, int start)
{
    for (int i=0; i<this->n && key>=this->element[i]; i++)  //T必须重载>=
        if (this->element[i]==key)                          //T必须重载==
            return i;
    return -1;
}

//插入，根据x元素大小顺序查找x确定插入位置。插入在等值结点之前，T必须重载>运算符
//覆盖了基类的insert(int i, T x)和insert(T x)函数，无论参数列表是否相同，返回值相同
template <class T>
void SortedSeqList<T>::insert(T x)
{
    int i=0;
    while (i<this->n && x > this->element[i])              //T必须重载>
        i++;
    SeqList<T>::insert(i, x);                              //插入x作为第i个元素，调用被覆盖的基类成员函数
}

//删除首次出现的关键字为key元素。覆盖基类的removeFirst(T key)函数，参数列表相同，返回值相同。
//没有覆盖基类的remove(int i)函数。
//算法要先调用search(key)函数，查找确定删除元素位置，因此，要求T必须重载==和>=。
template <class T>
void SortedSeqList<T>::removeFirst(T key)
{
    remove(this->search(key));                              //调用函数remove(i)
//    this->~SeqList(); //编译错：'SortedSeqList<T>' : 类没有 析构函数，其名称为 '~SeqList'。证明，析构不继承？？
//    SortedSeqList<T>::~SortedSeqList();          //没有声明,也能调用，证明有默认析构
}

//8.  子类不能删除基类成员
/*
template <class T>
void SortedSeqList<T>::set(int i, T x)                     //不支持该操作，抛出异常；运行时覆盖
{
    throw logic_error("不支持set(int i, T x)操作");        //抛出C++ STL逻辑错误异常
}*/

//9.  类型的多态，子类对象即是基类对象，赋值相容
//正确
template <class T>
SortedSeqList<T>::SortedSeqList(SeqList<T> &list)          //重载拷贝构造函数，由顺序表构造排序顺序表
{                                                          //此处自动执行SeqList<T>()基类构造函数
    for (int i=0; i<list.count(); i++) 
        this->insert(list[i]);                             //排序顺序表插入元素
}
//与以下声明的二义性问题：
//SortedSeqList<T>::SortedSeqList(SortedSeqList<T> &list)  //深拷贝构造函数，由顺序表构造排序顺序表

//教材第49页【思考题2-2】答案，【习2.2】
//返回两个排序顺序表*this与list归并后的对象；不改变*this和list对象。
//返回值类型为对象，参数传递时执行拷贝构造函数
//覆盖，参数列表相同，返回值类型不同
//算法同SeqList类，只是temp类型不同
template <class T>
SortedSeqList<T> SortedSeqList<T>::operator+(SeqList<T> &list)
{
    SortedSeqList<T> temp(*this);
    temp += list;                                          //执行SortedSeqList继承的+=，排序顺序表插入
    return temp;
}


//9.5   归并排序
//归并两条排序顺序表，重载+运算符，返回*this+list对象，不改变*this和list对象
//一趟归并排序算法，不调用+=，？？
/*template <class T>
SortedSeqList<T> SortedSeqList<T>::operator+(SortedSeqList<T> &list)
{
    SortedSeqList<T> temp(*this);                                //执行拷贝构造函数，复制*this当前对象给temp
    temp += list;
    return temp;                                           //返回temp局部变量存储的对象，先执行拷贝构造函数，再析构temp
}*/
//上述二义性？？


//8.2  基于排序顺序表的二分法查找
//在排序顺序表（升序）中，二分法查找关键字为key元素，若找到返回下标，否则返回-1
//T必须重载==和<运算符
template <class T>
int SortedSeqList<T>::binarySearch(T key)
{
    return binarySearch(key, 0, this->count()-1);
}
//在排序顺序表（升序）从begin～end范围内，二分法查找关键字为key元素
template <class T>
int SortedSeqList<T>::binarySearch(T key, int begin, int end)
{
    while (begin<=end)                                     //边界有效
    {
        int mid = (begin+end)/2;                           //中间位置，当前比较元素位置
        cout<<this->element[mid]<<"? ";                    //显示比较中间结果，可省略
        if (element[mid]==key)                             //比较对象相等，T必须重载==
            return mid;                                    //查找成功，返回元素下标
        if (key < element[mid])                            //比较对象大小，T必须重载<
            end = mid-1;                                   //key值小，查找范围缩小到前半段
        else begin = mid+1;                                //否则，查找范围缩小到后半段
    }
    return -1;                                             //查找不成功
}  

//第3版第9章 排序
//【例9.2】排序顺序表调用排序算法。
//（1）类中以下成员函数声明语法错误 : 应输入“{”而不是“;”
//    SortedSeqList(SeqList<T> &list):SeqList<T>(list);        //重载拷贝构造函数，由顺序表构造排序顺序表，第9章

//（2）正确
//重载拷贝构造函数，由顺序表构造排序顺序表，声明调用基类拷贝构造函数，再调用一种排序算法
/*template <class T>
SortedSeqList<T>::SortedSeqList(SeqList<T> &list):SeqList<T>(list)
{
    shellSort(this->element, this->n);                 //希尔排序（升序）
}
*/
