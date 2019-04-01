//《数据结构（C++版）（第3版）》 作者：叶核亚
//3.2.3   字符串类

#include <iostream>
using namespace std;
#include <string.h>        //包含strlen(s)求串长等函数
//约定：在保证正确前提下，可对char*使用string.h中函数

class MyString                                             //字符串类，//？？如何声明最终类，不能被继承
{
  private:                                                 //私有成员
    char *element;                                         //动态字符数组
    int length;                                            //数组容量
    int n;                                                 //串长度
    void init(char *s="", int length=32);                  //初始化串，参数指定初值和容量

  public:
    MyString(char *s="", int length=32);                   //构造串对象，s指定char*串常量，length指定容量
    MyString(char ch);                                     //构造串对象，ch指定字符初值
    MyString(MyString &str);                               //拷贝构造函数，深拷贝
    MyString& operator=(MyString &str);                    //重载=赋值运算符，深拷贝
    MyString& operator=(char *str);                        //支持赋值为字符串常量
    ~MyString();                                           //析构函数

    bool empty();                                          //判断串是否为空
    int count();                                           //返回串长度
    char& operator[](int i);                               //重载下标运算符，引用第i（≥0）个字符
    friend ostream& operator<<(ostream& out, MyString &s); //重载<<输出流运算符

    bool operator==(MyString &str);                        //重载==运算符，比较两串是否相等
    bool operator!=(MyString &str);                        //重载!=运算符，比较两串是否不相等
    bool operator<(MyString &str);                         //重载<运算符，比较两串大小
    bool operator<=(MyString &str);
    bool operator>(MyString &str);
    bool operator>=(MyString &str);
    void reverse();                                        //将当前串逆转。Huffman算法用

    MyString substring(int i, int len);                    //返回从第i个字符开始长度为len的子串
    MyString substring(int i);                             //返回从第i个字符开始至串尾的子串
    void insert(int i, MyString &str);                     //在第i个字符处插入str串
    void insert(int i, char ch);                           //插入ch作为第i个字符
    void insert(int i, char* str);                         //在第i个字符处插入str串
    void operator+=(MyString &str);                        //重载＋=运算符，在当前串之后连接str串
    void operator+=(char ch);                              //重载＋=运算符，在当前串之后连接ch字符
    void operator+=(char *str);                            //重载＋=运算符，在当前串之后连接str串
    MyString operator+(MyString &str);                     //重载＋运算符，返回当前串与str连接后的串
    void remove(int i, int len);                           //删除从第i个字符开始长度为len的子串
    void remove(int i);                                    //删除从第i个字符开始至串尾的子串

    //3.3   串的模式匹配
    int search(MyString &pattern, int start=0);            //返回当前串中从start开始首个与模式串pattern匹配的子串序号
    void removeFirst(MyString &pattern);                   //删除串中首个与pattern匹配的子串
    void removeAll(MyString &pattern);                     //删除串中包含的所有与pattern匹配的子串
    void replaceFirst(MyString &pattern, MyString &str);   //将串中首个与pattern匹配的子串替换为str
    void replaceAll(MyString &pattern, MyString &str);     //将串中所有与pattern匹配的子串替换为str

   //习题解答习3.2
    void trim();                                           //删除串所有空格。习题.2

    //实验3
    void uppercase();                                      //将串中的小写字母转换成大写字母

  private:
    //3.3   串的模式匹配
    void getNext(int next[]);                              //返回模式串pattern改进的next数组
};

//1. 字符串的基本操作
//（1）构造、析构
void MyString::init(char *s, int length)                   //初始化串，s指定初值，length指定（默认）数组容量
{
    this->n = strlen(s);                                   //获得s串长度，strlen(s)定义在string.h中
    this->length = (n*2)>length ? (n*2) : length;          //指定数组容量，取n*2、length最大值
    this->element = new char[this->length];                //申请字符数组
    for (int i=0; s[i]!='\0'; i++)                         //复制s字符串，strcpy(*,*)功能
       this->element[i] = s[i]; 
    this->element[this->n] = '\0'; 
}
//构造串对象，s指定初值，接受char*类型的字符串常量；length指定数组容量，有默认值
MyString::MyString(char *s, int length) 
{
    this->init(s, length);
//    cout<<s<<endl;
}
MyString::MyString(char ch)                                //构造串对象，ch指定字符初值
{
    this->init("");
    this->n = 1;
    this->element[0] = ch; 
    this->element[1] = '\0'; 
}
MyString::MyString(MyString &str)                          //拷贝构造函数，深拷贝
{
    this->init(str.element);
}
MyString& MyString::operator=(MyString &str)               //重载=赋值运算符，深拷贝
{
    this->~MyString();                                     //调用析构函数，释放element数组空间
    this->init(str.element);                               //全部重新申请数组空间
    return *this;
}
MyString& MyString::operator=(char *str)                   //重载=赋值运算符，深拷贝
{
    this->~MyString();                                     //调用析构函数，释放element数组空间
    this->init(str);                                       //全部重新申请数组空间
    return *this;
}

