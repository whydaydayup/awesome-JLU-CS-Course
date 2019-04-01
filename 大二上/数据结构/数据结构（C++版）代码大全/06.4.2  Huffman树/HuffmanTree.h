//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.4   Huffman树
//构造哈夫曼树并获得哈夫曼编码
//使用顺序表存储

#include "SeqList.h"                                       //顺序表类（第2章）
#include "MyString.h"                                      //字符串类（第3章）
#include "TriElement.h"

class HuffmanTree                                          //Huffman树类
{
  private:
    MyString charset;                                      //字符集 
    SeqList<TriElement> huftree;                           //结点顺序表

    MyString encode(int i);                                //返回charset[i]字符的编码字符串

  public:
    HuffmanTree(int weight[], int n);                      //指定权值集合构造Huffman树
    void printCode();                                      //输出所有字符的编码
    MyString encode(MyString &text);                       //编码，数据压缩
    MyString decode(MyString &codestr);                    //译码，数据解压缩
};

//构造Huffman树，weight[]指定权值集合，n指定数组长度（叶子结点数）
HuffmanTree::HuffmanTree(int weight[], int n)
   : huftree(2*n-1)                    //声明执行SeqList<T>(int length)，n个叶子结点的Huffman树共有2n-1个结点
{                                      //此处先执行MyString(char *s, int length)，再执行SeqList<T>(int length)
    for (int i=0; i<n; i++)                                //初始化
    {   this->charset.insert(i,'A'+i);                     //默认字符集从'A'开始的n个字符
        this->huftree.insert(TriElement(weight[i],-1,-1,-1)); //初始有n个叶子结点
    }
    cout<<"Huffman树的结点顺序表初值："<<this->huftree<<endl;

    for (int i=0; i<n-1; i++)                              //构造n-1个2度结点，每次循环构造1个2度结点
    {
        int min1=0x7fffffff, min2=min1, x1=0, x2=0;        //最小和次最小权值及其下标
        for (int j=0; j<n+i; j++)                          //查找两个无父母的最小权值结点
            if (huftree[j].parent==-1 && huftree[j].data<min1)
            {
                min2 = min1;
                x2 = x1;
                min1 = huftree[j].data;                    //min1记最小权值
                x1 = j;                                    //x1记最小权值结点下标
            }
            else if (huftree[j].parent==-1 && huftree[j].data<min2)
                 {
                     min2 = huftree[j].data;               //min2记次最小权值
                     x2 = j;                               //x2记次最小权值结点的下标
                 }

        huftree[x1].parent = n+i;                          //将找出的两棵权值最小的子树合并为一棵子树
        huftree[x2].parent = n+i;        
        huftree.insert(TriElement(huftree[x1].data+huftree[x2].data, -1, x1, x2));   //添加第n+i个结点
    }
    cout<<"Huffman树的结点顺序表："<<this->huftree<<endl;
}

MyString HuffmanTree::encode(int i)                        //返回charset[i]字符的编码字符串
{
    MyString str;                                          //以MyString字符串保存Huffman编码
    int child=i, parent=huftree[child].parent;
    while (parent!=-1)                                     //由叶结点向上直到根结点循环
    {
        str += (huftree[parent].left==child) ? '0' : '1';  //左、右孩子结点编码为0、1。+=连接串
        child = parent;
        parent = huftree[child].parent;        
    }
    str.reverse();                                         //将str串逆转，得到编码字符串
    return str;
}

void HuffmanTree::printCode()                              //输出所有字符的编码
{
    cout<<"Huffman编码：";
    for (int i=0; i<this->charset.count(); i++)            //输出所有叶子结点的Huffman编码
        cout<<this->charset[i]<<" "<<encode(i)<<"，";
    cout<<endl; 
}

MyString HuffmanTree::encode(MyString &text)               //编码，数据压缩，返回将text中所有字符压缩的编码字符串
{
    MyString codestr;
    for (int i=0; i<text.count(); i++) 
        codestr += encode(text[i]-'A');                    //默认字符集是从A开始的n个字符
    return codestr;
}

MyString HuffmanTree::decode(MyString &codestr)            //译码，数据解压缩，返回将编码串str解压后的译码字符串
{
    MyString text;
    int node=this->huftree.count()-1;                      //node搜索一条从根到达叶子的路径
    for (int i=0; i<codestr.count(); i++) 
    {
        if (codestr[i]=='0')                               //根据0/1分别向左右孩子走
            node = huftree[node].left;
        else node = huftree[node].right;
        if (huftree[node].isLeaf())                        //到达叶子结点
        {
            text += this->charset[node];                   //获得一个字符
            node=this->huftree.count()-1;                  //node再从根结点开始
        }
    }
    return text;
}

//void min(T values[], int n, T &min1, T &min2)	//求values数组的最小值和次最小值
//？？<T>，不行。因为，由散列表统计字符出现次数，CharCount类声明??其他没改
//思考题：？？
//输入文本，查找， 