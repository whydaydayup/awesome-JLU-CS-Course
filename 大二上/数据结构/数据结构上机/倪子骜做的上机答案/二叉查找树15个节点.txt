#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;
bool flag[1010];
class TreeNode{
	int x;
	TreeNode* l;
	TreeNode* r;
	int deep;
	public:
	TreeNode(int d,int a=0,TreeNode* b=NULL,TreeNode* c=NULL):deep(d),x(a),l(b),r(c){}
	void print(){
		printf("%d",x);
	}
	friend class Tree;
};
class Tree{
	TreeNode* root;
	public:
	Tree():root(new TreeNode(1)){}
	TreeNode* getroot(){return root;}
	bool dfs(TreeNode*& p,int x,int deep){
		if (p->x==0){
			p=new TreeNode(deep,x,new TreeNode(deep+1),new TreeNode(deep+1));
			return 1;
		}
		if (p->x > x) dfs(p->l,x,deep+1);
		if (p->x < x) dfs(p->r,x,deep+1);
		if (p->x == x) return 0;
	}
	bool Insert(int x){
		if (!dfs(root,x,1)) {printf("Already heave");return false;}
		return true;
	}
	void print(){
		queue<TreeNode*> q;
		q.push(root);
		int d=1;
		while (!q.empty()){
			TreeNode* p=q.front();
			q.pop();
			if (p->deep>d){
				printf("\n");d++;
			}
			if (p->x!=0){
				printf("%4d",p->x);
				q.push(p->l);
				q.push(p->r);
			}
			else printf("%4s","NUL");
		}
	}
	void InOrder(TreeNode* p){
		if (p->x!=0){
			InOrder(p->l);
			printf("%4d",p->x);
			InOrder(p->r);
		}
	}
	TreeNode* search(TreeNode* p,int x){
		if (p->x == x){
			return p;
		}
		if (p->x > x) return search(p->l,x);
		return search(p->r,x);
	}
	double calc_su(int a[]){
		int sum=0;
		for (int i=1;i<=15;i++){
			TreeNode* p=search(root,a[i]);
			sum+=p->deep;
		}
		return sum/15.0;
	}
	void dfs_fa(TreeNode* p,int& s,int& num){
		if (p->x==0){
			s+=p->deep;
			num++;
			return;
		}
		dfs_fa(p->l,s,num);
		dfs_fa(p->r,s,num);
	}
	double calc_fa(){
		int sum=0;
		int num=0;
		dfs_fa(root,sum,num);
		return 1.0*sum/num;
	}
};
int main(){
	Tree t;
	srand(time(NULL));
	int a[20];
	for (int i=1;i<=15;i++){
		a[i]=rand()%1000+1;
		if (flag[a[i]]){
			i--;continue;
		}
		flag[a[i]]=1;
		printf("%d ",a[i]);
		t.Insert(a[i]);
	}
	printf("\n");
	t.print();
	printf("\nInOrder:");
	t.InOrder(t.getroot());
	printf("\nsuc time:%.2lf\nfail time:%.2lf",t.calc_su(a),t.calc_fa());
	return 0;
}
