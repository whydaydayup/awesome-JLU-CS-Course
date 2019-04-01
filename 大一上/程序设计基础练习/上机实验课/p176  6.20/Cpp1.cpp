#include<stdio.h>
main(){
	int a[30],i,j,m;
	i=0;
	j=0;
	m=1;
	a[0]=1;
	for(m=1;m<30;m++){
		if((a[i]*2)<(a[j]*3)){
			a[m]=2*a[i]+1;
	    	i=i+1;
		}
		else{
			a[m]=3*a[j]+1;
			j=j+1;
		}
	}
	for(i=0;i<30;i++){
	   printf("%d ",a[i]);
	}
}