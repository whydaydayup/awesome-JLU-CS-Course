//《数据结构（C++版）（第3版）》 作者：叶核亚
//07.5.2  每对顶点间的最短路径（Floyd算法）
 
#include "MatrixGraph.h"
 
int main()
{
    char vertices[]="ABCD";                                //带权有向图G5的顶点集合
    Triple edges[]={Triple(0,1,16), Triple(0,2,57), Triple(0,3,65),
                     Triple(1,2,11), Triple(1,3,43), 
                     Triple(2,0,39), Triple(2,3,9), 
                     Triple(3,0,22)};                     //G5的出边集合
    MatrixGraph<char> graph(vertices, 4, edges, 8);
    cout<<"带权有向图G5，"<<graph<<endl;
/*
    cout<<"Dijkstra算法，单源最短路径\n";
    for (int i=0; i<graph.vertexCount(); i++)             //每对顶点之间的最短路径
        graph.shortestPathFrom(i);                             //顶点vi的单源最短路径，Dijkstra算法
    cout<<endl;
*/
    cout<<"Floyd算法，每对顶点间的最短路径\n";
    graph.shortestPath();                                  //调用Floyd算法求带权图每对顶点间的最短路径

    system("pause");
    return 0;
}


/*
程序运行结果如下：
带权有向图G5，顶点集合：(A, B, C, D)
邻接矩阵：
     0    16    57    65
    ∞     0    11    43
    39    ∞     0     9
    22    ∞    ∞     0

dist矩阵（4×4）：
     0    16    57    65
  9999     0    11    43
    39  9999     0     9
    22  9999  9999     0
path矩阵（4×4）：
    -1     0     0     0
    -1    -1     1     1
     2    -1    -1     2
     3    -1    -1    -1

用顶点A作为其他路径的经过顶点，dist矩阵（4×4）：
     0    16    57    65
  9999     0    11    43
    39    55     0     9
    22    38    79     0
path矩阵（4×4）：
    -1     0     0     0
    -1    -1     1     1
     2     0    -1     2
     3     0     0    -1

用顶点B作为其他路径的经过顶点，dist矩阵（4×4）：
     0    16    27    59
  9999     0    11    43
    39    55     0     9
    22    38    49     0
path矩阵（4×4）：
    -1     0     1     1
    -1    -1     1     1
     2     0    -1     2
     3     0     1    -1

用顶点C作为其他路径的经过顶点，dist矩阵（4×4）：
     0    16    27    36
    50     0    11    20
    39    55     0     9
    22    38    49     0
path矩阵（4×4）：
    -1     0     1     2
     2    -1     1     2
     2     0    -1     2
     3     0     1    -1

用顶点D作为其他路径的经过顶点，dist矩阵（4×4）：
     0    16    27    36
    42     0    11    20
    31    47     0     9
    22    38    49     0
path矩阵（4×4）：
    -1     0     1     2
     3    -1     1     2
     3     0    -1     2
     3     0     1    -1

每对顶点间的最短路径如下：
(A,B)长度16	        (A,B,C)长度27	    (A,B,C,D)长度36	
(B,C,D,A)长度42	    (B,C)长度11	        (B,C,D)长度20	
(C,D,A)长度31	    (C,D,A,B)长度47	    (C,D)长度9	
(D,A)长度22	        (D,A,B)长度38	    (D,A,B,C)长度49	


*/

