#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "HuffmanTree.h"

using namespace std;

HuffmanTree::HuffmanTree()
{
    num=0;
    CharArr=NULL;
}

HuffmanTree::~HuffmanTree()
{
    //dtor
}

void HuffmanTree::Init(char* d,int* w,int n)
{
    num=n;
    CharArr=new Node*[num+1];
    SortedArr=new Node*[num+1];
    for(int i=0;i<num;i++)      //Init data
    {
        CharArr[i]=new Node(d[i],w[i]);
        SortedArr[i]=new Node(d[i],w[i]);
    }
    for(int i=0;i<num;i++)      //Sort
    {
        for(int j=0;j<num-1;j++)
        {
            if(SortedArr[j]->weight>SortedArr[j+1]->weight)
            {
                Node* tmp=SortedArr[j];
                SortedArr[j]=SortedArr[j+1];
                SortedArr[j+1]=tmp;
            }
        }
    }

    int pos;
    for(pos=0;SortedArr[pos]->weight==0;pos++);
    ContextNum=num-pos;
    ContextArr=new Node*[ContextNum];
    for(int i=0;i<ContextNum;i++)
    {
        ContextArr[i]=new Node(SortedArr[i+pos]->data,SortedArr[i+pos]->weight);
    }

    cout<<endl;

    for(int i=0;i<ContextNum;i++)
    {
        if(ContextArr[i]->weight!=0)
        {
            cout<<ContextArr[i]->data<<":  "<<ContextArr[i]->weight<<endl;
        }
    }

    Node* t;
    Node* p;
    Node* p1;
    Node* p2;

    for(int i=0;i<ContextNum-1;i++)
    {
        p1=ContextArr[i];
        p2=ContextArr[i+1];
        //cout<<"p2"<<p2->weight<<endl;
        t=new Node();
        t->weight=p1->weight+p2->weight;    //Add weight

        t->Left=p1;t->Right=p2;
        t->data='\0';
        //cout<<t->data;

        //cout<<endl<<t->weight<<endl;

        int j;
        p=t;
        for(j=i+2;j<ContextNum&&p->weight>ContextArr[j]->weight;j++)    //Get new sorted position
        {
            ContextArr[j-1]=ContextArr[j];    //Move to prev
        }
        ContextArr[j-1]=p;
    }

    root=ContextArr[ContextNum-1];

    /*for(int i=0;i<num;i++)      //Init Nodes to NULL
    {
        SortedArr[i]->Left=NULL;
        SortedArr[i]->Right=NULL;
    }

    for(int i=0;i<num;i++)
    {
        Node* p1=SortedArr[i];
        Node* p2=SortedArr[i+1];
        Node* t=new Node();
        t->weight=p1->weight+p2->weight;    //Add weight

        int j;
        for(j=i+2;j<num&&t->weight>SortedArr[j]->weight;j++)    //Get new sorted position
        {
            SortedArr[j-1]=SortedArr[j];    //Move to prev
        }

        SortedArr[j]=t;
    }*/
}

void HuffmanTree::Display()
{
    cout<<endl;
    for(int i=0;i<num;i++)
    {
        if(CharArr[i]->weight!=0)
        {
            cout<<CharArr[i]->data<<":  "<<CharArr[i]->weight<<endl;
        }
    }
}


void HuffmanTree::DisplaySorted()
{
    cout<<endl;
    for(int i=0;i<num;i++)
    {
        if(SortedArr[i]->weight!=0)
        {
            cout<<SortedArr[i]->data<<":  "<<SortedArr[i]->weight<<endl;
        }
    }


}

void HuffmanTree::PreOrder(Node* p,string str)
{
    if(p->Left==NULL&&p->Right==NULL)
    {
        p->s=str;
        for(int i=0;i<str.length();i++)
        {
            HuffCode[p->data][i]=str[i];
        }
        HuffCode[p->data][str.length()]='\0';
        if(p->data!='\n'&&p->data!=' ')
        {
            cout<<p->data<<":"<<str<<endl;
        }else if(p->data=='\n')
        {
            cout<<"\\n"<<":"<<str<<endl;
        }else
        {
            cout<<"space"<<":"<<str<<endl;
        }
    }
    bool flag=0;
    if(p->Left!=NULL)
    {
        flag=1;
        str+="0";
        PreOrder(p->Left,str);
    }
    if(p->Right!=NULL)
    {
        if(flag)    //Cut end code if left not NULL
        {
            str=str.substr(0,str.length()-1);
        }
        str+="1";
        PreOrder(p->Right,str);
    }
}

string HuffmanTree::pre="";

void HuffmanTree::OutCode(Node* p)
{
    //ofstream outfile("Encode",ios::out);
    if(p->data!='\0')
    {
        //outfile<<p->data;
        pre+=p->data;
    }else
    {
        //outfile<<'~';
        pre+='~';
    }
    if(p->Left!=NULL)
    {
        OutCode(p->Left);
    }else
    {
        //outfile<<'#';
        pre+='#';
    }
    if(p->Right!=NULL)
    {
        OutCode(p->Right);
    }else
    {
        //outfile<<'#';
        pre+='#';
    }

}

