//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//【习4.1】  打印数字塔。

#include <iostream>
using namespace std;

void count(int i, int n)                         //递归函数，输出一行
{
    cout<<i<<"  ";
    if (i<n)
    {
        count(i+1,n);
        cout<<i<<"  ";
    }
}

int main()
{
   int n=9;
   for(int i=1; i<=n; i++)
   {
       for (int j=n; j>i; j--)
           cout<<"   ";
       count(1, i);
       cout<<"\n";
   }
   return 0;
}

/*
程序运行结果如下：
                          1
                       1  2  1
                    1  2  3  2  1
                 1  2  3  4  3  2  1
              1  2  3  4  5  4  3  2  1
           1  2  3  4  5  6  5  4  3  2  1
        1  2  3  4  5  6  7  6  5  4  3  2  1
     1  2  3  4  5  6  7  8  7  6  5  4  3  2  1
  1  2  3  4  5  6  7  8  9  8  7  6  5  4  3  2  1
*/
