//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.5】  用递归算法计算Fibonacci序列。

#include <iostream>
using namespace std;

int fibonacci(int n)                                       //求Fibonacci序列第n项，递归函数
{
    if (n==0 || n==1)                                      //边界条件，递归结束条件
        return n;
    if (n>=2)
        return fibonacci(n-2)+fibonacci(n-1);              //递归调用，递推通式
    throw invalid_argument("Fibonacci序列当n<0时无定义");  //抛出无效参数异常
}

int main()
{
    for (int i=0; i<=20; i++)
        cout<<fibonacci(i)<<" ";
    cout<<endl;

    system("pause");
    return 0;
}

/*
程序运行结果如下：
 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765
*/