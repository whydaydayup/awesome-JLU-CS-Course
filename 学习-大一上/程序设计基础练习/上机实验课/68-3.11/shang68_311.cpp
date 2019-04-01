#include <stdio.h>
#include <math.h>
int main()
{
    int x;
	scanf("%d",&x);
	if(x%3==0)
		printf("能被3整除\n");
    if(x%5==0)
		printf("能被5整除\n");
	if(x%7==0)
		printf("能被7整除\n");
    if((x%7==0)&&(x%5==0)&&(x%3==0))
		printf("能同时被三个数整除\n");
	if((x%7==0)&&(x%5==0))
		printf("能同时被7和5整除\n");
	if((x%5==0)&&(x%3==0))
		printf("能同时被5和3整除\n");
	if((x%7==0)&&(x%3==0))
		printf("能同时被7和3整除\n");
	return 0;
    
}


