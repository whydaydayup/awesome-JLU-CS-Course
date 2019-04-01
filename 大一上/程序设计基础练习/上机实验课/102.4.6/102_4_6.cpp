#include <stdio.h>
#include <math.h>
int main()
{
    int x1,x2,y,n;
	x1=1;
	x2=1;
	n=2;
	printf("%d %d",x1,x2);
	do
	{
	        y=x1+x2;
			putchar(' ');
            printf("%d",y);
			x1=x2;
            x2=y;
			n+=1;
		}while(n<20);
	putchar('\n');
		return 0;

}
