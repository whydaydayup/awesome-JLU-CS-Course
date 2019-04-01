//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.2   基于排序顺序表的二分法查找

#include "SortedSeqList.h"                                 //排序顺序表类，包含"Array.h"

int main()
{
    const int N=8, SIZE=100; 
    int values[] ={8,17,26,32,40,72,87,99};                //已按升序排序数组，图8.1
    random(values,N,SIZE);                                 //声明在Array.h中

    SortedSeqList<int> slist1(values, N);
    cout<<"排序顺序表slist1："<<slist1;
//    int keys[]={40,39,99};
    int keys[]={slist1[slist1.count()-1],50,99};
    for (int i=0; i<3; i++)
        cout<<"二分法查找 "<<keys[i]<<"，"<<((slist1.binarySearch(keys[i])==-1)?"不":"")<<"成功\n";

    system("pause");
    return 0;
}
/* 
程序运行结果如下：
排序顺序表slist1：(8, 17, 26, 32, 40, 72, 87, 99)
32? 72? 40? 二分法查找 40，成功
32? 72? 40? 二分法查找 39，不成功
32? 72? 87? 99? 二分法查找 99，成功


排序顺序表slist1：(0, 24, 34, 41, 58, 67, 69, 78)
41? 67? 69? 78? 二分法查找 78，成功
41? 67? 58? 二分法查找 50，不成功
41? 67? 69? 78? 二分法查找 99，不成功

*/

