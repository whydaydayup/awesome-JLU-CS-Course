#include<stdio.h>
main(){
	int a[7],i,j,n,m;
	n=7;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);  //输入数组
	}
    for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[i]==a[j])
			{         //判断是否有相同元素
				for(m=j;m<n-1;m++)
				{
				  a[m]=a[m+1];       //向前串1
				}
				n=n-1;              //数组中元素减1
				j=j-1;
			}
		}
	}
    for(i=0;i<n;i++){
	   printf("%d ",a[i]);   //输出
	}

}
