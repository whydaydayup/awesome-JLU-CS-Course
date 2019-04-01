//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.2 顺序表类

#include <iostream>
using namespace std;
#include <iomanip>                                         //包含
#include <exception>                                       //包含C++ STL（标准类库）异常类

template <class T>
class SeqList                                              //顺序表类，T指定元素类型，T必须重载==和!=关系运算符
{
  protected:                                               //保护成员，子类可见
    T *element;                                            //动态数组存储顺序表的数据元素
    int length;                                            //顺序表的数组容量
    int n;                                                 //顺序表元素个数（长度）

  private:                                                 //私有成员，只在本类可见
    void init(T values[], int n);                          //初始化顺序表，由values数组提供元素，n指定元素个数

  public:                                                  //公有成员，所有类可见
    SeqList(int length=32);                                //构造空表，length指定（默认）容量
    SeqList(int length, T x);                              //构造顺序表，length个元素值为x
    SeqList(T values[], int n);                            //构造顺序表，由values数组提供元素，n指定元素个数
    ~SeqList();                                            //析构函数 

    bool empty();                                          //判断顺序表是否为空
    int count();                                           //返回顺序表元素个数
    T& operator[](int i);                                  //重载下标运算符
    friend ostream& operator<<<>(ostream&, SeqList<T>&);   //输出顺序表所有元素，重载输出流运算符，增加<>，<>省略T，隐式模板参数
    void printPrevious();                                  //反序输出，从后向前

    void insert(int i, T x);                               //插入x作为第i个元素
    virtual void insert(T x);                              //在顺序表最后插入x；虚函数
    T remove(int i);                                       //删除第i（0≤i<n）个元素，返回被删除元素
    void removeAll();                                      //删除顺序表所有元素
    virtual int search(T key, int start=0);                //从start开始顺序查找首次出现的关键字为key元素，返回元素序号；虚函数
    virtual void removeFirst(T key);                       //删除首次出现的关键字为key元素；虚函数；必须First，否则与remove(int)参数相同

    SeqList(SeqList<T> &list);                             //拷贝构造函数
    SeqList<T>& operator=(SeqList<T> &list);               //重载=赋值运算符，深拷贝
    bool operator==(SeqList<T> &list);                     //比较两个顺序表对象的值是否相等
    bool operator!=(SeqList<T> &list);
    void operator+=(SeqList<T> &list);                     //在*this当前顺序表之后合并连接list
//    SeqList<T>& operator+=(SeqList<T> &list);            //两者均可，结果相同
    SeqList<T> operator+(SeqList<T> &list);                //返回*this与list合并连接的对象；不能声明虚函数
    //以上第2章ADT

    //实验2 顺序查找；虚函数
    bool contains(T key);                                  //判断是否包含关键字为key元素
    void removeAll(T key);                                 //删除所有关键字为key元素
    void replaceFirst(T key, T x);                         //将首次出现的关键字为key元素替换为x
    void replaceAll(T key, T x);                           //将所有关键字为key元素替换为x
    virtual int indexLast(T key, int start);               //从start开始顺序查找最后出现的关键字为key元素，返回元素序号；虚函数
};

//1.  顺序表的基本操作及效率分析
//（1） 顺序表的构造和析构
template <class T>
SeqList<T>::SeqList(int length)                            //构造空顺序表，length指定数组容量（默认）
{
    this->element = new T[length];                         //若length<0，则C++将中止运行
    this->length = length;
    this->n = 0;                                           //元素个数为0
}

template <class T>
SeqList<T>::SeqList(int length, T x)                       //构造顺序表，length个元素值为x，构造函数重载。并查集等用
{
    this->element = new T[length];
    this->length = this->n = length;
    for (int i=0; i<this->n; i++)
        this->element[i] = x;                              //执行T的=赋值，T的默认=赋值必需
}

template <class T>
void SeqList<T>::init(T values[], int n)                   //初始化顺序表，由values数组提供元素，n指定元素个数
{
    this->length = n*2;
    this->element = new T[this->length];
    this->n = n;
    for (int i=0; i<n; i++)
        this->element[i] = values[i];                      //执行T的=赋值，T的默认=赋值必需
}

template <class T>
SeqList<T>::SeqList(T values[], int n)                     //构造顺序表，由values数组提供元素，n指定元素个数，构造函数重载
{
    this->init(values, n);
}

template <class T>
SeqList<T>::~SeqList()                                     //析构函数
{
//    cout<<"析构~SeqList"<<*this;
    delete []this->element;                                //释放动态数组element占用的存储空间
}

//（2） 顺序表的判空、求长度和随机访问特性
template <class T>
bool SeqList<T>::empty()                                   //判断顺序表是否为空，若空返回true，O(1)
{
    return this->n==0;
}
template <class T>
int SeqList<T>::count()                                    //返回顺序表元素个数（长度），O(1)
{
    return this->n;
}

