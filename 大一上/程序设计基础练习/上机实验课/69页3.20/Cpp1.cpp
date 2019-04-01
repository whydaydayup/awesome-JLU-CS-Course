#include <stdio.h>
enum tmonth {January,February,March,April,May,June,July,August,September,October,November,December}month;
int main()
{
	int x;
    printf("please input month in number\n");
    scanf("%d",&x);
	switch(x){
	case 1:printf("month=January");break;
	case 2:printf("month=February");break;
	case 3:printf("month=March");break;
	case 4:printf("month=April");break;
	case 5:printf("month=May");break;
	case 6:printf("month=June");break;
	case 7:printf("month=July");break;
	case 8:printf("month=August");break;
	case 9:printf("month=September");break;
	case 10:printf("month=October");break;
	case 11:printf("month=November");break;
	case 12:printf("month=December");break;
	}
	return 0;

}
