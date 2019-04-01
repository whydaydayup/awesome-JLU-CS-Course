//《数据结构（C++版）（第3版）》 作者：叶核亚

#include "TermX.h"
class TermXY : public TermX                                //二元多项式的一项
{
//  protected:
  public:
    int yexp;                                              //y指数
    TermXY(double coef=0,int xexp=0,int yexp=0);           //构造一项
    friend ostream& operator<<(ostream& out, TermXY& termxy); //输出，重载输出流运算符<<
//    bool operator==(TermXY& termxy);                       //按x指数和y指数比较两项是否相等
//    bool operator!=(TermXY& termxy);
    bool operator<(TermXY& termxy);                        //按x指数和y指数比较两项大小
    bool operator<=(TermXY& termxy);
    bool operator>(TermXY& termxy);
    bool operator>=(TermXY& termxy);

    TermXY(TermX term) :  TermX(term)           //构造一项
    {
        yexp=0;
    }
/*    bool operator==(TermX& termx)                       //按x指数和y指数比较两项是否相等
    {
        return TermX::operator==(termx);
    }*/
};