MyString::~MyString()                                      //析构函数
{
//    cout<<"MyString析构"<<*this<<"，n="<<count<<"，length="<<length<<endl;
    delete []this->element;
}

//【思考题3-1】
//（2）判空、串长度、输出和存取字符
bool MyString::empty()                                   //判断串是否为空
{
    return this->n==0;
}
int MyString::count()                                      //返回串长度
{
    return this->n;
}

//重载下标运算符，引用第i（0≤i<n）个字符。若i<0或i≥n，则抛出异常
char& MyString::operator[](int i)
{
    if (i>=0 && i<this->n)
        return this->element[i];                           //返回元素引用
    throw out_of_range("参数i指定元素序号超出范围");       //抛出C++ STL范围越界异常
}

ostream& operator<<(ostream& out, MyString &str)           //重载<<输出流运算符
{
    out<<"\""<<str.element<<"\"";                          //输出流支持以字符指针形式输出字符数组
    return out;
}

//【习3.1】  
//（6）关系运算，char支持==、!=、>、>=、<、<=运算
bool MyString::operator==(MyString &str)                   //重载==运算符，比较两个串是否相等
{
    if (this==&str)                                        //指针比较，当两个对象引用同一个实例时
        return true;
    if (this->n != str.n)                                  //以下考虑深拷贝情况，比较两者长度是否相等，不比较数组容量
        return false;
    for (int i=0; i<this->n; i++)                          //比较两个串的所有字符是否对应相等
        if (this->element[i] != str.element[i])
            return false;
    return true;
}
bool MyString::operator!=(MyString &str)                   //重载!=运算符，比较两个串是否不相等
{
    return !(*this==str);
}

bool MyString::operator<(MyString &str)                    //重载<运算符，比较两个串大小
{
    if (this==&str)                                        //指针比较，当两个对象引用同一个实例时
        return false;
    int i=0;
    while (i<this->n && i<str.n)
        if (this->element[i]==str.element[i])              //对应字符相等时继续比较
            i++;
        else
            return this->element[i]<str.element[i];        //以首个不相等字符确定两串的大小
    return this->n < str.n;                        //两串前若干字符对应相等，还要比长度。*this串较短时返回1，不包括等长
}   

bool MyString::operator<=(MyString &str)                   //重载<=运算符，比较两个串大小
{
    if (this==&str)                                        //指针比较，当两个对象引用同一个实例时
        return true;
    int i=0;
    while (i<this->n && i<str.n)
        if (this->element[i]==str.element[i])                    //对应字符相等时继续比较
            i++;
        else
            return this->element[i]<str.element[i];
    return this->n <= str.n;                       //两串等长或*this串较短时返回1
}   

bool MyString::operator>(MyString &str)                    //重载>运算符，比较两个串的大小
{
    return !(*this <= str);
}

bool MyString::operator>=(MyString &str)                   //重载>=运算符，比较两个串的大小
{
    return !(*this < str);
}

void MyString::reverse()                                   //将当前串逆转。Huffman算法用
{
    for (int i=0; i<n/2; i++)
    {
        char temp = this->element[i];                      //交换字符
        this->element[i] = element[n-1-i]; 
        this->element[n-1-i] = temp;
    }
}

//2.  对子串的操作
//（1）求子串
//返回从第i（0≤i<n）个字符开始长度为len（>=0）的子串；len容错，若i+len>串长度n，
//则复制到串尾。若i<0或i≥n，或len<0则抛出异常
MyString MyString::substring(int i, int len)
{
    if (i>=0 && i<n && len>=0)
    {
        if (len>n-i)                                       //len容错
            len=n-i;                                       //i+len最多到串尾
        MyString sub;                                      //创建空串对象
        sub.n = len;                                       //若len=0，则返回空串
        for (int j=0; j<len; j++)
            sub.element[j] = this->element[i+j];
        sub.element[len]='\0';
        return sub;                                        //执行MyString的拷贝构造函数
    }
    else
        throw out_of_range("参数i指定字符序号或len超出范围");//抛出C++ STL范围越界异常
}
MyString MyString::substring(int i)                        //返回从第i个字符开始至串尾的子串
{
    return substring(i, this->n-i+1);
}

