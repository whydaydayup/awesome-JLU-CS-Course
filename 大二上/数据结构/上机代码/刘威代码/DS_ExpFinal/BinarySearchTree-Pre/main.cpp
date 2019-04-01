#include <iostream>
#include <BinarySearchTree.h>

using namespace std;

void ShowMenu(int i);

int main()
{
    int d;
    BinarySearchTree<int>* BST=new BinarySearchTree<int>();

    ShowMenu(0);

    int operation=0;
    cin>>operation;

    while(operation)
    {
        Node<int>* tmp;
        switch(operation)
        {
        case 1:
            ShowMenu(1);
            BST->Create();
            break;
        case 2:
            BST->PreOrder(BST->root);
            break;
        case 3:
            BST->InOrder(BST->root);
            break;
        case 4:
            BST->PostOrder(BST->root);
            break;
        case 5:
            ShowMenu(2);
            cin>>d;
            tmp=BST->Find(d);
            if(tmp!=NULL)
            {
                cout<<"Record Found: "<<endl<<tmp->data<<endl;
            }else{
                cout<<"Cannot Found the Record!"<<endl;
            }
            break;
        case 6:
            ShowMenu(2);
            cin>>d;
            BST->Insert(d);
            break;
        case 7:
            ShowMenu(2);
            cin>>d;
            BST->DeleteByData(d);
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
        cout<<endl<<"Please enter an option:";
        cout<<endl<<"1) Create"<<endl<<"2) PreOrder"<<endl<<"3) InOrder"<<endl<<"4) PostOrder"<<endl<<"5) Find"<<endl<<"6) Insert"<<endl<<"7) Delete"<<endl<<"0) Exit"<<endl<<endl;
        break;
    case 1:
        cout<<endl<<"Please enter PreOrder:"<<endl;
        break;
    case 2:
        cout<<endl<<"Please enter the data:"<<endl;
        break;
    }
}
