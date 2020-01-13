//分书问题
//回溯递归
#include<stdio.h>
	int like[6][6]={{0},
	{0,0,0,1,1,0},
	{0,1,1,0,0,1},
	{0,0,1,1,0,1},
	{0,0,0,0,1,0},
	{0,0,1,0,0,1}},
	flag[6]={0},
	taken[6]={0};
void solution(int i)
{
	int j,k;
	for(j=1;j<=5;j++)
	{
		if((flag[j]!=0)||(like[i][j]==0))continue;
		taken[i]=j;
		flag[j]=1;
		if(i==5)
		{
			for(k=1;k<=5;k++)
				printf("%d ",taken[k]);
			putchar(10);
		}
		else solution(i+1);
		taken[i]=0;
		flag[j]=0;
	}
}
int main()
{
	printf("分书方案：\nA B C D E\n");
	solution(1);
	return 0;
}
