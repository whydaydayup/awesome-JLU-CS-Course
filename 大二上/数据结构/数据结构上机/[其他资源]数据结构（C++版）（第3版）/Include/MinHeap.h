//10.1.3   贪心法
//最小堆类
#include "SeqList.h"                                       //顺序表类（第2章）
#include "Comparator.h"                                    //比较器抽象类 

template <class T>
class MinHeap                                              //最小堆类，T必须重载>运算符
{
  private:
    SeqList<T> list;                                       //使用顺序表存储最小堆元素
    Comparator<T> *comp;                                   //比较器对象指针 

    void sift(int parent);                                 //将以parent为根的子树调整成最小堆
    
  public:
    MinHeap(Comparator<T> *comp=NULL)                      //构造空最小堆，comp指定比较器对象指针
    {                                                      //此处执行SeqList<T>()，顺序表容量为默认值
        this->comp = comp;
    }
    MinHeap(T value[], int n, Comparator<T> *comp=NULL)    //构造最小堆，value数组提供元素
    {                                                      //此处自动执行SeqList<T>()
        this->comp = comp;
        for (int i=0; i<n; i++)
            this->insert(value[i]);                        //数组元素插入最小堆
    }
    ~MinHeap(){}                                           //析构函数，自动执行~SeqList<T>()，可省略

    bool empty()                                           //判断是否空堆
    {   
        return this->list.empty();
    }
    int count()                                            //返回最小堆元素个数
    {
        return this->list.count();
    }
    friend ostream& operator<<(ostream& out, MinHeap<T> &heap)//输出最小堆，形式为“(,)”
    {
        out<<heap.list;
        return out;
    }
    void insert(T x);                                      //将x插入到最小堆中
    T removeMin();                                         //返回最小值，删除根结点并调整为最小堆
};


template <class T>
void MinHeap<T>::insert(T x)                               //将x插入到最小堆中
{
    this->list.insert(x);                                  //在最小堆最后插入元素，顺序表尾插入元素，顺序表自动计数和扩容
    for (int i=this->count()/2-1; i>=0; i=(i-1)/2)         //自下而上调整各子二叉树为最小堆
    {
        sift(i);        
        if(i==0)
            break;
    }
//    cout<<*this;
}

//将以parent为根的子树调整成最小堆，T必须重载>
template <class T>
void MinHeap<T>::sift(int parent)
{
    if (this->empty())
        return;

    int child = 2*parent+1;                                //child为子树根parent结点的左孩子
    T key = this->list[parent];                            //获得第parent个元素的值
    while (child < this->count())                          //沿较小值孩子结点向下筛选
    {
        if (child<this->count()-1)
        {
            T left=list[child], right=list[child+1];       //左右孩子结点值
            if (comp!=NULL ? comp->compare(left, right)>0 : left>right)
                  //若comp指针不空，由*comp比较器对象比较T对象大小；否则执行T的>运算
            child++;                                       //child为左右孩子的较小者
        }
        if (comp!=NULL ? comp->compare(key, list[child])>0 : key>list[child])
        {                                                  //若父母结点值较大
            list[parent] = list[child];                    //孩子结点中的较小值上移
            parent = child;                                //parent、child向下一层
            child = 2*parent+1;
        }
        else break;
    }
    this->list[parent] = key;                              //当前子树的原根值调整后的位置
}

template <class T>
T MinHeap<T>::removeMin()                                  //返回最小值元素（根），删除根结点并调整为最小堆
{
     if (this->empty())
        return NULL;
     T x = this->list[0];                                  //获得最小堆根结点元素
     list[0] = list[this->count()-1];                      //将最后位置元素移到根，即删除根
     this->list.remove(this->count()-1);                   //顺序表尾删除，长度自动减1
     sift(0);                                              //调整根值下沉到最小堆的合适位置
     return x;
}