//重载下标运算符，引用第i（0≤i<n）个元素。若i<0或i≥n，则抛出异常
template <class T>
T& SeqList<T>::operator[](int i)
{
    if (i>=0 && i<this->n)
        return this->element[i];                           //返回元素引用
    throw out_of_range("参数i指定元素序号超出范围");       //抛出C++ STL范围越界异常
}

//（3） 顺序表的遍历输出
//输出顺序表所有元素，重载<<输出流运算符，形式为“(,)”，空表返回()
//Visual C++ 2008 增加<>，<>省略T，隐式模板参数，T必须重载<<输出流运算符
template <class T>
ostream& operator<<<>(ostream& out, SeqList<T> &list)
{
    out<<"(";
    if (list.n>0)
        out<<list.element[0];
 //   out.width(5);                                        //列宽，后留空
    for (int i=1; i<list.n; i++)
        out<<", "<<list.element[i];              //执行T的<<，T必须重载<<
//        out<<", "<<setw(5)<<list.element[i];              //执行T的<<，T必须重载<<，列宽，前留空
    out<<")"<<endl;
    return out;
}

template <class T>
void SeqList<T>::printPrevious()                           //反序输出，从后向前。Dijkstra、Floyd算法用
{
    cout<<"(";
    if (this->n > 0)
        cout<<this->element[this->n-1];
    for (int i=this->n-2; i>=0; i--)
        cout<<", "<<this->element[i]; 
    cout<<")";
}

//（4） 顺序表的插入操作
//插入x作为第i个元素。若i指定序号越界，采取容错措施，插入在最前或最后。
template <class T>
void SeqList<T>::insert(int i, T x)
{
    if (i<0)                                               //插入位置i容错
        i=0;                                               //插入在最前
    if (i>this->n)
        i=this->n;                                         //插入在最后

    T *temp = this->element;  
    if (this->n==this->length)                             //若数组满，则扩充顺序表的数组容量
    {
        this->length *=2;
        this->element = new T[this->length];               //重新申请一个容量更大的数组
        for (int j=0; j<i; j++)                            //复制当前数组前i-1个元素
            this->element[j] = temp[j];                    //执行T的=赋值运算
    }
    for (int j=this->n-1; j>=i; j--)                       //从i开始至表尾的元素向后移动，次序是从后向前
        this->element[j+1] = temp[j];
    if (temp!=this->element)
        delete[] temp;                                     //释放原数组空间
    this->element[i] = x;
    this->n++;
}

template <class T>
void SeqList<T>::insert(T x)                               //在顺序表最后插入x元素，成员函数重载
{
    this->insert(this->n, x); 
}

//（5） 顺序表的删除操作
//删除第i（0≤i<n）个元素，返回被删除元素；若i<0或i≥n，则抛出异常
template <class T>
T SeqList<T>::remove(int i)
{
    if (this->n>0 && i>=0 && i<n)
    {
        T old = this->element[i];                          //old中存储被删除元素
        for (int j=i; j<n-1; j++)                          //元素前移，平均移动n/2
            this->element[j] = element[j+1];
        this->n--;
        return old;                                        //返回old局部变量存储的对象，先执行拷贝构造函数，再析构old
    }
    throw out_of_range("参数i指定元素序号超出范围");       //抛出C++ STL范围越界异常
}

template <class T>
void SeqList<T>::removeAll()                               //删除顺序表所有元素，未释放数组空间
{
    this->n=0;
}

//（6） 顺序表的查找操作
//从start开始顺序查找首次出现的关键字为key元素，返回元素序号i（0≤i<n），若查找不成功返回-1
//start≥0，默认0；T必须重载==运算符
template <class T>
int SeqList<T>::search(T key, int start)
{
    for (int i=start; i<this->n; i++)
        if (this->element[i]==key)                         //T必须重载==
            return i;
    return -1;
}

template <class T>
void SeqList<T>::removeFirst(T key)                        //删除首次出现的关键字为key元素；虚函数；必须First，否则与remove(int)参数相同
{
    this->remove(this->search(key));                        //查找到，删除，调用remove(i)
}

//【例2.1】使用顺序表求解约瑟夫环问题。
//【例2.2】对象信息分类统计与查找。

//2. 顺序表的浅拷贝与深拷贝
//（1）顺序表的浅拷贝
/*
template <class T>
SeqList<T>::SeqList(SeqList<T> &list)                      //默认拷贝构造函数（浅拷贝）
{
    this->length = list.length;
    this->n = list.n;
    this->element = list.element;                          //指针赋值，只复制了数组首地址，析构时出错
}
template <class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T> &list)        //赋值（浅拷贝）
{
    this->length = list.length;
    this->n = list.n;
    this->element = list.element;                          //指针赋值，只复制了数组首地址，析构时出错
    return *this;
}*/

//（4） 顺序表的深拷贝
template <class T>
SeqList<T>::SeqList(SeqList<T> &list)                      //深拷贝构造函数，复制list
{
    this->init(list.element, list.n);                      //初始化当前对象，由list数组提供元素
}