//（2）插入串
//在第i（≥0）个字符处插入str串。i容错，若i<0，插入在最前；若i≥n，插入在最后
void MyString::insert(int i, MyString &str) 
{
    if (str.n==0)  return;                                 //若str为空串，则不操作
    if (i<0)  i=0;                                         //插入位置i容错，最前
    if (i>n)  i=n;                                         //最后
    char *temp = this->element;
    if (this->length <= this->n+str.n)                     //若当前串的字符数组空间不足，则扩充容量
    {
        this->length = (this->n+str.n+1)*2;                //指定数组容量
        this->element = new char[this->length];            //重新申请字符数组空间
        for (int j=0; j<i; j++)                            //复制当前串前i-1个字符
            this->element[j] = temp[j];
    }
    for (int j=this->n; j>=i; j--)                         //从i开始至串尾的子串（包括'\0'）向后移动，次序是从后向前
        this->element[j+str.n] = temp[j];                  //移动距离是插入串长度
    if (temp!=this->element)
        delete[] temp;                                     //释放原数组空间
    for (int j=0; j<str.n; j++)                            //插入str串
        this->element[i+j] = str.element[j];
    this->n += str.n;
}
void MyString::insert(int i, char ch)                      //插入ch作为第i个字符。i序号越界容错
{
    this->insert(i, MyString(ch));
}
void MyString::insert(int i, char* str)                    //在第i个字符处插入str串常量。i序号越界容错
{
    this->insert(i, MyString(str));
}

//【思考题3-2】连接串
//重载+=运算符，在当前串之后连接str，*this += str，改变当前串
void MyString::operator+=(MyString &str)
{
    this->insert(this->n, str);
}
void MyString::operator+=(char ch)                      //连接ch字符
{
    insert(this->n, MyString(ch));
}
void MyString::operator+=(char* str)                    //连接str串，习题3
{
    insert(this->n, MyString(str));
}

//重载+运算符，返回连接起来的新串，result=*this+str，不改变当前串*this
MyString MyString::operator+(MyString &str)
{
    MyString result(*this);                                //复制当前串*this，执行MyString的拷贝构造函数
    result.insert(this->n, str);
    return result;                                         //返回串对象，执行MyString的拷贝构造函数
}

//（3） 删除子串
//删除从第i（0≤i<n）个字符开始长度为len（>0）的子串。若i或len参数无效，则不操作。
//len容错，若i+len>串长度n，则删除到串尾
void MyString::remove(int i, int len)
{
    if (i<0 || i>=this->n || len<0)
        return;
    if (len>n-i)                                           //len容错，若i+len>串长度n，则删除到串尾
        len = n-i;
    for (int j=i+len; j<=n; j++)                           //从i+len开始至串尾的子串（包括'\0'）向前移动len个字符
        this->element[j-len] = element[j];
    this->n -= len;
}
void MyString::remove(int i)                               //删除从第i（≥0）个字符开始至串尾的子串
{
    remove(i, this->n-i);
}


//3.3 串的模式匹配
//3.3.1   Brute-Force算法

//返回在当前串从start（0≤start<n）开始首个与模式串pattern匹配的子串序号，匹配失败时返回－1
/*int MyString::search(MyString &pattern, int start)
{
    int i=start, j=0;                                      //i、j分别为目标串和模式串当前字符下标
    int len=0;                                             //len统计字符比较次数
    while (i<this->n)
    {
        len++;
        if (this->element[i]==pattern.element[j])          //若当前两字符相等，则继续比较后续字符
        {   i++;
            j++;
        }
        else                                               //否则i、j回溯，进行下一次匹配
        {   i=i-j+1;                                       //目标串下标i退回到下个匹配子串序号
            j=0;                                           //模式串下标j退回到0
        }
        if (j==pattern.n)                                  //一次匹配结束，匹配成功
            return i-j;                                    //返回匹配子串序号
    }
//    cout<<"\n字符比较次数："<<len<<endl;
    return -1;                                             //匹配失败时返回－1
}*/

//2.  模式匹配应用
//（1）删除子串
void MyString::removeFirst(MyString &pattern)              //删除串中首个与pattern匹配的子串
{
    remove(search(pattern), pattern.n);                     //调用remove(i,n)函数
}
/*
void MyString::removeAll(MyString &pattern)                //删除串中所有与pattern匹配的子串，多次移动算法
{
    int start=0;
    do
    {
        start=search(pattern, start);
        remove(start, pattern.n);                          //调用remove(i,n)函数
    } while (start!=-1);
}*/

