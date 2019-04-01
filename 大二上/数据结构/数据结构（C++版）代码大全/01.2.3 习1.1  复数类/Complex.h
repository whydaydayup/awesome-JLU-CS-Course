//《数据结构（C++版）（第3版）习题解答与实验指导》 作者：叶核亚
//习1.1 复数类

#include <iostream>
using namespace std;
class Complex                                              //复数类
{
  private:
    double real, imag;                                     //实部，虚部imaginary

  public:
    Complex(double real=0,double imag=0);                  //构造函数，提供无参构造函数
    Complex(const Complex&);                               //默认拷贝构造函数
    ~Complex();                                            //默认析构函数

    void set(double real, double imag);                    //设置复数对象的成员变量
    friend ostream& operator<<(ostream&, const Complex&);  //重载输出流运算符
    Complex& operator=(const Complex&);                    //默认赋值运算
    Complex& operator+=(const Complex&);                   //加赋值
    Complex operator+(const Complex&) const;               //对象相加，返回新创建对象
    bool operator==(const Complex&) const;                 //比较当前对象与对象c是否相等
    bool operator!=(const Complex&) const;                 //比较对象是否相等
};

Complex::Complex(double real, double imag)                 //构造函数，两个参数可缺省
{
    this->set(real, imag);
//    this->real = real;
//    this->imag = imag;
}
Complex::~Complex()                                        //默认析构函数
{
    cout<<"析构~Complex() "<<*this;
}

void Complex::set(double real, double imag)                //设置复数对象的成员变量
{
    this->real = real;
    this->imag = imag;
}

Complex& Complex::operator=(const Complex &c)              //默认赋值运算，*this=c
{
    this->set(c.real, c.imag);
    return *this;
}
Complex::Complex(const Complex &c)                         //默认拷贝构造函数，复制对象，重载
{
//    this->set(c.real, c.imag);                 //也可
//    this->real = c.real;                       //也可
//    this->imag = c.imag;
	*this=c;                                               //执行赋值运算
}

ostream& operator<<(ostream &out, const Complex &c)        //重载输出流运算符，cout<<c
{
    out<<"("<<c.real<<"+"<<c.imag<<"i)";
    return out;
}

Complex& Complex::operator+=(const Complex &c)             //加赋值，*this+=c，改变当前对象。-=算法类似
{
 //   this->real += c.real;
 //   this->imag += c.imag;
    this->set(this->real+c.real, this->imag+c.imag);
    return *this;
}
/*
Complex Complex::operator+(const Complex &c) const         //对象相加，*this+c，返回新创建对象，没有改变当前对象
{ 
    return Complex(this->real+c.real, this->imag+c.imag);  //返回对象，没有执行拷贝构造函数
//    return new Complex(this->real+c.real, this->imag+c.imag); //编译错，不能将参数 1 从“Complex *”转换为“double”
}*/
Complex Complex::operator+(const Complex &c) const         //对象相加，*this+c，函数声明返回对象，调用+=算法
{ 
    Complex temp(*this);                                   //执行拷贝构造函数
    temp+=c;
    return temp;                                           //返回对象，先执行拷贝构造函数，复制局部对象。再析构temp
}

bool Complex::operator==(const Complex &c) const           //比较当前对象与对象c是否相等，*this==c
{
    return this->real==c.real && this->imag==c.imag;
}
bool Complex::operator!=(const Complex &c) const           //比较当前对象与对象c是否相等，*this!=c
{
    return !(*this==c);
}

/*
bool Complex::operator==(const Complex &c) const           //比较当前对象与对象c是否相等，*this==c
{
    return this==&c                                        //当两个对象引用同一个实例时
           || this->real==c.real && this->imag==c.imag;
}*/