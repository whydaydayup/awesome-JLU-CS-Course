#include <stdio.h>
#include <math.h>
int main()
{
	float rx(float x);
	float m,n;
	float t;
	printf("please input m&n\n"); 
	scanf("%f%f",&m,&n);
	if(m<n)
	{
		t=m;
		m=n;
		n=t;
	}                           //考虑到n>m的情况
    printf("%f\n",rx(m)/(rx(m-n)*rx(n)));
	return 0;

}
float rx(float x)               //逐个求阶乘太麻烦，相同的多次操作可定义函数
{
	float i;
	float p;
	p=1;
	for(i=x;i>=1;i--) p=p*i;    //注意i>=1而不是i<=1(循环的方向要正确)
    return(p);
}