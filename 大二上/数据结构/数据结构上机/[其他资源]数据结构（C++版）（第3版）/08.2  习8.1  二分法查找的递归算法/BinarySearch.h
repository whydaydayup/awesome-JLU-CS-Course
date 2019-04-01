////《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//8.2   基于排序顺序表的二分法查找
//【习8.1】  二分法查找的递归算法。
//以数组存储

//在按升序排列的value数组的前n个元素中，二分法查找关键字为key元素，若找到返回下标，否则返回-1
template <class T>
int binarySearch(T value[], int n, T key)
{
    return binarySearch(value, 0, n-1, key);
}  

//二分法查找递归算法，在从begin到end范围内、按升序排列的value数组中，二分法查找关键字为key的元素
template <class T>
int binarySearch(T value[], int begin, int end, T key)
{
    if (begin<=end)                                         //边界有效
    {
        int mid = (begin+end)/2;                            //中间位置，当前比较元素位置
        cout<<value[mid]<<"? ";
        if (value[mid]==key)                                //比较对象相等，T必须重载==
            return mid;                                     //查找成功，返回元素下标
        if (key < value[mid])                               //key值小，查找范围缩小到前半段
            return binarySearch(value, begin, mid-1, key);  //递归调用
        return binarySearch(value, mid+1, end, key);        //否则，查找范围缩小到后半段，递归调用
    }
    return -1;
}

/*非递归算法，同排序顺序表
//在从begin到end范围内、按升序排列的value数组中，二分法查找关键字为key的元素
template <class T>
int binarySearch(T value[], int begin, int end, T key)
{
    while (begin<=end)                                     //边界有效
    {
        int mid = (begin+end)/2;                           //中间位置，当前比较元素位置
        cout<<value[mid]<<"? ";                            //显示比较中间结果，可省略
        if (value[mid]==key)                               //比较对象相等，T必须重载==
            return mid;                                    //查找成功，返回元素下标
        if (key < value[mid])                              //比较对象大小，T必须重载<
            end = mid-1;                                   //key值小，查找范围缩小到前半段
        else begin = mid+1;                                //否则，查找范围缩小到后半段
    }
    return -1;                                             //查找不成功
}  */


//第2版例8.1、例8.2用
#include <string.h>
//字符串数组的二分法查找，value数组元素已按升序排列，在value数组中二分法查找key元素，begin、end表示查找范围的下界和上界
//若查找成功返回元素下标，否则返回-1
int binarySearch(char* value[], char* str, int begin, int end)
{
    while (begin<=end)
    {
        int mid = (begin+end)/2;
        cout<<value[mid]<<"? ";
        if (strcmp(value[mid], str)==0)            //两个字符串相等
            return mid;
        if (strcmp(str, value[mid])==-1)           //str字符串值小
            end = mid-1;
        else
            begin = mid+1; 
    }
    return -1;
}  
