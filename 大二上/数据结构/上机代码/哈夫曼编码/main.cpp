#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <HuffmanTree.h>

using namespace std;

void ShowMenu(int i);

int main()
{
    ifstream infile("text.txt",ios::in);
    if(!infile)
    {
        cout<<"No File!"<<endl;
        return 0;
    }
    /*char ch[10240];
    char c;
    int i=0;
    */
    /*while(infile.get(c))
    {
        ch[i]=c;
        i++;
    }
    ch[i+1]='\0';
    cout<<ch;*/

    char chars[128];
    for(int i=0;i<128;i++)
    {
        chars[i]=i;
        //cout<<chars[i];
    }
    int we[128];
    for(int i=0;i<128;i++)
    {
        we[i]=0;
    }

    char c;
    int textSize=0;
    char text[10240];

    while(infile.get(c))
    {
        text[textSize]=c;
        //cout<<c;
        we[(int)c]+=1;
        //cout<<we[(int)c];
        textSize+=1;
    }

    text[textSize]='\0';

    HuffmanTree* HTree=new HuffmanTree();
    //HTree->Init(chars,we,128);

    //HTree->Display();
    //HTree->DisplaySorted();
    //cout<<endl<<HTree->root->weight;

    cout<<endl;
    //HTree->PreOrder(HTree->root,HTree->root->s);

    //HTree->Compress(text,textSize);

    //HTree->Decompress();

    ShowMenu(0);

    int operation=0;
    cin>>operation;



    //char* codeee;

    /*ofstream outfile("t.txt",ios::out);
    for(int i=0;i<4096;i++) //4096: 文本长度
    {
        char c=(rand()%('l'-'a'+1))+'a';  //a/l: 生成范围
        outfile<<c;
    }*/
    while(operation)
    {

        char ch;
        Node* tmp;
        switch(operation)
        {
        case 1:
            break;
        case 2:
            HTree->Init(chars,we,128);
            break;
        case 3:
            HTree->PreOrder(HTree->root,HTree->root->s);
            HTree->OutCode(HTree->root);
            //cout<<HTree->pre;
            //codeee=new char[HTree->pre.length()];
            HTree->writePre();
            break;
        case 4:
            HTree->Compress(text,textSize);
            break;
        case 5:
            HTree->ReReCreate();
            //HTree->PreOrder(HTree->root,HTree->root->s);
            HTree->Decompress();
            break;
        case 6:
            break;
        }
        ShowMenu(0);
        cin>>operation;
    }

    return 0;
}

void ShowMenu(int i)
{
    switch(i)
    {
    case 0:
        cout<<endl<<"please input numbers to decide what you want to do:";
        cout<<endl<<"1.read in file"<<endl<<"2.initial and statistic"<<endl<<"3.coding"<<endl<<"4.out to binary"<<endl<<"5.decoding"<<endl<<"0.quit"<<endl<<endl;
        break;
    }

}
