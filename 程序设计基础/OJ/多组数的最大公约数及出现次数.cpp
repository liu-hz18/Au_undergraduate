#include<stdio.h>
#include<math.h>
int getmaxdivisor(int x,int y)
{
	while(x!=y)
	{
		if(x>y)x-=y;
		else y-=x;
	}
return x;
}
int max(int m,int n){int p=(m>n)?m:n;return p;}
int main()
{
	int getmaxdivisor(int x,int y);
	int max(int m,int n);
	int a[100],b[100],c[100];
	int t=0,count=0;
	for(int i=1;i<100;i++)
	{
		printf("please input two numbers:");
		scanf_s("%d%d",&a[i],&b[i]);
	    if((a[i]==0)||(b[i]==0))break;
		if((a[i]<0)||(b[i]<0)){printf("Erorr!please re-input!\n\n");i--;continue;}
		else if((a[i]!=0)&&(b[i]!=0)){c[i]=getmaxdivisor(a[i],b[i]),t++;}
		printf("\n");
	}
	if(t==0)printf("you have not input the right numbers!\n\n");
	else
	{
		int m=max(c[1],c[2]);
		for(int k=3;k<=t;k++)m=max(m,c[k]);
        printf("\n%d   ",m);
	    for(int k=1;k<=t;k++)if(c[k]==m)count++;
	    printf("%d\n\n",count);
	}
return 0;
}
