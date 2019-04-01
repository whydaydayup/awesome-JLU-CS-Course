#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <stack>
#include <string>
#include "Student.h"
#include "StudentStuct.h"

using namespace std;
/***********************************************二叉查找树类*********************************************************/
class sort_BSTNode
{
public:
	sort_BSTNode *llink;
	sort_BSTNode *rlink;
	Student* key;
	sort_BSTNode(Student* &item, sort_BSTNode *lptr = NULL, sort_BSTNode *rptr = NULL) :key(item), llink(lptr), rlink(rptr) {}
	sort_BSTNode *Getllink()const { return llink; }
	sort_BSTNode *Getrlink()const { return rlink; }
	Student* Getkey()const { return key; }
};

class sort_BSTree
{
public:
	sort_BSTree(sort_BSTNode *t = NULL) :root(t) {}
	~sort_BSTree() { Del(root); }
	void Del(sort_BSTNode *t);
	sort_BSTNode* Sub_Insert(Student* k,int Sub_Num);
	sort_BSTNode* Toscore_Insert(Student* k);
	void total_InOrder();
	void Sub_InOrder(int i);
private:
	sort_BSTNode *root;
};

void sort_BSTree::Del(sort_BSTNode *t)
{
	if (t != NULL)
	{
		sort_BSTNode *p = t->Getllink(), *next;
		while (p != NULL)
		{
			next = p->Getrlink();
			Del(p);
			p = next;
		}
		delete t;
	}
}

sort_BSTNode* sort_BSTree::Sub_Insert(Student* k,int Sub_Num)//构造成绩查询二叉查找树
{
	if (root == NULL)
	{
		root = new sort_BSTNode(k, NULL, NULL);
		return NULL;
	}
	sort_BSTNode *p = root;
	while (p != NULL)
	{
		if (k->getsubject()[Sub_Num] > p->key->getsubject()[Sub_Num])
		{
			if (p->llink == NULL)
				break;
			else
				p = p->llink;
		}
		else
		{
			if (p->rlink == NULL)
				break;
			else
				p = p->rlink;
		}
	}
	sort_BSTNode *q = new sort_BSTNode(k, NULL, NULL);
	if (k->getsubject()[Sub_Num] > p->Getkey()->getsubject()[Sub_Num])
		p->llink = q;
	else
		p->rlink = q;
	return NULL;
}

sort_BSTNode* sort_BSTree::Toscore_Insert(Student* k)//构造总分查询
{
	if (root == NULL)
	{
		root = new sort_BSTNode(k, NULL, NULL);
		return NULL;
	}
	sort_BSTNode *p = root;
	while (p != NULL)
	{
		if (k->gettotalscore() > p->key->gettotalscore())
		{
			if (p->llink == NULL)
				break;
			else
				p = p->llink;
		}
		else
		{
			if (p->rlink == NULL)
				break;
			else
				p = p->rlink;
		}
	}
	sort_BSTNode *q = new sort_BSTNode(k, NULL, NULL);
	if (k->gettotalscore() > p->Getkey()->gettotalscore())
		p->llink = q;
	else
		p->rlink = q;
	return NULL;
}

void sort_BSTree::total_InOrder()//总分排序
{
	sort_BSTNode *t = root;
	if (t == NULL) { return; }
	stack<sort_BSTNode *> s;
	cout << "   学号     姓名       总成绩" <<endl;
	while (t != NULL || !s.empty())
	{
		while (t != NULL)
		{
			s.push(t);
			t = t->Getllink();
		}
		if (s.empty()) { return; }
		t = s.top();
		s.pop();
        cout << t->Getkey()->getstudentID() << "    " << t->Getkey()->getname()<<"       "<<t->Getkey()->gettotalscore()<< endl;
		t = t->Getrlink();
	}
}

void sort_BSTree::Sub_InOrder(int i)//成绩排序
{
	sort_BSTNode *t = root;
	if (t == NULL) { return; }
	stack<sort_BSTNode *> s;
	cout << "   学号     姓名       科目" << i+1 <<endl;
	while (t != NULL || !s.empty())
	{
		while (t != NULL)
		{
			s.push(t);
			t = t->Getllink();
		}
		if (s.empty()) { return; }
		t = s.top();
		s.pop();
        cout << t->Getkey()->getstudentID() << "    " << t->Getkey()->getname()<<"       "<<t->Getkey()->getsubject()[i]<< endl;
		t = t->Getrlink();
	}
}

void Sort(int Sub_num,StudentStruct& astruct)//查询种类选择
{
    system("cls");
    sort_BSTree Subsort;
	//导入树******
	if(Sub_num==11)
	{
	    for (int i = 0; i < astruct.stucount; i++)
	{
		Student* temp = &astruct.studentArray[i];
		Subsort.Toscore_Insert(temp);
	}
	    Subsort.total_InOrder();
	}
	else
    {
        for (int i = 0; i < astruct.stucount; i++)
	{
		Student* temp = &astruct.studentArray[i];
		Subsort.Sub_Insert(temp,Sub_num-1);
	}
        Subsort.Sub_InOrder(Sub_num-1);
    }
	//*********
	system("pause");
}

#endif // SORT_H

