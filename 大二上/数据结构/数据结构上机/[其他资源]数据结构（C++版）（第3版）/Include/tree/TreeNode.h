//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.5.3   树的父母孩子兄弟链表实现
//树的父母孩子兄弟链表结点类

template <class T>
class TreeNode                                             //树的父母孩子兄弟链表结点类，T指定结点的元素类型
{
  public:
    T data;                                                //数据域
    TreeNode<T> *parent, *child, *sibling;                 //指针域，分别指向父母、孩子、兄弟结点

    //构造结点，参数分别指定元素、父母结点、孩子结点和兄弟结点
    TreeNode(T data, TreeNode<T> *parent=NULL, TreeNode<T> *child=NULL, TreeNode<T> *sibling=NULL)
    { 
        this->data = data;
        this->parent = parent;
        this->child = child;
        this->sibling = sibling;
    }
};
