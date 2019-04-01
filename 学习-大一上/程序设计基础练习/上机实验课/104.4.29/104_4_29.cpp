#include <stdio.h>
#include <math.h>
int main()
{
double y;
y=0;
float x;
for(x=0;x<=63;x++) y=y+pow(2,x);
y/=1.4*(1e+8);
printf("%f\n",y);
return 0;
}
