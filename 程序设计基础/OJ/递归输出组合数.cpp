//递归实现
#include<stdio.h>
//x表示已经选了x个，s表示从第s个自然数开始考虑。
void permutation(int x,int s,int n,int r)
{
    for(int i=s;n-i>=r-x;i++)
	{
        if(i!=s)
			for(int j=1;j<x;j++)printf("    ");
        printf("%4d",i);
        if(x==r)putchar('\n');
        else permutation(x+1,i+1,n,r);
    }
}
int main()
{
    int n,r;
	while(1){
		printf("Enter N R:");
		scanf_s("%d%d",&n,&r);
		if(n<1||n>1000||r>n||r<1)
		{
			printf("Error!please input again!\n");
		}
		else
		{
			printf("combinations:\n");
			permutation(1,1,n,r);
			break;
		}
	}
    return 0;
}
