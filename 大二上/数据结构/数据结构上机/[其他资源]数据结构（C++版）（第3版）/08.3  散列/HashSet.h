//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.4   散列
//采用图8.11所示结构链地址法的散列表类，包括插入、删除、查找、遍历等操作。

#include "SinglyList.h"                                    //单链表类

template <class T>
class HashSet                                              //采用链地址法的散列表类，T必须支持hashCode()返回散列码
{
  private:
    SinglyList<T> *table;                                  //散列表的数组，数组元素是单链表对象
    int length;                                            //散列表的数组容量
    int hash(T key);                                       //散列函数
     
  public:
    HashSet(int length=32);                                //构造指定容量的散列表
    ~HashSet();                                            //析构函数

    void insert(T key);                                    //插入元素key
    void remove(T key);                                    //删除关键字为key元素
    T* search(T key);                                      //查找关键字为key元素
    friend ostream& operator<<<>(ostream& out, HashSet<T> &); //输出散列表中所有元素
};

template <class T>
HashSet<T>::HashSet(int length)                            //构造容量为length的散列表
{
    this->length = length;
    this->table = new SinglyList<T>[length];               //默认执行SinglyList<T>()构造空单链表
}

template <class T>
HashSet<T>::~HashSet()                                     //析构函数
{
    delete[] this->table;                                  //多次执行~SinglyList()单链表析构函数
}

//散列函数，计算关键字为key元素的散列地址。除留余数法，除数是散列表长度
//当T是类时，T必须声明hashCode()返回对象的散列码，约定对象到int的一对一映射
template <class T>
int HashSet<T>::hash(T key)
{    
    return key.hashCode() % this->length;                  //使用key对象的散列码计算
//    return key % this->length;                           //当T是基本类型时
}
  
template <class T>
void HashSet<T>::insert(T key)                             //插入元素key
{
    int i = hash(key);                                     //散列地址
    this->table[i].insertUnrepeatable(key);                //同义词单链表尾插入关键字不重复元素
} 

template <class T>
void HashSet<T>::remove(T key)                             //删除关键字为key元素，若未找到元素，则不删除
{
    this->table[hash(key)].removeFirst(key);               //在同义词单链表中删除关键字为key结点
}

//查找关键字为key元素，若查找成功返回元素地址，否则返回NULL
template <class T>
T* HashSet<T>::search(T key)
{
    Node<T> *find = this->table[hash(key)].search(key);    //在单链表中查找，返回结点
    return (find==NULL) ? NULL : &find->data;
}

template <class T>
ostream& operator<<<>(ostream& out, HashSet<T> &ht)        //输出散列表的各同义词单链表中元素
{
    for(int i=0; i<ht.length; i++)
        out<<"table["<<i<<"]= "<<ht.table[i];              //遍历单链表并输出元素值
    return out;
}

/*
以下声明错误，不能指定存储在顺序表的指定位置。存储位置可能 > 长度
    SeqList<SinglyList<int>> hashtable;                    //散列表，元素是单链表的顺序表
因此，只能用数组。这是数组与顺序表的差别

*/