//10.1.4   回溯法
//【例10.5】  预见算法解骑士游历问题。

#include "Matrix.h"                                        //矩阵类（见例5.1）

class Point                                                //棋盘一格坐标
{
  public: 
    int x,y;                                               //行、列坐标

    Point(int x, int y)                                    //构造函数
    {
        this->x=x;
        this->y=y;
    }
    friend ostream& operator<<(ostream &out, Point &p)     //输出
    {
        out<<"("<<p.x<<","<<p.y<<")";
        return out;
    } 
}; 


class HorseTravel                                          //预见算法解骑士游历问题
{
  private:
    int n;                                                 //棋盘大小
    Matrix chessboard;                                     //用矩阵表示棋盘并保存问题的一个解

    int select(Point p);                                   //选择p格到达下一格的方向
    Point go(Point p, int direction);                      //返回p格按direction方向的下一格
    bool isValid(Point p);                                 //判断p是否在棋盘内且未被占领过

  public:
    HorseTravel(int n, int x, int y);
};

HorseTravel::HorseTravel(int n, int x, int y)              //构造函数，n指定棋盘大小，x、y指定起始位置
    : chessboard(n,n,0)                                    //声明执行Matrix(int rows, int columns, int x)
{
    if (n<5 || n>8)                                        //控制棋盘大小为5～8
        throw out_of_range("参数n指定棋盘大小超出5～8范围");
    this->n = n;
    Point p(x,y);                                          //当前格从(x,y)开始游历
    int count=1, direction=1;                              //count记录步数，diretion表示8个方向
    while (count<=n*n && direction!=0)
    {
        chessboard.set(p.x, p.y, count);                   //设置p格的值为count
        cout<<"第"<<count<<"步  ";
        direction = select(p);                             //预见，选择一个方向
        if (direction==0 && count<n*n)
            cout<<"第"<<count<<"步无路可通!\n";
        else
        {   count++;                                       //步数加1
            p = go(p, direction);                          //前进一步 
        }
    }
}

//预见，为p位置试探下一步8个方向位置的可通路数，返回下一步可通路数最小值的方向
int HorseTravel::select(Point p)
{
    cout<<"当前位置: "<<p<<endl<<this->chessboard;         //输出棋盘所有元素
    cout<<"方向   下一位置   可通方向     可通路数"<<endl;
    int direction=0, minroad=8;
    for (int i=1; i<=8; i++)                               //试探p(x,y)的8个方向位置
    {
        int road=0;
        Point next1 = go(p,i);                             //next1是p按i方向的下一位置
        if (isValid(next1))                                //next1在棋盘内且未被访问过
        {
            cout<<"  "<<i<<"\t"<<next1<<"\t";
            for (int j=1; j<=8; j++)                       //统计next1(x,y)的可通路数road
            {
                Point next2 = go(next1,j);                 //next2是next1按j方向的下一位置
                if (isValid(next2))                        //next2在棋盘内且未被访问过
                {
                    road++;
                    cout<<j<<",";
                }
            }    
            if (road<minroad)
            {
                minroad=road;                              //minroad记载road的最小值
                direction=i;                               //direction记载road最小值的方向
            }
            cout<<"\t"<<road<<endl;
        }
    }
    cout<<"选定下一步方向  direction="<<direction<<"\r\n\n";
    return direction;                                      //返回下一步可通路数最小值的方向
}

bool HorseTravel::isValid(Point p)                         //判断p是否在棋盘内且未被访问过
{
    return (p.x>=0 && p.x<n && p.y>=0 && p.y<n && chessboard.get(p.x, p.y)==0);
}

Point HorseTravel::go(Point p, int direction)              //返回p按direction方向的下一位置，不改变p
{
    Point q(p);                                            //执行Point类的默认拷贝构造函数
    switch (direction)
    {
        case 1:  q.x-=2;  q.y++;   break; 
        case 2:  q.x--;   q.y+=2;  break; 
        case 3:  q.x++;   q.y+=2;  break; 
        case 4:  q.x+=2;  q.y++;   break; 
        case 5:  q.x+=2;  q.y--;   break; 
        case 6:  q.x++;   q.y-=2;  break; 
        case 7:  q.x--;   q.y-=2;  break; 
        case 8:  q.x-=2;  q.y--;   break; 
    }
    return q;
} 

int main()
{
//    HorseTravel horse(5,0,1);                         //不通
//    HorseTravel horse(8,0,0);                       //从(0,0)位置开始游历，显示中间结果
//    HorseTravel horse(8,4,3);

    int n=8, x=0, y=0;
//    cout<<"输入棋盘大小n、初始位置(x,y)：";
//    cin>>n>>x>>y;
    HorseTravel horse(n,x,y);

    system("pause");
    return 0;
}

/*
程序运行结果如下：
    HorseTravel horse(8,0,0);
   1  16  27  22   3  18  47  56
  26  23   2  17  46  57   4  19
  15  28  25  62  21  48  55  58
  24  35  30  45  60  63  20   5
  29  14  61  34  49  44  59  54
  36  31  38  41  64  53   6   9
  13  40  33  50  11   8  43  52
  32  37  12  39  42  51  10   7


    HorseTravel horse(5,0,1);                  //不通
第24步无路可通!
  18   1  14   7  16
  11   6  17   2  13
  22  19  12  15   8
   5  10  23  20   3
   0  21   4   9  24


    HorseTravel horse(8,4,3);
第64步  当前位置: (4,2)
  12  25  14  31  10  27  36  61
  15  32  11  26  35  62   9  28
  24  13  34  63  30  47  60  37
  33  16  23  56  59  38  29   8
  22  55  64   1  46  57  48  39
  17  52  19  58  49  42   7   4
  54  21  50  45   2   5  40  43
  51  18  53  20  41  44   3   6

 */  