template <class T>
SeqList<T>& SeqList<T>::operator=(SeqList<T> &list)        //重载=赋值运算符，返回对象引用，深拷贝
{
    if (this->length > list.n)
    {
        this->n = list.n;
        for (int i=0; i<this->n; i++)                      //复制list数组所有元素，O(n)
            this->element[i] = list.element[i];            //执行T的=赋值运算，T默认=赋值必需
        return *this;                                      //返回当前对象引用
    }
    //当前对象的数组容量较小时，扩充数组容量
    this->~SeqList();                                      //调用析构函数，释放element数组空间
    this->init(list.element, list.n);                      //初始化当前对象，由list的数组提供元素
    return *this;                                          //返回当前对象引用
}

//3.  顺序表重载运算符
template <class T>
bool SeqList<T>::operator==(SeqList<T> &list)              //比较两个顺序表是否相等，T必须重载!=运算符，O(n)
{
    if (this==&list || this->element==list.element)        //指针比较，当两个对象引用同一个实例，或顺序表浅拷贝，两个对象引用同一个数组时
        return true;
    if (this->n!=list.n)                                   //比较两者长度是否相等，不比较数组容量
        return false;
    for (int i=0; i<n; i++)                                //比较两个顺序表的所有元素是否相等
        if (this->element[i] != list.element[i])           //T必须重载!=运算符
            return false;
    return true;
}

template <class T>
bool SeqList<T>::operator!=(SeqList<T> &list)              //比较两个顺序表是否不相等
{
    return !(*this==list);
}

//2.2.3   排序顺序表
//10.  虚函数与滞后联编

//在*this当前顺序表之后合并连接list；改变*this对象，不改变list对象。
//参数类型为对象引用，参数传递时不执行拷贝构造函数。
template <class T>
void SeqList<T>::operator+=(SeqList<T> &list)
{ 
    for (int i=0; i<list.n; i++)
        this->insert(list[i]);                             //执行哪个类的insert(x)函数？
} 
//其中，若insert(x)声明为虚函数，运行时覆盖，本类执行尾插入；SortedSeqList子类执行排序插入。
//因此，本函数不需要被子类覆盖，不需要声明为虚函数。

//以下声明可行，结果同上。
/*template <class T>
SeqList<T>& SeqList<T>::operator+=(SeqList<T> &list)
{ 
    for (int i=0; i<list.n; i++)
        this->insert(list[i]);                             //执行哪个类的insert(x)函数？
    return *this;
} */

//教材第49页【思考题2-2】
//返回*this与list合并连接的对象；不改变*this和list对象。
//返回值类型为对象，参数传递时执行拷贝构造函数
template <class T>
SeqList<T> SeqList<T>::operator+(SeqList<T> &list)
{
    SeqList<T> temp(*this);                                //执行拷贝构造函数，复制*this当前对象给temp
    temp += list;
    return temp;                                           //返回temp局部变量存储的对象，先执行拷贝构造函数，再析构temp
}
//存在问题，因temp是基类，+=都执行基类的insert(x)，编译时确定，因此基类可行，子类不行。
//且返回值类型，不能返回给实际参数为子类的调用。？？为什么？？
//解决方法：子类运行时覆盖为归并。或者，需要采用反射机制，根据*this是基类或子类，分别拷贝基类或子类实例。
//以下修改也不行。
/*
template <class T>
SeqList<T> SeqList<T>::operator+(SeqList<T> &list)
{ 
    SeqList<T> *p = new SeqList<T>(*this);                 //仍然执行SeqList拷贝构造函数，无法自动调节
    *p += list;
    return *p;
}*/



//实验2，顺序表基于查找的删除和替换操作
template <class T>
bool SeqList<T>::contains(T key)                           //判断是否包含关键字为key元素
{
    return search(key)>=0;                                 //以查找结果判断是否包含指定元素
} 

template <class T>
void SeqList<T>::removeAll(T key)                          //删除所有关键字为key元素。算法每元素移动多次
{
    int i=0;
    while ((i=this->search(key,i))!=-1)                     //从i开始顺序查找关键字为key元素
        this->remove(i);                                   //查找到，删除，调用remove(i)
}

template <class T>
void SeqList<T>::replaceFirst(T key, T x)                  //将首次出现的关键字为key元素替换为x
{
    int i=this->search(key,0);
    if (i!=-1) 
        this->element[i] = x;                              //查找到，替换
}

template <class T>
void SeqList<T>::replaceAll(T key, T x)                    //将所有关键字为key元素替换为x
{
    int i=-1;
    while ((i=this->search(key,i+1))!=-1)                   //从i+1开始再次查找关键字为key元素
        this->element[i] = x;                               //查找到，替换
}

//从start开始顺序查找关键字为key元素，返回最后出现元素序号，若未找到返回-1，虚函数
template <class T>
int SeqList<T>::indexLast(T key, int start)
{
    for (int i=this->n-1; i>=start; i--)
        if (this->element[i]==key)
            return i;
    return -1;
}

