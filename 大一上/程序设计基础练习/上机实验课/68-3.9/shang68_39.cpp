#include <stdio.h>
#include <math.h>
int main()
{
    int ch,c1,c2,c3,t;
	printf("please input a three-digit number\n");
    scanf("%d",&ch);
	c1=ch%10;
	t=ch%100;
	c2=t/10;
    c3=ch/100;
	if(ch==pow(c1,3)+pow(c2,3)+pow(c3,3))
		printf("yes!");
	else
	    printf("no!");
	return 0;

}