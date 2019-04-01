//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//8.2   基于排序顺序表的二分法查找
//【习8.1】  二分法查找的递归算法。

#include "Array.h"
#include "BinarySearch.h"

int main()
{
    const int N=10, SIZE=100;
    int values[N]={0};
    random(values, N, SIZE);                               //产生N个0～size-1之间的随机数，声明在Array.h中
    insertSort(values, N);                                 //直接插入排序（升序），算法见9.1节。
    cout<<"排序随机数序列：";
    print(values, N);                                      //声明在Array.h中

    int keys[]={values[N/2],10,99};
    for (int i=0; i<3; i++)
        cout<<"二分法查找 "<<keys[i]<<"，"<<((binarySearch(values, N, keys[i])==-1)?"不":"")<<"成功\n";

    system("pause");
    return 0;
}

/* 
程序运行结果如下：
排序随机数序列：0  24  34  41  58  62  64  67  69  78  
58? 67? 62? 二分法查找 62，成功
58? 24? 0? 二分法查找 10，不成功
58? 67? 69? 78? 二分法查找 99，不成功

*/

