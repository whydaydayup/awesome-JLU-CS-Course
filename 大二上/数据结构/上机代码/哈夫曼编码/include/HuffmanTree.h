#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <stack>

using namespace std;

class Node
{
public:
    char data;
    int weight;
    Node* Left;
    Node* Right;
    string s;
    Node(){Left=NULL;Right=NULL;data='\0';s="";}
    Node(char c,int w){Left=NULL;Right=NULL;data=c;weight=w;s="";}
};

class HuffmanTree
{
    public:
        HuffmanTree();
        virtual ~HuffmanTree();
        int num;
        int ContextNum;
        Node** CharArr;
        Node** SortedArr;
        Node** ContextArr;
        Node* root;
        char HuffCode[128][50];
        string HuffString;
        int textSize;
        void Init(char* d,int* w,int n);
        void Display();
        void DisplaySorted();
        void PreOrder(Node* p,string str);
        Node* Find(char c);
        void Compress(char* c,int size);
        void Decompress();
        void OutCode(Node* p);
        static string pre;
        void writePre();
        Node* ReCreate(ifstream* infile);
        void ReReCreate();
    protected:

    private:
};

#endif // HUFFMANTREE_H
