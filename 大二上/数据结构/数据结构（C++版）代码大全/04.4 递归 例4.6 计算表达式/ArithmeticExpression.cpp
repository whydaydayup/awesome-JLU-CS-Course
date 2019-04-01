//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.6】 用递归算法计算算术表达式的值。

#include "MyString.h"                                      //字符串类（见第3章）

class ArithmeticExpression                                 //算术表达式（整数、不包括位运算）
{
  private:
    MyString expstr;                                       //中缀算术表达式字符串
    int index;                                             //当前字符序号

    int term();                                            //计算〈项〉
    int factor();                                          //计算〈因子〉
    int constant();                                        //计算〈常数〉

  public:
    ArithmeticExpression(MyString expstr="");              //由字符串构造算术表达式
    int intValue();                                        //计算算术表达式，返回整数值
};

ArithmeticExpression::ArithmeticExpression(MyString expstr)//构造算术表达式，expstr指定中缀表达式字符串
{
    this->expstr = expstr;
    this->index = 0;
}

//计算从index开始的一个（子）算术表达式，返回整数值，其中进行多〈项〉加减运算
int ArithmeticExpression::intValue()
{
    int value1 = term();                                   //计算〈项〉获得操作数1
    while (this->index < expstr.count())                   //进行多〈项〉的加减运算
    {
        char ch = expstr[this->index];
        if (ch=='+' || ch=='-')
        {   this->index++;
            int value2 = term();                           //计算〈项〉获得操作数2
            //以下进行两〈项〉的加减运算，ch记得出现在value2之前的运算符
            switch (ch)
            {   case '+': value1 += value2; break;         //value1存储运算结果
                case '-': value1 -= value2; break;
            }                
        }
        else
        {
//            cout<<"expstr["<<index<<"]="<<expstr[index]<<endl;
            break;                                         //遇到')'时，〈项〉结束
        }
    }
    return value1;  
}

int ArithmeticExpression::term()       //计算从index开始的一〈项〉，其中进行多〈因子〉的乘除运算
{
    int value1 = factor();                                 //计算〈因子〉获得操作数1
    while (this->index < expstr.count())                   //进行多〈因子〉的乘除运算
    {
        char ch = expstr[this->index];
        if (ch=='*' || ch=='/' || ch=='%')
        {   this->index++;
            int value2 = factor();                         //计算〈因子〉获得操作数2
            switch (ch)                                    //两〈因子〉进行乘除运算
            {   case '*': value1 *= value2; break;
                case '/': value1 /= value2; break;
                case '%': value1 %= value2; break;
            }                
        }
        else 
        {
//            cout<<"expstr["<<index<<"]="<<expstr[index]<<endl;
            break;                                         //遇到')'、'+'、'-'时，〈因子〉结束
        }
    }
    return value1;  
}

//计算从index开始的一个〈因子〉，其中包含以()为界的子表达式，间接递归调用
int ArithmeticExpression::factor()
{
    if (expstr[this->index]=='(')
    {   this->index++;                                     //跳过'('
        int value = intValue();                            //计算()括号内的子表达式，间接递归调用
        this->index++;                                     //跳过')'
        return value;
    }
    return constant(); 
}

int ArithmeticExpression::constant()                       //计算从index开始的一个〈常数〉
{
    if (this->index < expstr.count())
    {
        char ch=expstr[this->index];
        int sign=1;
        if (ch=='+' || ch=='-')
        {    sign = ch=='-' ? -1 : 1;                      //符号位，记住正负数标记 
             this->index++;                                //跳过符号位
        }
        int value=0;
        while (this->index < expstr.count() && expstr[index]>='0' && expstr[index]<='9')
            value = value*10+expstr[this->index++]-'0';    //value记住当前获得的整数值
        if (value!=0)
            return value*sign;                             //返回有符号的整数值
    }
//   throw Exception("\""+expstr.substring(this->index-1)+"\"不能转换成整数");
}
  
int main()
{
    MyString expstr="123+10*(50-45+15)/((35-25)*2-10)+(-11)";
    cout<<expstr<<"="<<ArithmeticExpression(expstr).intValue()<<endl;

    MyString expstrs[]={"123","+123","-123","(-123)",
                     "1+-2","1-+2","-1+((-2))","1+2+3","1*2*3","-1*-2*-3"};
    for (int i=0; i<10; i++)
        cout<<expstrs[i]<<"="<<ArithmeticExpression(expstrs[i]).intValue()<<endl;

    system("pause");
    return 0;
}    

/*
程序运行结果如下：
123+10*(50-45+15)/((35-25)*2-10)+(-11)=132
123=123
+123=123
-123=-123
(-123)=-123
1+-2=-1
1-+2=-1
-1+((-2))=-3
1+2+3=6
1*2*3=6
-1*-2*-3=-6

*/
