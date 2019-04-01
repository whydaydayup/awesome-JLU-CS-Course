//《数据结构（C++版）（第3版）》 作者：叶核亚
//2.4.1   一元多项式的表示及运算
//项类，一元多项式的一项

#include <iostream>
using namespace std;
#include <math.h>

class TermX                                                //项类，一元多项式的一项
{
//  protected:
  public:
    double coef;                                           //系数
    int xexp;                                              //x变量指数，可为正、0

    TermX(double coef=0, int xexp=0);                      //构造一项，指定默认值
//    TermX(char* termstr);                                  //以“系数x^指数”形式字符串构造一项
    friend ostream& operator<<(ostream& out, const TermX& term); //重载<<输出流运算符
    bool operator==(TermX& term);                          //按x指数比较两项是否相等，重载运算符==
    bool operator!=(TermX& term);
    bool operator<(TermX& term);                           //按x指数比较两项大小，重载<运算符
    bool operator<=(TermX& term);
    bool operator>(TermX& term);
    bool operator>=(TermX& term);
    void operator+=(TermX& term);                          //加法，重载＋=运算符，约定两元素相加规则
//    TermX operator+(TermX& term);                          //加法，重载＋运算符，返回对象
    bool removable();                                      //约定删除元素条件
};
