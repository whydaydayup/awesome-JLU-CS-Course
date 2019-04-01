//习7  构造图10.10所示带权无向图的最小生成树和最短路径。
 
public class WeightedUndiG1010
{
    public static void main(String args[])
    {
        String[] vertices={"A","B","C","D","E","F"};           //带权无向图的顶点集合
        Edge edges[]={new Edge(0,1,16),new Edge(0,2,18),new Edge(0,3,5), //边集合
                      new Edge(1,0,16),new Edge(1,2,7),new Edge(1,4,3),
                      new Edge(2,0,18),new Edge(2,1,7),new Edge(2,3,15),new Edge(2,4,26),new Edge(2,5,4),
                      new Edge(3,0,5),new Edge(3,2,15),new Edge(3,5,8), 
                      new Edge(4,1,3),new Edge(4,2,26),new Edge(4,5,6),
                      new Edge(5,2,4), new Edge(5,3,8),new Edge(5,4,6)};
//        AdjMatrixGraph<String> graph = new AdjMatrixGraph<String>(vertices, edges);
        AdjListGraph<String> graph = new AdjListGraph<String>(vertices, edges);
//        System.out.println("带权无向图，"+graph.toString());
//        graph.minSpanTree_prim();                          //构造带权图最小生成树的普里姆算法
        graph.shortestPath(0);               //顶点A的单源最短路径，Dijkstra算法
//        for (int i=0; i<graph.vertexCount(); i++)
//            graph.shortestPath(i);               //顶点vi的单源最短路径，Dijkstra算法

    }
}
/*
程序运行结果如下：
//Prim
mst数组：(0,1,16)(0,2,17)(0,3,5)(0,4,99999)(0,5,99999)
mst数组：(0,3,5)(3,2,15)(0,1,16)(0,4,99999)(3,5,8)
mst数组：(0,3,5)(3,5,8)(0,1,16)(5,4,6)(5,2,4)
mst数组：(0,3,5)(3,5,8)(5,2,4)(5,4,6)(2,1,7)
mst数组：(0,3,5)(3,5,8)(5,2,4)(5,4,6)(4,1,3)
mst数组：(0,3,5)(3,5,8)(5,2,4)(5,4,6)(4,1,3)
最小生成树的边集合：(0,3,5) (3,5,8) (5,2,4) (5,4,6) (4,1,3) ，最小代价为26

//D

vset数组{1,0,0,0,0,0}	path数组{-1,0,0,0,-1,-1}	dist数组{0,16,18,5,∞,∞}
vset数组{1,0,0,1,0,0}	path数组{-1,0,0,0,-1,3}	dist数组{0,16,18,5,∞,13}
vset数组{1,0,0,1,0,1}	path数组{-1,0,5,0,5,3}	dist数组{0,16,17,5,19,13}
vset数组{1,1,0,1,0,1}	path数组{-1,0,5,0,5,3}	dist数组{0,16,17,5,19,13}
vset数组{1,1,1,1,0,1}	path数组{-1,0,5,0,5,3}	dist数组{0,16,17,5,19,13}
vset数组{1,1,1,1,1,1}	path数组{-1,0,5,0,5,3}	dist数组{0,16,17,5,19,13}
从顶点A到其他顶点的最短路径如下：
(A,B)长度为 16
(A,D,F,C)长度为 17
(A,D)长度为 5
(A,D,F,E)长度为 19
(A,D,F)长度为 13

*/

/*
程序运行结果如下：

*/        
/*
*/ 