void HuffmanTree::writePre()
{
    ofstream outfile("Encoded.txt",ios::out);
    for(int i=0;i<pre.length();i++)
    {
        char ch=(pre.at(i));
        //cout<<ch<<endl;
        outfile<<ch;
    }
}

void HuffmanTree::ReReCreate()
{

    ifstream* infile=new ifstream("Encoded.txt",ios::in);
    root=ReCreate(infile);
}

Node* HuffmanTree::ReCreate(ifstream* infile)
{
    char ch;

    infile->get(ch);
    cout<<ch;
    if(ch=='#')
    {
        return NULL;
    }else{
        Node* p=new Node(ch,0);
        p->Left=ReCreate(infile);
        p->Right=ReCreate(infile);
        return p;
    }
}

Node* HuffmanTree::Find(char c)
{
    queue<Node*>* q=new queue<Node*>();
    q->push(root);
    while(!q->empty())
    {
        Node* p=q->front();
        q->pop();
        if(p!=NULL&&p->data==c)
        {
            return p;
        }
        if(p->Left!=NULL)
        {
            q->push(p->Left);
        }
        if(p->Right!=NULL)
        {
            q->push(p->Right);
        }
    }
}

void HuffmanTree::Compress(char* c,int size)
{
    //ofstream outfile("Compressed.bin",ios::binary);

    FILE* f=fopen("Compressed.bin","w");

    /*if(!outfile)
    {
        cout<<"Open Failed!"<<endl;
        return;
    }*/

    string str="";
    int bc=0;
    int k=0;
    for(int i=0;i<size;i++)
    {
        Node* p=Find(c[i]);
        str+=p->s;
        /*for(int j=0;j<str.length();j++)
        {
            schar[i]=str[i];
        }
        schar[str.length()]='\0';*/
    }
    textSize=size;
    HuffString=str;
    cout<<str<<endl<<endl;

    //char* buff=new char[str.length()/8+1];

    for(int j=0;j<str.length();j++)
    {
        if(str[j]=='1')
        {
            bc=bc*2;
            bc+=1;
            //cout<<(int)bc<<"  ";
        }else
        {
            bc=bc*2;
            //cout<<(int)bc<<"  ";
        }
        k++;
        //cout<<"k"<<k<<"  ";
        if(k==8)
        {
            //cout<<(int)bc<<endl;
            //buff[j/8]=(int)bc;   //into buff if 8
            //cout<<(int)buff[j/8];

            fwrite(&bc, sizeof(char), 1, f); /* Ð´µÄstructÎÄ¼þ*/
            bc=0;
            k=0;
        }
    }

    //cout<<endl<<(int)buff[0]<<endl;

    /*if(k!=0)
    {
        //bc<<(8-k);  //shift to highest if not 8 bits
        /*buff[str.length()/8]=(char)bc;*/
        /*fwrite(&bc, k, 1, f);
    }*/

    fclose(f);
    /*outfile.write(buff,str.length()/8+1);*/
}


void HuffmanTree::Decompress()
{
    ifstream infile("Compressed.bin",ios::binary);
    infile.seekg(0, ios::end);
    int len=infile.tellg();
    infile.seekg(0, ios::beg);
    //FILE* fin;
    //fin=fopen("Compressed.bin","r");
    ofstream outfile("Decompress.txt",ios::out);

    /*if(!infile)
    {
        cout<<"Open Failed!"<<endl;
        return;
    }*/

    //cout<<HuffString.length();
    char szBuf[len] = {'\0'};

    infile.read(szBuf, len);

    //fseek(fin, 0, SEEK_SET);

    //fread(szBuf,1,HuffString.length(),fin);

    //cout<<(unsigned int)szBuf[0];

    //cout<<szBuf;

    /*int size;
    for(size=0;szBuf[size]!='\0';size++);*/
    bool binaryArr[len*8];
    for(int i=0;i<len;i++)
    {
        int b=1;
        for (int j=7;j>=0;j--)
        {
            binaryArr[i*8+j]=((szBuf[i]&(b))!=0);
            b=b<<1;
            //cout<<b<<endl;
            //cout<<binaryArr[i*8+j];
        }
    }

    //cout<<endl<<endl<<HuffString.length()*8<<endl<<endl;

    Node* p=root;

    for(int i=0;i<len*8;i++)
    {
        bool bit=binaryArr[i];

        //cout<<bit;
        if(!bit)
        {
            p=p->Left;
            if(p->Left==NULL&&p->Right==NULL)
            {
                cout<<p->data;
                outfile<<p->data;
                p=root;
            }
        }else
        {
            p=p->Right;
            if(p->Left==NULL&&p->Right==NULL)
            {
                cout<<p->data;
                outfile<<p->data;
                p=root;
            }
        }
    }
}
