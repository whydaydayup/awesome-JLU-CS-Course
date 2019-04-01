#include <stdio.h>
#include <math.h>
int main()
{
float x,y;
float fx(float x);
printf("please input x\n");
scanf("%f",&x);
y=fx(x);
printf("%f\n",y);
return 0;
}
float fx (float x)
{
	int i;
    for(i=1;i<=10;i++)
	{
		x=1+1/x;
	}
	return(x);
}
