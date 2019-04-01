//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.2】 使用栈计算表达式的值。

#include "MyString.h"                                      //字符串类
#include "SeqStack.h"                                      //顺序栈类
#include "LinkedStack.h"                                   //链式栈类

//将expstr表示的中缀表达式转换为后缀表达式，返回MyString对象
MyString toPostfix(MyString &expstr)
{
//    SeqStack<char> stack;                                  //运算符栈
    LinkedStack<char> stack;
    MyString postfix("", expstr.count()*2);                //后缀表达式字符串
    int i=0;
    while (i<expstr.count())
        switch (expstr[i])
        {
            case '+':                                      //遇到＋、－运算符，与栈顶元素比较
            case '-': while (!stack.empty() && stack.get()!='(')
                          postfix += stack.pop();          //出栈字符连接到后缀表达式串
                      stack.push(expstr[i++]);             //当前运算符入栈
                      break;
            case '*':                                      //遇到*、/运算符
            case '/': while (!stack.empty() && (stack.get()=='*' || stack.get()=='/'))
                          postfix += stack.pop();
                      stack.push(expstr[i++]);
                      break;
            case '(': stack.push(expstr[i++]);             //遇到左括号，入栈
                      break;
            case ')': { char out = stack.pop();             //遇到右括号，出栈
                      while (!stack.empty() && out!='(') //判断出栈字符是否为左括号
                      {   postfix += out;
                          out = stack.pop();
                      }
                      i++;
                      break;}
            default:                                       //遇到数字时，加入到后缀表达式
                      while (i<expstr.count() && expstr[i]>='0' && expstr[i]<='9')
                          postfix += expstr[i++];     
                      postfix += ' ';                      //后缀表达式字符串中数值之间以空格分隔
        }
    while (!stack.empty())
        postfix += stack.pop();
    return postfix;                                        //返回MyString对象，执行MyString的拷贝构造函数
}

int toValue(MyString &postfix)                             //计算后缀表达式的值
{
    SeqStack<int> stack;                                   //操作数栈
//    LinkedStack<int> stack;                                //操作数栈
    int value=0;
    for (int i=0; i<postfix.count(); i++)                  //逐个检查后缀表达式中的字符
        if (postfix[i]>='0' && postfix[i]<='9')            //遇到数字字符
        {
            value=0;
            while (postfix[i]!=' ')                        //整数字符串转化为整数数值
                value = value*10 + postfix[i++]-'0';
            stack.push(value);                             //操作数入栈
        }
        else
            if (postfix[i]!=' ')
            {
                int y = stack.pop();                       //出栈两个操作数
                int x = stack.pop();
                switch (postfix[i])                        //根据运算符分别计算
                {
                    case '+': value = x+y;  break;
                    case '-': value = x-y;  break;
                    case '*': value = x*y;  break;
                    case '/': value = x/y;  break;         //整除
                }
                stack.push(value);                         //运算结果入栈
            } 
    return stack.pop();                                    //返回运算结果
}

int main()
{
//    MyString expstr("1+2*(3-4)+5");                              //图4.7
//    MyString expstr("121+10*(53-49+20)/((35-25)*2+10)+11");      //例4.2
    MyString expstr="121+10*(53-49+20)/((35-25)*2+10)+11";         //例4.2，也可， MyString必须重载=(char*)
//    MyString expstr("121+10*(53-49+20)/((35-25)*2+10)+(-11)");   //例4.2，没有识别正负号

    MyString postfix = toPostfix(expstr);                  //执行MyString的=，深拷贝 
    cout<<"expstr=  "<<expstr<<endl;
    cout<<"postfix= "<<postfix<<endl;
    cout<<"value=   "<<toValue(postfix)<<endl;

    system("pause");
    return 0;
}
/*
程序运行结果如下：
expstr=  121+10*(53-49+20)/((35-25)*2+10)+11
postfix= 121 10 53 49 -20 +*35 25 -2 *10 +/+11 +
value=   140

*/
