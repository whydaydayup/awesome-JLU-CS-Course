#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	while(n!=1){
	  if((n-1)%2==0||((n-1)%3==0)){
         if((n-1)%2==0)
			 n=(n-1)/2;
		 else
			 n=(n-1)/3;
	}
	  else{
		printf("no/n");
	    return(0);
	  }
	}
	printf("yes/n");
	return(0);
}