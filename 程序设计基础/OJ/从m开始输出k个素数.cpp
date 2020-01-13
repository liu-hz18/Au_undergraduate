#include<stdio.h>
#include<math.h>
int main()
{
	int judge(int x);int a[200];
	int m,k;
    int i,t=0;
	scanf_s("%d%d",&m,&k);
	while((m!=0)&&(k!=0))
	{

		for(i=m;t<k;i++){if(judge(i)){t++;a[t]=i;}}
		for(int j=t;j>0;j--)printf("%d ",a[j]);
	    printf("\n\n");
	    scanf_s("%d%d",&m,&k);
		t=0;
	}
return 0;
}
int judge(int x)
{
	if(x==2)return 1;
	for(int i=2;i<x;i++)
        {
			int m=x%i;
	        if(m==0){return 0;break;}
        	else if(i>sqrt((double)x)){return 1;break;}
	    }
}