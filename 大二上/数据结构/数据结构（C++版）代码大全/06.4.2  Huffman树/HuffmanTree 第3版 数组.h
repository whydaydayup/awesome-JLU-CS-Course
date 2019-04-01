//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.4   Huffman树
//构造哈夫曼树并获得哈夫曼编码
//初稿，使用数组

#include "MyString.h"                                      //字符串类（见第3章）
#include "TriElement.h"

class HuffmanTree                                          //Huffman树类
{
  private:
    int leafNum;                                           //叶子结点个数
    TriElement *huftree;                                   //结点数组
    MyString *hufcodes;                                    //Huffman编码数组，元素是字符串

    void getHuffmanCode();                                 //获得Huffman编码

  public:
    HuffmanTree(int weight[], int n);                      //构造指定权值集合的Huffman树
    ~HuffmanTree();
    void print();
};

//构造Huffman树，weight数组指定权值集合，n指定叶子结点数，即数组长度
HuffmanTree::HuffmanTree(int weight[], int n)
{
    this->leafNum = n;
    this->huftree = new TriElement[2*n-1];                 //n个叶子结点的Huffman树共有2n-1个结点//TriElement声明类，调用TriElement()
    for (int i=0; i<n; i++)                                //结点数组初始化有n个叶子结点
    {
        this->huftree[i].data = weight[i];
        huftree[i].parent = huftree[i].left = huftree[i].right = -1;
    }

    for (int i=0; i<n-1; i++)                              //构造n-1个2度结点，每次循环构造1个2度结点
    {
        int min1, min2, x1, x2;
        min1 = min2 = 0x7fffffff;                          //选择最小和次最小权值，初值为整数最大值（16进制）
        x1 = x2 = -1;                                      //记录两个无父母的最小权值结点下标
        for (int j=0; j<n+i; j++)                          //查找两个无父母的最小权值结点
            if (huftree[j].data<min1 && huftree[j].parent==-1)
            {
                min2 = min1;
                x2 = x1;
                min1 = huftree[j].data;                    //min1记下最小权值
                x1 = j;                                    //x1记下最小权值结点的下标
            }
            else if (huftree[j].data<min2 && huftree[j].parent==-1)
                 {
                     min2 = huftree[j].data;               //min2记下次小权值
                     x2 = j;                               //x2记下次小权值结点的下标
                 }

        huftree[x1].parent = n+i;                          //将找出的两棵权值最小的子树合并为一棵子树
        huftree[x2].parent = n+i;
        huftree[n+i].data = huftree[x1].data+huftree[x2].data;
        huftree[n+i].parent = -1;
        huftree[n+i].left = x1;
        huftree[n+i].right = x2;
    }
    getHuffmanCode();                                      //Huffman编码数组，元素是字符串
}

//从huftree结点数组获得当前Huffman树的Huffman编码，hufcodes数组以MyString字符串形式保存Huffman编码
void HuffmanTree::getHuffmanCode()
{
    this->hufcodes = new MyString[this->leafNum];          //编码数组，一个字符串表示一个编码，执行leafNum次MyString()
    for (int i=0; i<this->leafNum; i++)                    //求leafNum个叶子结点的Huffman编码
    {
        int child=i, parent=this->huftree[child].parent;
        while (parent!=-1)                                 //由叶结点向上直到根结点循环
        {
            this->hufcodes[i] += (huftree[parent].left==child) ? '0' : '1'; //左、右孩子结点编码为0、1。+=是MyString字符串连接运算
            child = parent;
            parent = this->huftree[child].parent;        
        }
        this->hufcodes[i].reverse();                       //将当前串逆转，得到编码字符串
    }
}

void HuffmanTree::print()
{
    cout<<"Huffman树的结点数组：\n";
    int i;
    for (i=0; i<this->leafNum*2-1; i++)
        cout<<"第"<<i<<"行  "<<huftree[i].data<<", "<<huftree[i].parent<<", "<<huftree[i].left<<", "<<huftree[i].right<<endl;

    cout<<"\nHuffman编码：\n";
    for (i=0; i<this->leafNum; i++)
        cout<<this->hufcodes[i]<<endl;
    cout<<endl;
}

HuffmanTree::~HuffmanTree()
{
    delete[] this->huftree;
    delete[] this->hufcodes;
}

/*??
//    byte* encode(char *str, char *letter, int &len);               //编码，数据压缩
//    char* decode(char *letter, byte codes[], int n);             //译码，数据解压缩
int indexOf(char *str, char ch)                   //返回字符ch在字符串str中的序号
{
    int i=0;
    while (letter[i]!='\0' && letter[i]!=ch)
        i++;
    if (letter[i]!='\0')
        return i;
    else
        return -1;
}

byte* HuffmanTree::encode(char *str, char *letter, int bitCount)  //编码，数据压缩
{
    char *codes=new char[100];
    for (int i=0; str[i]!='\0'; i++)
    {
        int j=indexOf(letter, str[i]);           //求str[i]字符在letter字符串中的序号
        hufcodes[j]                              // str[i]字符r    编码

    }
    int 
    codes[j]
}

char* HuffmanTree::decode(char *letter, char *codes)             //译码，数据解压缩
{
}

  */