//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.4  Huffman树
//（2） 采用静态三叉链表存储Huffman树

class TriElement                                          //二叉树的静态三叉链表元素
{
  public:
    int data, parent, left, right;                        //数据域父母结点和左、右孩子结点下标

    TriElement(int data=0, int parent=-1, int left=-1, int right=-1)
    {
        this->data = data;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
    friend ostream& operator<<(ostream& out, TriElement &e) //输出
    {
        out<<"("<<e.data<<","<<e.parent<<","<<e.left<<","<<e.right<<")";
        return out;
    }
    bool isLeaf()                                          //判断是否叶子结点
    {
        return this->left==-1 && this->right==-1;
    }
    bool operator==(TriElement &e)                         //重载==运算符，比较是否相等
    {
        return this->data==e.data;
    }
};


/*未用？？
bool operator<(TriElement &e)                          //重载<运算符，比较大小
    {
        return this->data < e.data;
    }

    bool operator<(TriElement &e)                          //重载<运算符，比较大小
    {
        return this->parent==-1 && this->data < e.data;
    }

*/

