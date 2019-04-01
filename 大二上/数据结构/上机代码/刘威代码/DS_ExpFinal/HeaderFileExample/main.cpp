#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

#define MAX 1000000
#define MIN 0

using namespace std;

int GenerateRandom();
void VectorExample();
void ListExample();
void StackExample();
void QueueExample();
void SetExample();
void MaxExample();
void MinExample();
void SwapExample();
void SortExample();
bool Compare(int x,int y);

int main()
{
    srand(time(NULL));
    //cout<<GenerateRandom();
    //VectorExample();
    //ListExample();
    //StackExample();
    //QueueExample();
    //SetExample();
    //MaxExample();
    //MinExample();
    //SwapExample();
    SortExample();
    return 0;
}

int GenerateRandom()
{
    return rand()%(MAX-MIN+1)+MIN;
}

void VectorExample()
{
    vector<int>* vec=new vector<int>();
    for(int i=0;i<100;i++)
    {
        vec->push_back(i+1000);
    }

    vector<int>::iterator it;
    for(it=vec->begin();it!=vec->end();it++)
    {
        cout<<*it<<endl;
    }
    vec->pop_back();    //pop tail unit
    vec->insert(it-=3,9999);    //insert at pos last but 3
    for(it=vec->begin();it!=vec->end();it++)
    {
        cout<<*it<<endl;
    }
}

void ListExample()
{
    list<int>* l=new list<int>();
    for(int i=0;i<100;i++)
    {
        l->push_back(i+1000);
    }

    list<int>::iterator it;
    for(it=l->begin();it!=l->end();it++)
    {
        cout<<*it<<endl;
    }
}

void StackExample()
{
    stack<int>* s=new stack<int>();
    for(int i=0;i<100;i++)
    {
        s->push(i+1000);
    }

    while(!s->empty())
    {
        cout<<s->top()<<endl;
        s->pop();
    }
}

void QueueExample()
{
    queue<int>* q=new queue<int>();
    for(int i=0;i<100;i++)
    {
        q->push(i+1000);
    }

    while(!q->empty())
    {
        cout<<q->front()<<endl;
        q->pop();
    }
}

void SetExample()
{
    set<int>* s=new set<int>();
    for(int i=0;i<1000;i++)
    {
        s->insert(GenerateRandom());
    }
    set<int>::iterator it;
    for(it=s->begin();it!=s->end();it++)
    {
        cout<<*it<<endl;
    }
    cout<<endl<<*s->find(90);   //return iterator
}

void MaxExample()
{
    int a=10,b=20,c=100;
    cout<<max(a,max(b,c));
}

void MinExample()
{
    int a=10,b=20,c=100;
    cout<<min(a,min(b,c));
}

void SwapExample()
{
    int x=10,y=100;
    swap(x,y);
    cout<<"x"<<x<<"y"<<y;
}

void SortExample()
{
    int a[999];
    for(int i=0;i<999;i++)
    {
        a[i]=GenerateRandom();
    }
    sort(a,a+999,Compare);  //reverse
    for(int i=0;i<999;i++)
    {
        cout<<a[i]<<endl;
    }
}

bool Compare(int x,int y)
{
    return x>y;
}
