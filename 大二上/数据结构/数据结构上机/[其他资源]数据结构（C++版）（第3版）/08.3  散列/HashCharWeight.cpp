//《数据结构（C++版）（第3版）》 作者：叶核亚
//8.4   散列
//【例8.2】统计文本中各字符的出现次数，为建立Huffman树做准备。

#include "MyString.h"                                      //字符串类（第3章）
#include "HashSet.h"                                       //采用链地址法的散列表类

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
    void add()                                             //出现次数加1
    {
        this->count ++;
    }
    int hashCode()                                         //返回散列码，将字符character值转换成int
    {
        return (int)this->character; 
    }
    bool operator==(CharCount &cc)                         //约定元素相等规则：字符相同
    {
        return this->character==cc.character;
    }
    bool operator!=(CharCount &cc) 
    {
        return this->character!=cc.character;
    }
};

//使用散列表作为存储结构，统计text中各字符及其出现次数
void HashCharWeight(MyString text)
{
    HashSet<CharCount> set(text.count());                  //创建空散列表，指定散列表数组容量
    for (int i=0; i<text.count(); i++)                     //逐个字符查找计数
    {
        CharCount key(text[i],1);
        CharCount *find = set.search(key);                 //查找
        if (find==NULL) 
            set.insert(key);                               //插入
        else  
            find->add();                                   //对应字符计数加1
    }   
    cout<<"\""<<text<<"\"字符及其出现次数：\n"<<set;
}

int main()
{
    HashCharWeight("class HashSet");
//    HashCharWeight("public class");   
//    HashCharWeight("AAAABBBCDDBBAAA");

    system("pause");
    return 0;
}

/*
程序运行结果如下：
"class HashSet"字符及其出现次数：
table[0]= ()
table[1]= ((e,1))
table[2]= (( ,1), (H,1))
table[3]= ((S,1))
table[4]= ((h,1))
table[5]= ((s,3))
table[6]= ((t,1))
table[7]= ((a,2))
table[8]= ((l,1))
table[9]= ((c,1))

"class HashSet"字符及其出现次数：
table[0]= ((h,1))
table[1]= ()
table[2]= ()
table[3]= ()
table[4]= ((l,1))
table[5]= ((S,1))
table[6]= ((a,2), ( ,1))
table[7]= ((H,1))
table[8]= ((c,1))
table[9]= ()
table[10]= ((e,1))
table[11]= ((s,3))
table[12]= ((t,1))


"public class"字符及其出现次数：
table[0]= ()
table[1]= ()
table[2]= ((p,1), ( ,1))
table[3]= ()
table[4]= ()
table[5]= ((i,1), (s,2))
table[6]= ()
table[7]= ((u,1), (a,1))
table[8]= ((b,1), (l,2))
table[9]= ((c,2))


*/
