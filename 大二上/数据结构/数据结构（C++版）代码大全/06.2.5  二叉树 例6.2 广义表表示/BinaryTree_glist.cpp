//《数据结构（C++版）（第3版）》 作者：叶核亚
//【例6.2】 二叉树的广义表表示。

#include "BinaryTree.h"                                    //二叉树类

int main()
{
//    BinaryTree<MyString> bitree("AAA(BB,CC)");                 //创建二叉树
    BinaryTree<MyString> bitree("A(B(D(^,G),^),C(E,F(H,^)))");  //构造二叉树，图6.21所示二叉树的广义表表示
    bitree.printGenList(); 

    cout<<bitree;                                          //输出先根次序遍历序列（标明空子树）
    bitree.inOrder();                                      //输出中根次序遍历序列
    bitree.postOrder();                                    //输出后根次序遍历序列
//    bitree.traverseGList(); 
	system("pause");
    return 0;
}

/*
程序运行结果如下：
A(B(D(^,G),^),C(E,F(H,^)))

*/
/*
//以广义表表示创建一棵子树，子树根结点值是genlist[i]，返回根结点地址，递归算法
BinaryNode<char>* createGenList(char *genlist, int &i)
{
    BinaryNode<char> *p=NULL;
    if (genlist[i]>='A' && genlist[i]<='Z')                //以大写字母表示元素
    {
        p = new BinaryNode<char>(genlist[i++]);            //创建叶子结点
        if (genlist[i]=='(')
        {
            i++;                                           //跳过'('
            p->left = createGenList(genlist, i);           //创建左子树，先++i
            i++;                                           //跳过','
            p->right = createGenList(genlist, i);          //创建右子树
            i++;                                           //跳过')'
        }
    }
    if (genlist[i]=='^')
        i++;                                               //跳过'^'
    return p;
}

void createGenList(BinaryTree<char> &bitree, char genlist[]) //以广义表表示构造二叉树
{
    int i=0;
    bitree.root = createGenList(genlist, i);               //调用递归算法
}*/

//#include "SeqStack.h"                            //顺序栈
//#include "LinkedStack.h"                         //链式栈
/*??/*未完成 2012年3月29日
//非递归算法，使用栈
void createGList(BinaryTree<char> &bitree, char glist[])   //以广义表表示构造二叉树
{
    bitree.root = NULL;                                    //创建空二叉树
    SeqStack<BinaryNode<T>*> stack;              //创建一个空栈
    int i=0;
    BinaryNode<T> *p = root;
    while (p!=NULL || !stack.isEmpty())          //p非空或栈非空时
        if (p!=NULL)
        {
            cout<<p->data<<" ";                  //访问结点
            stack.push(p);                       //p结点入栈
            p = p->left;                         //进入左子树
        }
        else                                     //p为空且栈非空时
        {
            p = stack.pop();                     //p指向出栈结点
            p = p->right;                        //进入右子树
        }
    cout<<endl;
    int i=0;
    BinaryNode<char> *p=NULL;
    if (glist[i]>='A' && glist[i]<='Z')                    //大写字母
    {
        p = new BinaryNode<char>(glist[i++]);              //创建结点
        if (glist[i]=='(')
        {
            i++;                                           //跳过(
            p->left = createGList(glist, i);               //创建建立左子树，先++i
            i++;                                           //跳过,
            p->right = createGList(glist, i);              //创建建立右子树
            i++;                                           //跳过)
        }
    }
    if (glist[i]=='^')
        i++;                                               //跳过^
    return p;
}*/
