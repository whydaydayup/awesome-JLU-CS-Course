//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.3   基于索引表的分块查找
//【例8.1】 采用索引表查询C++关键字。
//【习8.2】 采用扩充索引表查询C++关键字。

#include <iostream>
using namespace std;
#include "MyString.h"                                      //字符串类（第3章）
#include "SortedSeqList.h"                                 //排序顺序表（第2章）

   //关键字表
MyString keywords[]={"auto","bool","break","case","catch","char","class","const","const_cast",
    "continue","default","delete","do","double","dynamic_cast","else","enum","explicit","extern","false","float","for","friend",
    "goto","if","inline","int","long","mutable","namespace","new","operator","private","protected","public",
    "register","reinterpret_cast","return","short","signed","sizeof","static","static_cast","struct","switch","template",
    "this","throw","true","try","typedef","typeid","typename","union","unsigned","using","virtual","void","volatile","while"};

class IndexItem                                            //索引项类
{
  public:
    char first;                                            //关键字的首字符
    int begin, end;                                        //首字符相同的关键字块在主表中的开始、结束下标

    IndexItem(char first=' ', int begin=0, int end=0)      //构造函数
    {
        this->first = first;
        this->begin = begin;
        this->end = end;
    }
    friend ostream& operator<<(ostream& out, IndexItem &item)//输出索引项字符串
    {
        out<<"("<<item.first<<","<<item.begin<<","<<item.end<<")";
        return out;
    }
    bool operator==(IndexItem &item)                       //约定索引项相等规则：首字符相同
    {
        return this->first==item.first;
    }
    bool operator<(IndexItem &item)                        //约定索引项比较大小规则：按首字符比较大小
    {
        return this->first<item.first;
    }
    bool operator>(IndexItem &item) 
    {
        return this->first>item.first; 
    }
    bool operator>=(IndexItem &item) 
    {
        return this->first>=item.first;
    }
};

//为关键字排序顺序表list建立索引表indexlist
void create(SortedSeqList<MyString> &list, SortedSeqList<IndexItem> &indexlist) 
{
    int begin=0;
    while (begin<list.count())
    {
        char first = list[begin][0];                       //list[begin]字符串的首字符
        int i=0;                                           //块元素计数
        while (begin+i<list.count() && list[begin+i][0]==first) //寻找块结束序号
            i++;
        indexlist.insert(IndexItem(first,begin,begin+i-1));//添加下一块的索引项
        begin += i;                                        //下一块开始序号
    }
}
//判断str是否为C++关键字。先在索引表indexlist中进行二分法查找获得str首字符对应的索引项；
//再在关键字排序顺序表list的指定范围内进行二分法查找
bool isKeyword(MyString str, SortedSeqList<MyString> &list, SortedSeqList<IndexItem> &indexlist)
{
    int i = indexlist.binarySearch(IndexItem(str[0],0,0));  //索引项序号
    return i!=-1 && list.binarySearch(str, indexlist[i].begin, indexlist[i].end)>=0;
}

//思考题8-1
//【习8.2】 采用扩充索引表查询C++关键字。

//为关键字排序顺序表list建立扩充索引表indexlist
void createExpand(SortedSeqList<MyString> &list, SortedSeqList<IndexItem> &indexlist) 
{
    char first = 'a';
    int begin=0;
    while (begin<list.count())
    {
        int i=0;                                           //块元素计数
        while (begin+i<list.count() && list[begin+i][0]==first) //寻找块结束序号
            i++;
        if (i==0)
            indexlist.insert(IndexItem(first,-1,-1));      //补充一个索引项
        else
        {
            indexlist.insert(IndexItem(first,begin,begin+i-1));//添加下一块的索引项
            begin += i;                                    //下一块开始序号
        }
        first++;                                           //下一块首字符
    }
}

//判断str是否为C++关键字。先计算str首字符对应的索引项在索引表indexlist中的序号，获得索引项；
//再在关键字表list的指定范围内进行二分法查找
bool isKeywordExpand(MyString str, SortedSeqList<MyString> &list, SortedSeqList<IndexItem> &indexlist)
{
    int i = str[0]-'a';                                    //首字符对应索引项的序号，O(1)
    if (i<0 || i>indexlist.count())
         return false;
    IndexItem item = indexlist[i];                         //索引项
    int begin=item.begin;                                  //获得块开始序号
    if (begin==-1)
        return false;
    return list.binarySearch(str, begin, item.end)>=0;     //二分法查找关键字表的指定范围
}

int main() 
{
    SortedSeqList<MyString> list(keywords,60);             //关键字排序顺序表
//    cout<<"主表，"<<list.getCount()<<"个关键字\n"<<list;
    SortedSeqList<IndexItem> indexlist;                    //空索引表
    create(list, indexlist);                               //建立索引表
    cout<<"索引表，索引项数："<<indexlist.count()<<endl<<indexlist;
    MyString str[]={"auto","and","false","length","while","why"};
    for (int i=0; i<6; i++)
        cout<<str[i]<<(isKeyword(str[i],list,indexlist)?"":"不")<<"是关键字\n";

    //思考题8-1，习8.2
    SortedSeqList<IndexItem> indexlist2;                   //空索引表
    createExpand(list,indexlist2);                         //建立扩充索引表
    cout<<"\n扩充索引表，索引项数："<<indexlist2.count()<<endl<<indexlist2;
    for (int i=0; i<6; i++)
        cout<<str[i]<<(isKeywordExpand(str[i],list,indexlist2)?"":"不")<<"是关键字\n";

    system("pause");
    return 0;
}

/*
程序运行结果如下：
索引表，索引项数：19
((a,0,0), (b,1,2), (c,3,8), (d,9,12), (e,13,16), (f,17,20), (g,21,21), (i,22,24), (l,25,25), (m,26,26), (n,27,27), (o,28,28), (p,29,31), (r,32,33), (s,34,40), (t,41,46), (u,47,48), (v,49,51), (w,52,52))
(m,26,26)? (e,13,16)? (b,1,2)? (a,0,0)? auto? auto是关键字
(m,26,26)? (e,13,16)? (b,1,2)? (a,0,0)? auto? and不是关键字
(m,26,26)? (e,13,16)? (g,21,21)? (f,17,20)? float? false? false是关键字
(m,26,26)? (e,13,16)? (g,21,21)? (i,22,24)? (l,25,25)? long? length不是关键字
(m,26,26)? (s,34,40)? (u,47,48)? (v,49,51)? (w,52,52)? while? while是关键字
(m,26,26)? (s,34,40)? (u,47,48)? (v,49,51)? (w,52,52)? while? why不是关键字

扩充索引表，索引项数：23
((a,0,0), (b,1,2), (c,3,8), (d,9,12), (e,13,16), (f,17,20), (g,21,21), (h,-1,-1), (i,22,24), (j,-1,-1), (k,-1,-1), (l,25,25), (m,26,26), (n,27,27), (o,28,28), (p,29,31), (q,-1,-1), (r,32,33), (s,34,40), (t,41,46), (u,47,48), (v,49,51), (w,52,52))
auto? auto是关键字
auto? and不是关键字
float? false? false是关键字
long? length不是关键字
while? while是关键字
while? why不是关键字


*/
