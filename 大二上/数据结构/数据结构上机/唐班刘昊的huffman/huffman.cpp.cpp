#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
using namespace::std;
int total = 0,time = 0;
char code[25];
int last = 0;
char hufcode[400][25];
FILE *p, *q, *q1;



void CodeInitial()
{
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            hufcode[i][j] = '\0';
        }
    }
    for (int k = 0; k < 25; k++)
    {
        code[k] = '\0';
    }
}


struct Node
{
    char data;
    int weight;
    Node *left,*right;
    Node(){data = 0;weight = 0;left = right = NULL;};
}TextNode[258];

Node *lNode,*rNode;


class HufTree
{
public:
    Node *root;
    HufTree(){root = NULL;};
    // needs to combine n-1 times
    void HufCombine()
    {
        Node * q = new Node;
        lNode = new Node;
        rNode = new Node;
        *lNode = TextNode[time];
        *rNode = TextNode[time+1];
        q->left = lNode;
        q->right = rNode;

        q->weight = lNode->weight+rNode->weight;
        time++;
        TextNode[time] = *q;
        for (int i = time; i < total-1; i++)
        {
            if (TextNode[i].weight>TextNode[i+1].weight)
            {
                struct Node temp;
                temp = TextNode[i];
                TextNode[i] = TextNode[i+1];
                TextNode[i+1] = temp;
            }
            else
                break;
        }
    }
    void InitialHufTree()
    {
        for (int i = 0; i < total-1; i++)
            HufCombine();
        root = &TextNode[total-1];
    }
    void PreOrder(Node *p,int i)
    {
        if (p->left!=NULL)
        {
            code[i] = '0';
            i++;
            PreOrder(p->left,i);
            code[i] = '\0';
            i--;
        }
        if (p->right!=NULL)
        {
            code[i] = '1';
            i++;
            PreOrder(p->right,i);
            code[i] = '\0';
            i--;
        }
        if (p->left==NULL&&p->right==NULL)
        {
            strcpy(hufcode[(p->data)],code);
            cout<<p->data<<" "<<hufcode[p->data]<<endl;
        }
    }
};

void decode(HufTree h)
{
    q1 = fopen("textdecode.txt","w");
    q = fopen("uncompress2.txt","r");
    Node *s = h.root;
    while (!feof(q))
    {
        char c = fgetc(q);
        if (c=='0')
        {
            if (s->left!=NULL)s = s->left;
            else
            {
                fputc(s->data,q1);
                fseek(q,-1,SEEK_CUR);
                s = h.root;
            }
        }
        else if (c=='1')
        {
            if (s->right!=NULL)s = s->right;
            else
            {
                fputc(s->data,q1);
                fseek(q,-1,SEEK_CUR);
                s = h.root;
            }
        }
    }
    fclose(q1);
    fclose(q);
}
void CompressHuf()
{
    q = fopen("uncompress.txt","r");
    q1 = fopen("harry.huf","w");
    char com[10];
    bool check = true;
    while (fgets(com,8,q))
    {
        int num = 0;
        for (int i = 0; i < 7; i++)
        {
            if (com[i]=='\0')
            {
                check = false;
                fprintf(q1,"%c%d%c\n",2,i,num+33);
                break;
            }
            num *= 2;
            if (com[i]=='1')num++;
        }
        if (check) fprintf(q1,"%c",num+33);
    }
    fclose(q);
    fclose(q1);
}
void DeCompressHuf()
{
    q1 = fopen("harry.huf","r");
    q = fopen("uncompress2.txt","w");
    char c;
    int num[10];
    while (c = fgetc(q1))
    {
        if (c==2)
        {
            int l = fgetc(q1) - 48;
            int r = fgetc(q1) - 33;
            for (int i = 0; i < l; i++)
            {
                num[l-1-i] = r % 2;
                r /= 2;
            }
            for (int i = 0; i < l; i++)
                fputc(num[i]+48,q);
            break;
        }

        int m = (int(c) - 33 + 256) % 256;
        for (int i = 0; i < 7; i++)
        {
            num[6-i] = m % 2;
            m /= 2;
        }
        for (int i = 0; i < 7; i++)
            fputc(num[i]+48,q);
    }
    fclose(q);
    fclose(q1);
}
int main()
{
    CodeInitial();
    p = fopen("test.txt","r");
    if (p==NULL)
    {
        cout<<"Open failed!"<<endl;
        exit(0);
    }
    bool newchar;
    while (!feof(p))
    {
        newchar = true;
        char c = fgetc(p);
        for (int i = 0; i < total; i++)
        {
            if (c==TextNode[i].data)
            {
                TextNode[i].weight++;
                newchar = false;
                break;
            }
        }
        if (newchar)
        {
            TextNode[total].data = c;
            TextNode[total].weight++;
            total++;
        }
    }
    struct Node temp;
    for (int i = 0; i < total-1; i++)
    {
        for (int j = i+1; j < total; j++)
        {
            if (TextNode[i].weight>TextNode[j].weight)
            {
                temp = TextNode[i];
                TextNode[i] = TextNode[j];
                TextNode[j] = temp;
            }
        }
    }
    HufTree h;
    h.InitialHufTree();
    h.PreOrder(h.root,0);
    // put the 01 code into textout.txt
    fseek(p,0,SEEK_SET);
    q = fopen("uncompress.txt","w");
    while (!feof(p))
    {
        char c = fgetc(p);
        for (int i = 0; i < strlen(hufcode[c]);i++)
        {
            fputc(hufcode[c][i],q);
        }
    }
    fclose(p);
    fclose(q);
    CompressHuf();
    DeCompressHuf();
    decode(h);
    return 0;
}
