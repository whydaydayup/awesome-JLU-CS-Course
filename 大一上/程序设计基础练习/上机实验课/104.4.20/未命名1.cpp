#include <stdio.h>
int main()
{
	int i;
	char x;
	i=1;
	for(x='A';x<='I';x++) printf("%c ",x);
	putchar('\n');
	for(i=1;i<=5;i++)
	{
		for(x='A'+i;x<='I';x++) printf("%c ",x);
		for(x='A';x<='A'+i-1;x++) printf("%c ",x);
		putchar('\n');	
	 } 
	for(i=4;i>=0;i--)
	{
		for(x='A'+i;x<='I';x++) printf("%c ",x);
		for(x='A';x<='A'+i-1;x++) printf("%c ",x);
		putchar('\n');
	}
	return 0;
}
