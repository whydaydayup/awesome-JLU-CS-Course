
template <class T>
class Comparator                                           //比较器抽象类 
{
  public:
     virtual int compare(T obj1, T obj2)=0;                //提供T类的两个对象比较大小的规则，纯虚函数
};
