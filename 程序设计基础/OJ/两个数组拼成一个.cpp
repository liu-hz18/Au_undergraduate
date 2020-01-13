#include<stdio.h>
int main()
{
	int num1[20],num2[20],num[40];
	int len1,len2,n,k,m;
	printf("Please input the 1st array:");
	for(len1=0;len1<20;len1++)
	{
		scanf_s("%d",&num1[len1]);
	    if(num1[len1]==0){len1--;break;}
	}
    printf("Please input 2nd array:");
	for(len2=0;len2<20;len2++)
	{
		scanf_s("%d",&num2[len2]);
		if(num2[len2]==0){len2--;break;}
	}
	printf("\nThe new array is:\n");
	for(k=0;k<=len1;k++)
		num[k]=num1[k];
	for(k=len1+1;k<=len1+len2+1;k++)
		num[k]=num2[k-len1-1];
    for(k=len1+len2+1;k>=0;k--)//ц╟ещеепР 
		for(m=0;m<k;m++)
			if(num[m]>num[m+1]){int tmp=num[m];num[m]=num[m+1];num[m+1]=tmp;}
    for(k=0;k<=len1+len2+1;k++)printf("%d ",num[k]);
	printf("\n");
return 0;
}
