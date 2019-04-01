//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例4.1】 检查表达式中圆括号是否匹配。

#include "MyString.h"                                      //字符串类
#include "SeqStack.h"                                      //顺序栈类
//#include "LinkedStack.h"                                 //链式栈类

//检查expstr表达式中的左右圆括号是否匹配，若匹配，则没有输出；否则输出错误信息
void printError(MyString &expstr)
{
    SeqStack<char> stack;                                  //创建空栈
//    LinkedStack<char> stack;                               //创建空栈
    for (int i=0; i<expstr.count(); i++)
        switch (expstr[i])
        {
            case '(': stack.push(expstr[i]);               //左括号入栈
             //         cout<<stack;
                      break;
            case ')': if (stack.empty() || stack.pop()!='(')  //遇见右括号时，出栈，判断出栈字符是否为左括号
                          cout<<"期望(";
                //      cout<<stack;
        }
    if (!stack.empty())
        cout<<"期望)";
    cout<<endl;
}

int main()
{
    MyString expstr[]={"((1+2)*(3+4))()", "((1+2)*(3+4))(", "((1+2)*(3+4)))"}; 
    for (int i=0; i<3; i++)
    {
        cout<<expstr[i]<<"，";
        printError(expstr[i]);
    }

    system("pause");
    return 0;
}
/*
程序运行结果如下：
((1+2)*(3+4))，   
((1+2)*(3+4))(，  期望)
((1+2)*(3+4)))，  期望(

*/

/*
/判断expstr表达式中的圆括号是否匹配，返回编译错误信息
char* isValid(char *expstr)
{
    SeqStack<char> stack;                                  //创建空栈
    for (int i=0; expstr[i]!='\0'; i++)
        switch (expstr[i])
        {
            case '(': stack.push(expstr[i]);               //左括号入栈
                      break;
            case ')': if (stack.empty() || stack.pop()!='(')  //遇见右括号时，出栈
                          return "期望(";                  //判断出栈字符是否为左括号
        }

//    cout<<stack;
    if (stack.empty())
        return "";                                         //返回空串表示没有错误
    return "期望)";
}*/