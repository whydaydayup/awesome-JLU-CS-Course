//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例1.1】  算法时间复杂度分析。

#include <iostream>
using namespace std; 

int main() 
{ 
    int n=8,count=0,i,j;
    for (i=1; i<=n; i++)                         //时间复杂度为O(n)的循环语句
        count++;
    cout<<"1 count="<<count<<"\tn="<<n<<endl;

    count=0;
    cout<<"i=";
    for (i=1; i<=n; i*=2)                        //时间复杂度为O(log2(n)+1)的循环语句
    {
        cout<<i<<"  ";
        count++;
    }
    cout<<"\n2 count="<<count<<"\n";//<<log(n);

    count=0;
    for (i=1; i<=n; i++)                         //时间复杂度为O(n*n)的二重循环
        for(j=1; j<=n; j++)
            count++;
    cout<<"3 count="<<count<<"\tn*n="<<n*n<<endl;

    count=0;
    for (i=1; i<=n; i++)                         //时间复杂度为O(n*n)的二重循环
        for (j=1; j<=i; j++)
            count++;
    cout<<"4 count="<<count<<"\tn*(n+1)/2="<<n*(n+1)/2<<endl;

    count=0;
    for (i=1; i<=n; i*=2)                        //时间复杂度为O(nlog2(n))的二重循环
        for (j=1; j<=n; j++)
            count++;
    cout<<"5 count="<<count<<"\tn*log2(n)="<<endl; //n*log2(n)<<

    count=0;
    for (i=1; i<=n; i*=2)                        //时间复杂度为O(n)的二重循环
        for (j=1; j<=i; j++)
            count++;
    cout<<"6 count="<<count<<"\t2n-1="<<2*n-1<<endl;
    system("pause");
    return 0;
}

/*
程序运行结果如下:
1 count=8	n=8
i=1  2  4  8  
2 count=4
3 count=64	n*n=64
4 count=36	n*(n+1)/2=36
5 count=32	n*log2(n)=32
6 count=15	2n-1=15

*/