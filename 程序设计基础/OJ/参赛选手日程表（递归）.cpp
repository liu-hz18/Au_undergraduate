//编排比赛日程表
#include <stdio.h>
#define MAXN 64
int a[MAXN+1][MAXN+1]={0};
void gamecal(int k,int n)//处理编号k开始的n个选手的日程 
{
    int i,j;
    if(n==2)
    {
        a[k][1]=k;  //参赛选手编号
        a[k][2]=k+1; //对阵选手编号
        a[k+1][1]=k+1; //参赛选手编号 
        a[k+1][2]=k; //对阵选手编号 
    }
	else
	{
        gamecal(k,n/2);
        gamecal(k+n/2,n/2);//实现分块
        for(i=k;i<k+n/2;i++) //填充右上角 
        {
            for(j=n/2+1;j<=n;j++)
            {
                a[i][j]=a[i+n/2][j-n/2];
            }
        }
        for(i=k+n/2;i<k+n;i++) //填充右下角 
        {
            for(j=n/2+1;j<=n;j++)
            {
                a[i][j]=a[i-n/2][j-n/2];
            }
        }
    }
}
int main()
{
    int m,i,j;
    printf("输入参赛选手人数：");
    scanf_s("%d",&m);
    j=1;
    for(i=2;i<8;i++)
    {
        j=j*2;
        if(j==m) break;
    }
    if(i>=8)
    {
        printf("参赛选手人数必须为2的整数次幂，且不超过64！\n");
        return 0; 
    }//判断并保证参赛选手为2的整数幂
    gamecal(1,m);//使用gamecal函数
    printf("\n编号 ");
    for(i=2;i<=m;i++)
        printf("%2d天 ",i-1);
    printf("\n");//表头天数
    for(i=1;i<=m;i++)
    {
       for(j=1;j<=m;j++)
           printf("%4d ",a[i][j]);
       printf("\n");
    }
  return 0;
}