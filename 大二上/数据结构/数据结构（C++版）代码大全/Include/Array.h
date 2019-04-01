//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例1.3】随机数序列。
//【例9.1】调用排序算法。

#include <iostream>
using namespace std;
#include <stdlib.h>                                        //包含随机数函数rand()


//【例1.3】随机数序列。
//将产生的n个随机数（范围是0～size-1）存放于value数组前n个元素
void random(int value[], int n, int size)
{
    for (int i=0; i<n; i++)
        value[i] = rand() % size;                          //产生一个0～size-1之间的随机数
}

template <class T>
void print(T value[], int n)                               //输出value数组的前n个元素
{
    for (int i=0; i<n; i++)
        cout<<value[i]<<"  ";                              //T必须重载<<输出流运算符
    cout<<endl;
}


//第3版习题解答 习1.2
//判断数组元素是否已按升序排序，若已排序返回true，否则返回false。T必须重载>运算符
template <class T>
bool isSorted(T value[], int n)
{
    for (int i=0; i<n; i++)
        if (value[i]>value[i+1])
            return false;
    return true;
}


//【例9.1】调用排序算法。
//第3版第9章 排序
//9.2.1 直接插入排序
//直接插入排序（升序），将keys数组元素按升序重新排列，n指定数组元素个数，T必须重载<
template <class T>
void insertSort(T keys[], int n) 
{
    for (int i=1; i<n; i++)                                //n-1趟扫描，依次插入n-1个数
    {
        T temp = keys[i];                                  //每趟将keys[i]插入到前面的排序子序列中
        int j;
        for (j=i-1; j>=0 && temp<keys[j]; j--)             //将前面较大元素向后移动，T必须重载<
             keys[j+1] = keys[j];
        keys[j+1] = temp;                                  //temp到达插入位置
        cout<<"第"<<i<<"趟  temp="<<temp<<"\t  ";
        print(keys, n);                                    //输出数组元素，声明在Array.h，可省略
    }
    cout<<endl;
}

//9.2.2   希尔排序
template <class T>
void shellSort(T keys[], int n)                            //希尔排序（升序），T必须重载<
{
    for (int delta=n/2; delta>0; delta/=2)                 //若干趟，控制增量每趟减半
    {
        for (int i=delta; i<n; i++)                        //一趟分若干组，每组直接插入排序
        {
            T temp = keys[i];                              //keys[i]是当前待插入元素
            int j; 
            for (j=i-delta; j>=0 && temp<keys[j]; j-=delta)//组内直接插入排序
                keys[j+delta] = keys[j];                   //每组元素相距delta远
            keys[j+delta] = temp;                          //插入元素
        }
        cout<<"delta="<<delta<<"  ";
        print(keys,n);
    }
    cout<<endl;
}

//9.3.1   冒泡排序
//？？ prim 
template <class T>
void swap(T keys[], int i, int j)       //交换keys[i]与keys[j]数组元素，i、j范围由调用者控制
{ 
    T temp = keys[j];
    keys[j] = keys[i];
    keys[i] = temp;
}

template <class T>
void bubbleSort(T keys[], int n)                           //冒泡排序（升序），T必须重载>
{
    bool exchange=true;                                    //是否交换的标记
    for (int i=1; i<n && exchange; i++)                    //有交换时再进行下一趟，最多n-1趟
    {
        exchange=false;                                    //假定元素未交换 
        for (int j=0; j<n-i; j++)                          //一趟比较、交换
            if (keys[j]>keys[j+1])                         //相邻元素比较，若反序，则交换
            {   swap(keys, j, j+1); 
                exchange=true;                             //有交换 
            }
        cout<<"第"<<i<<"趟  ";
        print(keys,n);
    }
    cout<<endl;
}

//9.3.2   快速排序
template <class T>
void quickSort(T keys[], int n)                           //快速排序（升序），T必须重载<=
{
    quickSort(keys, n, 0, n-1);
}

//对存于keys数组begin～end之间的子序列进行一趟快速排序，递归算法
template <class T>
void quickSort(T keys[], int n, int begin, int end)
{ 
    if (begin>=0 && begin<n && end>=0 && end<n && begin<end)   //序列有效
    {
        int i=begin, j=end;                                //i、j下标分别从子序列的前后两端开
        T vot=keys[i];                                     //子序列第一个值作为基准值
        while (i!=j)
        {
            while (i<j && vot<=keys[j])                    //从后向前寻找较小值，不移动与基准值相等元素
                j--;
            if (i<j)
                keys[i++]=keys[j];                         //子序列后端较小元素向前移动

            while (i<j && keys[i]<=vot)                    //从前向后寻找较大值，不移动与基准值相等元素
                i++;
            if (i<j)
                keys[j--]=keys[i];                        //子序列前端较大元素向后移动
        }
        keys[i]=vot;                                      //基准值的最终位置
        cout<<begin<<".."<<end<<", vot="<<vot<<",  ";
        print(keys, n);
        quickSort(keys, n, begin, j-1);                   //前端子序列再排序，递归调用
        quickSort(keys, n, i+1, end);                     //后端子序列再排序，递归调用
    }
}

