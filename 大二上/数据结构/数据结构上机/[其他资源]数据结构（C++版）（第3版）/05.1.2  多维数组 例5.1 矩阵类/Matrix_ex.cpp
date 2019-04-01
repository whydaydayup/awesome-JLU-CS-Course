//《数据结构（C++版）（第3版）》 作者：叶核亚
//5.1.2   多维数组
//【例5.1】  矩阵类。

#include "Matrix.h"                                        //矩阵类

int main()
{
    const int M=3, N=4; 
    Matrix mata(M, N, 0);                                  //构造矩阵对象，元素为0
    mata.set(0,0,1);
    mata.set(M-1,N-1,1);                                   //{1,0,0,0,0,1};

    int table[M*N]={1,2,3,4,5,6,7,8,9};
    Matrix matb(M, N, table);                              //构造矩阵对象，以一维数组（行主序）

//    int table[M*N]={1,2,3,4,5,6,7,8,9};
//    Matrix matb(M,N,&table2[0][0]);                        //构造矩阵，二维数组转换为一维数组（行主序）
    cout<<"A "<<mata<<"B "<<matb;

    //【思考题5-1】矩阵运算
    Matrix matc(M-1,N-1); 
    matc=mata+matb;                                        //先执行+，再执行赋值(扩容)
    cout<<"C=A+B，C "<<matc<<endl;
    mata+=matb;
    cout<<"A+=B，A "<<mata<<endl;
    cout<<"C==A？"<<(matc==mata)<<endl;
    cout<<"C==B？"<<(matc==matb)<<endl;

    Matrix matd(M,M,0);
    cout<<"D "<<matd;
    cout<<"D 是上三角矩阵？"<<matd.isUpTriangular()<<endl;
    cout<<"D 是对称矩阵？"<<matd.isSymmetric()<<endl<<endl;
    matd = mata.transpose();                               //赋值，复制，扩容
    cout<<"D = A的转置，D "<<matd;
    cout<<"D 是上三角矩阵？"<<matd.isUpTriangular()<<endl;
    cout<<"D 是对称矩阵？"<<matd.isSymmetric()<<endl;

    system("pause");
    return 0;
}

/*
程序运行结果如下:
A 矩阵（3×4）：
1  0  0  0  
0  1  0  0  
0  0  1  0  
B 矩阵（3×4）：
1  2  3  4  
5  6  7  8  
9  0  0  0  
A + B =矩阵（3×4）：
2  2  3  4  
5  7  7  8  
9  0  1  0  

A += B，A矩阵（3×4）：
2  2  3  4  
5  7  7  8  
9  0  1  0  

C深拷贝(B)，C==B？1
D 矩阵（3×3）：
0  0  0  
0  0  0  
0  0  0  
D 是上三角矩阵？1
D 是对称矩阵？1

D = A的转置，D矩阵（4×3）：
2  5  9  
2  7  0  
3  7  1  
4  8  0  
D 是上三角矩阵？0
D 是对称矩阵？0


*/
