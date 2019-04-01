//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.5.3   树的父母孩子兄弟链表实现
//【例6.4】  以横向凹入表示构造一棵城市树。

#include "Tree.h"                                          //树的孩子兄弟链表实现的树类

int main()
{
    MyString prelist[]={"A","\tB","\t\tE","\t\tF","\tC","\tD","\t\tG"};  //图6.40
    Tree<MyString> tree1(prelist, 7); 
    cout<<tree1;

    //例6.6
    MyString china[]={"中国","\t北京","\t上海","\t江苏","\t\t南京","\t\t\t江宁","\t\t苏州","\t\t无锡"};
                                                            //MyString有char*类型的构造函数
    Tree<MyString> tree(china, 8);                         //以树的横向凹入表示法构造树（森林）
    cout<<tree;                                            //输出树的横向凹入表示字符串


/*    //习题6
    char* zhejian[]={"浙江","\t杭州","\t宁波","\t温州","广东","\t广州"};
    Tree<MyString> zjtree;
    create(zjtree, zhejian, 6);  
    cout<<zjtree;                                            //输出树的横向凹入表示字符串
// ？？   tree.insertChild(tree.root, zjtree, 0);                 //插入最后一棵子树

/*
    char* korea[]={"韩国","\t首尔","\t釜山","\t济洲"};
    char* usa[]={"美国","\t华盛顿","\t纽约州","\t\t纽约"};
    Tree<MyString> koreatree, usatree;
    create(koreatree, korea, 4);
    create(usatree, usa, 4);

    TreeNode<MyString> *California  = usatree.insertLastChild(usatree.root,"加利福尼亚");
    usatree.insertChild(California, "洛杉矶", 2);
    TreeNode<MyString> *Nevada = tree.insertLastSibling(California,"内华达");
    usatree.insertChild(Nevada, "拉斯维加斯",3);

    tree.insertChild(tree.getLastSibling(tree.root), koreatree, 1); //插入子树
    tree.insertSibling(tree.root, usatree, 3);
*/

//    cout<<tree;                                            //输出树的横向凹入表示字符串
    cout<<"共"<<tree.count()<<"个结点，高度为"<<tree.height()<<endl;
    cout<<"\""<<tree.root->data<<"\"有"<<tree.childCount(tree.root)<<"个孩子结点\n";
    tree.printGenList(); 


    system("pause");
    return 0;
}
/*
程序运行结果如下：
中国
	北京
	上海
	江苏
		南京
			江宁
		苏州
		无锡
			锡山
	浙江
		杭州
		宁波
		温州
	广东
		广州
韩国
	首尔
日本
	东京
共19个结点，高度为4
中国有5个孩子结点



中国
	北京
	上海
	江苏
		南京
			江宁
		苏州
		无锡
			锡山
	浙江
		杭州
		宁波
		温州
	广东
		广州
韩国
	首尔
日本
	东京
共19个结点，高度为4
中国有5个孩子结点
撤销树: 江宁 锡山 无锡 苏州 南京 温州 宁波 杭州 广州 广东 浙江 江苏 上海 北京 首尔 东京 日本 韩国 中国 

*/
/*
        if (tree.root->sibling==NULL)                      //根结点没有兄弟时
            insert(tree, tree.root, prelist[i]);           //将prelist[i]插入到tree树以tree.root为根的子树中
        else                                               //插入到根最后一个兄弟的子树中
            insert(tree, tree.getLastSibling(tree.root), prelist[i]);
}

void insert(Tree<char*> &tree, TreeNode<char*> *p, char *str)
{ 
    if (*str!='\t')                                        //str没有\t前缀时
        tree.insertLastSibling(p, str);                    //插入str作为p的最后一个兄弟
    else                                                   //str有\t前缀时，插入str到p的最后一棵子树中
    {
        str++;                                             //去除str串中一个前缀'\t'
        if (p->child==NULL)                   	           //p没有孩子时
            p->child = new TreeNode<char*>(str);           //插入str作为p的第一个孩子
        else
            insert(tree, tree.getLastChild(p), str);       //插入str到p的最后一棵子树中，递归调用
    }
}*/

/*
//在tree森林最后一棵树中插入以str横向凹入表示的一个结点，结点值去除了str所有\t前缀，非递归算法
void insert(Tree<char*> &tree, char *str)
{ 
    if (tree.root==NULL) 
        tree.root = new TreeNode<char*>(str);
    else
    {
        TreeNode<char*> *p=tree.getLastSibling(tree.root); //p到达根结点的最后一个兄弟
        if (p==NULL)
            p = tree.root;                   	           //p没有兄弟时指向根，选择森林中最后一棵树
        if (*str!='\t')
            p->sibling = new TreeNode<char*>(str);         //没有\t前缀时，插入str作为p的最后一个兄弟
        else                               	               //有\t前缀时，插入str到p的最后一棵子树中
        {
            str++;                                         //去除str串中一个前缀'\t'
            while (*str=='\t')                             //字符串以\t开头
            {
                TreeNode<String> lastChild=tree.getLastChild(p);    	//获得p的最后一个孩子
                if (lastChild!=null)
                    p = lastChild;
                str = str.substring(1);                      	//去除str串中一个前缀'\t'
                
				q = tree.getLastChild(p);        //q到达p结点的最后一个孩子
                if (q!=NULL)
                p = q;
                str++;
            }
            tree.insertLastChild(p, str);          //插入str作为p结点的最后一个孩子
        }
        else
    }
}
    public static void insert(Tree<String> tree, String str)
    {
=       {   str = str.substring(1);                            	//
            while (str.charAt(0)=='\t')                       	//字符串以\t开头
           }
            tree.insertLastChild(p, str);                        //插入str作为p的最后一个孩子
        }
    }*/


