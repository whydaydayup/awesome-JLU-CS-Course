//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例2.1】使用顺序表求解约瑟夫环问题。

#include "SeqList.h"                                       //顺序表类
//#include "SinglyList.h"                                    //单链表类
//#include "CirDoublyList.h"                                 //循环双链表类


//创建Josephus环并求解，参数指定环长度、起始位置、计数。使用顺序表
void josephus(int number, int start, int distance)
{
    SeqList<char> list;                                    //创建顺序表对象，执行无参构造函数，指定顺序表默认容量
    int i=0;
    for (i=0; i<number; i++)
        list.insert('A'+i);                                //在顺序表最后添加元素，O(1)
    cout<<"Josephus环("<<number<<","<<start<<","<<distance<<")，"<<list;    //输出顺序表

    i = start;                                             //计数起始位置
    while (list.count()>1)                                 //多于一个元素时循环，O(1)
    {
        i = (i+distance-1) % list.count();                 //计数时按循环规律变化，顺序表可看作是环形结构
        cout<<"删除"<<list.remove(i)<<"，"<<list;          //删除指定位置元素，O(n)
    }
    cout<<"被赦免者是"<<list[0]<<endl;                     //list[0]获得元素，O(1)
}

/*//创建Josephus环并求解，参数指定环长度、起始位置、计数。使用单链表、循环双链表
void josephus(int number, int start, int distance)
{
//    SinglyList<char> list;                                 //创建空单链表
    CirDoublyList<char> list;                              //创建空循环双链表
    int i;
    for (i=number-1; i>=0; i--)
        list.insert(0, 'A'+i);                             //单链表头插入，O(1)
    cout<<"Josephus环("<<number<<","<<start<<","<<distance<<")，"<<list;

    i = start;                                             //计数起始位置
    while (list.getCount()>1)                              //多于一个元素时循环，O(1)
    {
        i = (i+distance-1) % list.getCount();              //计数时按循环规律变化，顺序表可看作是环形结构
        cout<<"删除"<<list.remove(i)<<"，"<<list;          //删除指定位置元素，O(n)
    }
    cout<<"被赦免者是"<<list.get(0)<<endl;                 //get(0)获得第一个元素，O(1)
}*/

int main()
{
    josephus(5,0,2);
//    josephus(10,0,2);
//    josephus_set(5,0,2);
    system("pause");
    return 0;
}

/*
程序运行结果如下：
Josephus环(5,0,2)， (A, B, C, D, E) 
删除B， (A, C, D, E)
删除D， (A, C, E)
删除A， (C, E)
删除E， (C)
被赦免者是C 
*/

/* 顺序表不删除元素算法，设置空位置
void josephus_set(int number, int start, int distance)     //求解约瑟夫环
{                                                          //参数指定环长度、起始位置、计数
    SeqList<char> jose(number);                            //创建顺序表，长度为number
    int i=0;
    for (i=0; i<number; i++) 
        jose.insert('A'+i);                                //在顺序表最后添加元素
    cout<<"约瑟夫环("<<number<<","<<start<<","<<distance<<")，"<<jose;
//   jose.print();                                          //输出约瑟夫环中所有元素

    i = start-1;                                           //计数起始位置
    int count = jose.length();
    while (count>1)                                        //多于一个对象时循环
    {
        int j=0;
        while (j<distance) 
        {
            i = (i+1) % jose.length();                     //计数时按循环规律变化
            if (jose.get(i)!=' ')
                j++;
        }
        cout<<"删除"<<jose.get(i)<<"，";
        jose.set(i, ' ');                                  //以空格表示该位置元素为空
        count--;
        cout<<jose;//.print();
    }

    i=0;                                                   //寻找最后一个元素
    while (i<jose.length() && jose.get(i)==' ')
        i++;
    cout<<"被赦免者是"<<jose.get(i)<<endl;
}*/

/*
程序运行结果如下：
     josephus_set(5,0,2);
程序运行结果如下：
约瑟夫环(5,0,2)，list: (A, B, C, D, E) 
删除B，list: (A,  , C, D, E)
删除D，list: (A,  , C,  , E)
删除A，list: ( ,  , C,  , E)
删除E，list: ( ,  , C,  ,  )
被赦免者是C 
*/