//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.5.1   二叉排序树
//统计text中各字符及其出现次数

//#include "MyString.h"                                      //字符串类（第3章）
#include "BinarySortTree.h"                                //二叉排序树类

class CharCount                                            //字符及其出现次数
{
  private:
    char character;                                        //字符
    int count;                                             //出现次数

  public:
    CharCount(char character=' ', int count=0)
    {
        this->character = character;
        this->count = count;
    }
    friend ostream& operator<<(ostream& out, CharCount &cc) //输出元素，形式为“(字符,出现次数)”
    {
        out<<"("<<cc.character<<","<<cc.count<<")";
        return out;
    }
    void add()                    	   //出现次数加1
    {
        this->count ++;
    }
    int hashCode()                                         //返回散列码，根据字符决定对象在散列表中的位置
    {
        return (int)this->character; 
    }
    bool operator==(CharCount &cc)                     //约定索引项相等规则：字符相同
    {
        return this->character==cc.character;
    }
    bool operator!=(CharCount &cc) 
    {
        return this->character!=cc.character;
    }
    bool operator<(CharCount &cc) 
    {
        return this->character<cc.character;
    }
};

void BSTCharWeight(MyString text)                    	   //统计text中各字符及其出现次数
{
    BinarySortTree<CharCount> set;                         //构造空二叉排序树
    for (int i=0; i<text.count(); i++)                     //逐个字符查找计数
    {
        CharCount key(text[i],1);
        CharCount *find = set.search(key);                 //查找，element引用查找到的元素
        if (find==NULL) 
            set.insert(key);                               //插入
        else  
            find->add();                                   //对应字符计数加1
    }   
    cout<<"\""<<text<<"\"字符及其出现次数：\n"<<set;
    set.inOrder();
}

int main()
{
    BSTCharWeight("class BinarySortTree");
//    BSTCharWeight("public class");
//    BSTCharWeight("AAAABBBCDDBBAAA");

    system("pause");
    return 0;
}

/*
程序运行结果如下：
class BinarySortTree字符及其出现次数：
先根次序遍历二叉树:  (c,1) (a,2) ( ,1) ∧(B,1) ∧(S,1) ∧(T,1) ∧∧∧(l,1) (i,1) (e,2) ∧∧∧(s,2) (n,1) ∧(r,3) (o,1) ∧∧∧(y,1) (t,1) ∧∧∧
中根次序遍历二叉树:  ( ,1) (B,1) (S,1) (T,1) (a,2) (c,1) (e,2) (i,1) (l,1) (n,1) (o,1) (r,3) (s,2) (t,1) (y,1) 
撤销二叉树: (T,1) (S,1) (B,1) ( ,1) (a,2) (e,2) (i,1) (o,1) (r,3) (n,1) (t,1) (y,1) (s,2) (l,1) (c,1) 

public class字符及其出现次数：
先根次序遍历二叉树:  (p,1) (b,1) ( ,1) ∧(a,1) ∧∧(l,2) (i,1) (c,2) ∧∧∧∧(u,1) (s,2) ∧∧∧
中根次序遍历二叉树:  ( ,1) (a,1) (b,1) (c,2) (i,1) (l,2) (p,1) (s,2) (u,1) 
撤销二叉树: (a,1) ( ,1) (c,2) (i,1) (l,2) (b,1) (s,2) (u,1) (p,1) 

*/
