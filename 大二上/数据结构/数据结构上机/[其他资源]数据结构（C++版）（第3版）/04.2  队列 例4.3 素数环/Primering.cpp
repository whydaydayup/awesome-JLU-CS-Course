//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.3】 求解素数环问题。

#include <math.h>                                          //包含sqrt()函数
#include "SeqList.h"                                       //顺序表类
#include "SeqQueue.h"                                      //顺序循环队列类
#include "LinkedQueue.h"                                   //链式队列类
#include "DoublyQueue.h"                                   //链式队列类，使用循环双链表类作为成员变量实现队列

bool isPrime(int key)                                      //判断key是否为素数
{
    if (key==2)
        return true;
    if (key<2 || key>2 && key%2==0)
        return false;

    int j=(int)sqrt((double)key);                          //sqrt(key)返回key的平方根值，定义在math.h中
    if (j%2==0)
        j--;                                               //获得测试范围内的最大奇数
    while (j>2 && key%j!=0)
        j-=2;
    return j<2;
}

void primering(int n)                                      //输出1～n素数环的一个解
{
    SeqList<int> ring(n);                                  //创建一个顺序表存储素数环
    ring.insert(1);                                        //1添加到素数环中

    SeqQueue<int> que;                                     //空队列
//    LinkedQueue<int> que;
//    DoublyQueue<int> que;
    for (int i=2; i<=n; i++)                               //2～n全部入队
        que.enqueue(i);

    int i=0;
    while (!que.empty()) 
    {
        int key = que.dequeue();                           //出队
        if (isPrime((ring[i]+key)))                        //判断是否为素数
        {
            ring.insert(key);                              //key添加到素数环最后
            i++;
        }
        else
            que.enqueue(key);                              //再次入队
        cout<<que;                                         //输出队列
    }
    cout<<"1～"<<n<<"素数环："<<ring;                      //输出素数环
}

int main()
{
    primering(10);
    system("pause");
    return 0;
}
    
/*
程序运行结果如下：
1～10素数环：(1, 2, 3, 4, 7, 10, 9, 8, 5, 6)

1～20素数环：(1, 2, 3, 4, 7, 10, 13, 16, 15, 8, 9, 14, 17, 20, 11, 12, 19, 18, 5, 6)

*/
