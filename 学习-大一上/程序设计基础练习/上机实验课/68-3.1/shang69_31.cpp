#include <stdio.h>
#include <math.h>
int main()
{
	char ch;
	scanf("%c",&ch);
	if(ch>=97)
		ch=ch-32;
	printf("%c\n",ch);
	return 0;
}
		