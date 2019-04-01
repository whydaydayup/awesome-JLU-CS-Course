#include <stdio.h>
#include <math.h>
int main()
{
	int x,n,i,j;
	double p,y,m;
	p=1;
	m=0;
	printf("please input x and n\n");
	scanf("%d%d",&x,&n);
	for(j=1;j<=n;j++)
	{
	
	 for(i=1;i<=(2*n+1);i++)
	 {
		p=p*i;
	 }
	 m=pow(x,2*j+1)/p;
	 n+=1;
	 if(m<=1e-8) break;
	 y=y+m;
    }
    printf("%f\n",y);
    return 0;
}
