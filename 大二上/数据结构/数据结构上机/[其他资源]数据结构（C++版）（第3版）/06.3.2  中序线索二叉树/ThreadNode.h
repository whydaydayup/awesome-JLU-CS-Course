//《数据结构（C++版）（第3版）》 作者：叶核亚
//6.3   线索二叉树
//6.3.2   中序线索二叉树
//线索二叉树的二叉链表结点类

template <class T>
class ThreadNode                                           //线索二叉树的二叉链表结点类，T指定结点的元素类型
{
  public:
    T data;                                                //数据域，保存元素
    ThreadNode<T> *left,*right;                            //指针域，分别指向左、右孩子结点
    bool ltag,rtag;                                        //左、右线索标志，1个字节

    //构造结点，data指定元素，left、right指针分别指向左孩子和右孩子结点，默认空；
    //ltag、rtag分别表示左、右线索标志，默认0
    ThreadNode(T data, ThreadNode<T> *left=NULL, ThreadNode<T> *right=NULL, bool ltag=0, bool rtag=0)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->ltag = ltag;
        this->rtag = rtag;
    }
 };
/*
   //构造结点，指定元素、左孩子和右孩子结点
    ThreadNode(T data, ThreadNode<T> *left=NULL, int ltag=0, ThreadNode<T> *right=NULL, int rtag=0)
        :data(data),left(left),ltag(ltag),right(right),rtag(rtag)
    {}

    //构造结点，指定元素、左孩子和右孩子结点
    ThreadNode(T data, ThreadNode<T> *left=NULL, ThreadNode<T> *right=NULL)
        :data(data),left(left),right(right)
    {
        this->ltag = this->rtag = 0;
    }


*/