//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.4】 进程按优先级调度管理。

//#include "MyString.h"                                      //字符串类
#include "PriorityQueue.h"                                 //优先队列类

struct Process                                             //进程
{
    char* name;                                            //进程名
    int priority;                                          //优先级

    friend ostream& operator<<(ostream& out, Process &p)
    {
        out<<"("<<p.name<<","<<p.priority<<")";
        return out;
    }
    bool operator==(Process &p)                            //比较两个进程是否相等，用于查找时识别对象
    {
        return this->name==p.name && this->priority==p.priority;
    }
    bool operator!=(Process &p)
    {
        return !(*this==p);
    }
    bool operator>(Process &p)                             //比较两个进程大小，约定进程排队次序
    {
        return priority > p.priority;
    }
    bool operator>=(Process &p)
    {
        return priority >= p.priority;
    }
    bool operator<(Process &p)
    {
        return priority < p.priority;
    }
    bool operator<=(Process &p)
    {
        return priority <= p.priority;
    }
};

int main()
{
//    Process pro={"A",4};

    const int N=6;
    Process pro[N]={{"A",4},{"B",3},{"C",5},{"D",4},{"E",1},{"F",10}};     //进程序列
    PriorityQueue<Process> que(false);                            //优先队列，参数指定降序
    cout<<"入队进程：";
    for (int i=0; i<N; i++)
    {
        que.enqueue(pro[i]); 
        cout<<pro[i]<<" ";
    }

    cout<<"\n出队进程：";
    while (!que.empty()) 
        cout<<que.dequeue()<<" "; 
    cout<<endl;

    system("pause");
    return 0;
}
    
/*
程序运行结果如下：
入队进程：(A,4) (B,3) (C,5) (D,4) (E,1) (F,10) 
出队进程：(F,10) (C,5) (A,4) (D,4) (B,3) (E,1) 

*/