//9.4.1 直接选择排序
//min 求最小值？？
template <class T>
void selectSort(T keys[], int n)                           //直接选择排序（升序），T必须重载<
{
    for (int i=0; i<n-1; i++)                              //n-1趟，每趟在从keys[i]开始的子序列中寻找最小元素
    {
        int min=i; 
        for (int j=i+1; j<n; j++)                          //在子序列中查找最小值，min记住本趟最小元素下标
            if (keys[j]<keys[min])
                min = j;
              
        if (min!=i)                                        //将本趟最小元素交换到前边
            swap(keys, i, min);
        cout<<"第"<<i+1<<"趟  min="<<min<<"，\t";
        print(keys, n);
    }
    cout<<endl;
}

//9.4.2 堆排序
//将keys数组中以begin为根的子树调整成最小堆，子序列范围为begin～end，T必须重载>
template <class T>
void sift_minheap(T keys[], int n, int begin, int end)
{
    int parent=begin, child=2*parent+1;                    //parent是子树的根，child是parent的左孩子
    T value = keys[parent];
    while (child<=end)                                     //沿较小值孩子结点向下筛选
    {
        if (child<end && keys[child]>keys[child+1])        //child记住孩子值较小者（改成<为最大堆）
            child++;
        if (value>keys[child])                             //若父母结点值较大（改成<为最大堆）
        {   keys[parent] = keys[child];                    //将较小孩子结点值上移
            parent = child;                                //向下一层
            child = 2*parent+1;
        }
        else break; 
    }
    keys[parent] = value;                                  //当前子树的原根值调整后的位置
    cout<<"sift  "<<begin<<".."<<end<<"  ";
    print(keys, n);
}

template <class T>
void heapSort_down(T keys[], int n)                        //堆排序（降序），最小堆，T必须重载>
{
    cout<<"建立最小堆序列"<<endl;
    for (int i=n/2-1; i>=0; i--)                           //创建最小堆，根结点值最小
        sift_minheap(keys, n, i, n-1);
        
    cout<<"堆排序（降序）"<<endl;
    for (int i=n-1; i>0; i--)                              //每趟将最小值交换到后面，再调整成最小堆
    {
        swap(keys, 0, i);
        sift_minheap(keys, n, 0, i-1);
    }
    cout<<endl;
}

//9.5 归并排序
//一次归并，将X中分别以begin1、begin2开始的两个相邻子序列归并到Y中，X、Y数组长度为len，子序列长度最长为n
//T必须重载<
template <class T>
void merge(T X[], int len, T Y[], int begin1, int begin2, int n)
{
    int i=begin1, j=begin2, k=begin1;
    while (i<begin1+n && j<begin2+n && j<len)              //将X中两个相邻子序列归并到Y
        if (X[i] < X[j])                                   //将较小值复制到Y中
            Y[k++]=X[i++];
        else
            Y[k++]=X[j++];

    while (i<begin1+n && i<len)                            //将前一个子序列剩余元素复制到Y中，子序列长度可能不足n
        Y[k++]=X[i++];
    while (j<begin2+n && j<len)                            //将后一个子序列剩余元素复制到Y中
        Y[k++]=X[j++];
}

template <class T>
void mergepass(T X[], int len, T Y[], int n)               //一趟归并，子序列长度为n
{
    cout<<"子序列长度n="<<n<<"  ";
    for (int i=0;  i<len;  i+=2*n)                         //X中若干相邻子序列归并到Y中
        merge(X, len, Y, i, i+n, n);                       //将X中两个相邻子序列一次归并到Y数组中
    print(Y, len);
}

template <class T>
void mergeSort(T X[], int len)                             //归并排序，X数组长度为len。T必须重载<
{
    T *Y = new T[len];                                     //Y数组长度同X数组
    int n=1;                                               //排序子序列长度
    while (n<len)
    {
        mergepass(X, len, Y, n);                           //一趟归并，将X数组中各子序列归并到Y中
        n*=2;                                              //子序列长度加倍
        if (n<len)
        {
            mergepass(Y, len, X, n);                       //将Y数组中各子序列再归并到X中
            n*=2;
        }
    }
    cout<<endl;
}
    