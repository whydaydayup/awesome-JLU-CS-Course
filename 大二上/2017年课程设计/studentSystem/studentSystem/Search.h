#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <stack>
#include <string>
#include "Student.h"
#include "StudentStuct.h"

using namespace std;
/*************************************************二叉查找树类**********************************************************/
class BSTNode
{
public:
	BSTNode *llink;
	BSTNode *rlink;
	Student* key;
	BSTNode(Student* &item, BSTNode *lptr = NULL, BSTNode *rptr = NULL) :key(item), llink(lptr), rlink(rptr) {}
	BSTNode *Getllink()const { return llink; }
	BSTNode *Getrlink()const { return rlink; }
	Student* Getkey()const { return key; }
};

class BSTree
{
public:
	BSTree(BSTNode *t = NULL) :root(t) {}
	~BSTree() { Del(root); }
	void Del(BSTNode *t);
	BSTNode* IDInsert(Student* k);
	BSTNode* IDSearch(int iD);
	BSTNode* NameInsert(Student* k);
	BSTNode* NameSearch(string Name);
	void FZSearch(string fsname);
private:
	BSTNode *root;
};

/*********************************kmp算法及选择查询种类*************************************/
int * Get_Next(string str, int &m)   //fail
{
	m = str.length();
	int * next = new int[m];
	next[0] = -1;
	int i = 0;
	int j = -1;

	while (i<m - 1)
	{
		if (j == -1 || str[i] == str[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
	return next;
}
bool KMP(string str1, string str2)
{
	int Lstr1 = str1.length();
	int Lstr2 = str2.length();
	int * next = Get_Next(str2, Lstr2);
	int i = 0;
	int j = 0; //j=-1
	while (i<Lstr1 && j<Lstr2)
	{
		if (j == -1 || str1[i] == str2[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	delete[] next;

	if (j == Lstr2)
		return true;
	else
		return false;
} //kmp

void ID_ExactSearch(StudentStruct& astruct)
{
	BSTree ID_ES;
	int id;
	cout << "请输入要查询的学号：";
	cin >> id;
	//导入树******
	for (int i = 0; i < astruct.stucount; i++)
	{
		Student* temp = &astruct.studentArray[i];
		ID_ES.IDInsert(temp);
	}
	//*********
	ID_ES.IDSearch(id);
	system("pause");
}

void Name_ExactSearch(StudentStruct& astruct)
{
	BSTree Name_ES;
	string name;
	cout << "请输入要查询的姓名：";
	cin >> name;
	//导入树******
	for (int i = 0; i < astruct.stucount; i++)
	{
		Student* temp = &astruct.studentArray[i];
		Name_ES.NameInsert(temp);
	}
	//**********
	Name_ES.NameSearch(name);
	system("pause");
}

void Name_FuzzySearch(StudentStruct& astruct)
{
	BSTree Name_FS;
	string FSname;
	cout << "请输入要模糊查询的姓名：";
	cin >> FSname;
	//导入树*****
	for (int i = 0; i < astruct.stucount; i++)
	{
		Student* temp = &astruct.studentArray[i];
		Name_FS.NameInsert(temp);
	}
	//********
	Name_FS.FZSearch(FSname);
	system("pause");
}
/**********************************************************************/
void BSTree::Del(BSTNode *t)
{
	if (t != NULL)
	{
		BSTNode *p = t->Getllink(), *next;
		while (p != NULL)
		{
			next = p->Getrlink();
			Del(p);
			p = next;
		}
		delete t;
	}
}


BSTNode* BSTree::IDInsert(Student* k)
{
	if (root == NULL)
	{
		root = new BSTNode(k, NULL, NULL);
		return NULL;
	}
	BSTNode *p = root;
	while (p != NULL)
	{
		if (k->getstudentID() < p->key->getstudentID())
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
	BSTNode *q = new BSTNode(k, NULL, NULL);
	if (k->getstudentID() < p->key->getstudentID())
		p->llink = q;
	else
		p->rlink = q;
	return NULL;
}

BSTNode* BSTree::IDSearch(int iD)
{
	if (root == NULL)
	{
		cout << "error the BSTree is empty"<<endl;
		return NULL;
	}
	BSTNode *p = root;
	int count = 0;
	while (p != NULL)
	{
		if (iD == p->key->getstudentID())
		{
		   cout << "   学号     姓名      科目1  科目2  科目3  科目4  科目5  科目6  科目7  科目8  科目9  科目10  总成绩  平均成绩" <<endl;
		   cout << p->key->getstudentID() << "    " << p->key->getname() << "       ";
		   for(int i=0;i<10;++i)
           {
               cout<< p->key->getsubject()[i] <<"     ";
           }
           cout<< p->key->gettotalscore() <<"     "<< p->key->getaveragescore() <<endl;
		   count++;
		   p = p->rlink;
		   break;
		}
		if (iD < p->key->getstudentID())
		{
			if (p->llink == NULL)
				break;
			else
				p = p->llink;
		}
		if(iD >  p->key->getstudentID())
		{
			if (p->rlink == NULL)
				break;
			else
				p = p->rlink;
		}
	}
	if (count == 0)
	{
		cout << iD << "不存在！" << endl;
	}
}

BSTNode* BSTree::NameInsert(Student* k)
{
	if (root == NULL)
	{
		root = new BSTNode(k, NULL, NULL);
		return NULL;
	}
	BSTNode *p = root;
	while (p != NULL)
	{
		if (k->getname() < p->key->getname())
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
	BSTNode *q = new BSTNode(k, NULL, NULL);
	if (k->getname() < p->key->getname())
		p->llink = q;
	else
		p->rlink = q;
	return NULL;
}

BSTNode* BSTree::NameSearch(string Name)
{
	if (root == NULL)
	{
		cout << "error the BSTree is empty"<<endl;
		return NULL;
	}
	BSTNode *p = root;
	int count = 0;
	while (p != NULL)
	{
		if (Name == p->key->getname())
		{
		   cout << "   学号     姓名      科目1  科目2  科目3  科目4  科目5  科目6  科目7  科目8  科目9  科目10  总成绩  平均成绩" <<endl;
		   cout << p->key->getstudentID() << "    " << p->key->getname() << "       ";
		   for(int i=0;i<10;++i)
           {
               cout<< p->key->getsubject()[i] <<"     ";
           }
           cout<< p->key->gettotalscore() <<"     "<< p->key->getaveragescore() <<endl;
		   count++;
		   p = p->rlink;
		   continue;
		}
		if (Name < p->key->getname())
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
	if (count == 0)
	{
		cout << Name << "不存在！" << endl;
	}
}

void BSTree::FZSearch(string fsname)
{
	BSTNode *t = root;
	if (t == NULL) { return; }
	stack<BSTNode *> s;
	cout << "   学号     姓名      科目1  科目2  科目3  科目4  科目5  科目6  科目7  科目8  科目9  科目10  总成绩  平均成绩" <<endl;
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
		if (KMP(t->Getkey()->getname(), fsname))
            {
		   cout << t->key->getstudentID() << "    " << t->key->getname() << "       ";
		   for(int i=0;i<10;++i)
           {
               cout<< t->key->getsubject()[i] <<"     ";
           }
           cout<< t->key->gettotalscore() <<"     "<< t->key->getaveragescore() <<endl;
           }
		t = t->Getrlink();
	}
}



#endif // STUDENTSTRUCT_H