//删除串中所有与pattern匹配的子串。改进，字符移动一次算法
void MyString::removeAll(MyString &pattern)
{
    int i=this->search(pattern), k=i;                       //i为首个与pattern匹配子串序号
    while (k!=-1)                                          //每循环一次，删除一个匹配子串
    {
        int j=k+pattern.n;                                 //j为匹配子串之后的字符下标
        k=this->search(pattern, j);                         //k为从j开始查找的下个匹配子串序号
        while (k>0 && j<k || k<0 && j<=n)                  //将j～k-1之间的若干字符向前移动到i开始处
            this->element[i++] = element[j++];
//        cout<<*this<<endl;
    }
    if (i!=-1)
        this->n = i-1;                                     //设置目标串长度
}

//（2）替换子串
//将串中首个与pattern匹配的子串替换为str
void MyString::replaceFirst(MyString &pattern, MyString &str) 
{
    int start=search(pattern);  
    if (start!=-1)
    {
        remove(start, pattern.n);
        insert(start, str);
    }
}
//将串中所有与pattern匹配的子串替换为str
void MyString::replaceAll(MyString &pattern, MyString &str)
{
    int start=search(pattern);
    while (start!=-1)
    {
        remove(start, pattern.n);
        insert(start, str);
        start = search(pattern, start+str.n);         //从替换子串的下一个字符开始再次查找匹配子串
    }
}

//3.3.2   KMP模式匹配算法
//返回在当前串从start（0≤start<n）开始首个与模式串pattern匹配的子串序号，匹配失败时返回－1
int MyString::search(MyString &pattern, int start)
{
    int *next = new int[pattern.n];
    pattern.getNext(next);                                 //求得模式串的next数组
//        cout<<"next[]: ";
//        for (int h=0; h<pattern.n; h++)
//            cout<<next[h]<<"  ";

    int i=start, j=0;                                      //i、j为目标串、模式串当前字符序号
    int len=0;                                             //len统计字符比较次数
    while (i<this->n)
    {
        if (j!=-1) len++;
//            cout<<"\ni="<<i<<"  j="<<j<<"  n="<<n;
        if (j==-1 || this->element[i]==pattern.element[j])
        {
            i++;                                           //继续比较后续字符
            j++;
        }
        else
            j=next[j];                                     //确定模式串下次比较字符序号
        if (j==pattern.n)                                  //一趟比较结束，匹配成功
            return i-j;                                    //返回匹配的子串序号
    }
//        cout<<"\ncount="<<n<<endl;
    return -1;
}

/*
//获得模式串pattern的next数组（未改进），当前串*this为pattern
void MyString::getNext(int next[])
{
    next[0]=-1;
    int j=0, k=-1;
    while (j<this->n-1)                                    //next数组长度为pattern.n
        if (k==-1 || element[j]==element[k])
        {
            j++;
            k++;
            next[j]=k;                                     //有待改进，也可next[++j]=++k;
//            cout<<"j="<<j<<", k="<<k<<", next["<<j<<"]="<<k<<endl;
        }
        else
        {
//            cout<<"k=next["<<k<<"]=";
            k=next[k];
//            cout<<k<<endl;
        }
}*/

//获得模式串pattern的next数组（改进），当前串*this为pattern
void MyString::getNext(int next[])
{
    next[0]=-1;
    int j=0, k=-1;
    while (j<this->n-1)                                    //next数组长度为pattern.n
        if (k==-1 || element[j]==element[k])
        {
            j++;
            k++;
            if (element[j]!=element[k])                    //改进之处
                next[j]=k;
            else
                next[j]=next[k]; 
        }
        else
            k=next[k];
}

//习题解答第3章习3.2
void MyString::trim()                                      //删除串对象中的所有空格字符，O(n)
{
    int i=0;
    while (element[i]!=' ' && element[i]!='\0')            //寻找第1个空格
        i++;                                               //i记住第1个空格下标
    for (int j=i+1; element[j]!='\0'; j++)
        if (element[j]!=' ')
            element[i++] = element[j];                     //非空格字符向前移动到空格字符位置
    n = i;
    element[n] = '\0';
//    element[i] = element[j];                             //也行
}

//实验3
void MyString::uppercase()                                 //将串中的小写字母转换成大写字母
{
    for (int i=0; i<n; i++)
        if (element[i]>='a' && element[i]<='z')            //小写字母
            element[i] -= 'a'-'A';                         //转换成大写字母
}