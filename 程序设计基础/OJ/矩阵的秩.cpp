#include<stdio.h>
#include<math.h>
const int maxn=205;
double a[maxn][maxn];
bool Cmp(double x){return fabs(x)<1e-7;}
void swap(double&y,double&z){double temp=y;y=z;z=temp;}
int main()
{
	int m,n,i,j,k,rank=0;
	double tmp;
    printf("please input the row and column:");
	scanf_s("%d%d",&m,&n);
	printf("please input the elements of the matrix:\n");
	for(i=1;i<=m;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
    for(i=1;i<=n;i++)
	{
         //从对角线元素开始，纵向检查每列的元素,直到某一行出现非零元素跳出循环
		        for(j=i;j<=m&&Cmp(a[j][i]);j++);
				if(j>m)continue;//超过n就换下一列
				if(i^j)//i!=j
					for(k=1;k<=n;k++)
						swap(a[i][k],a[j][k]);//在a[i][i]为零时，为使其非零，交换第i行和第j行
				for(j=1;j<=m;j++)//从j=1开始是关键，这样最终会使矩阵化为对角矩阵而不是上三角矩阵。
				{
					if(i^j&&!Cmp(a[j][i]))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n;k++)
						{
							a[j][k]-=a[i][k]*tmp;//用第i行消去第j行，使得第j行的第j行元素为0；
						}
					}
				}
	}
	for(i=1;i<=m;i++,putchar(10))
		for(j=1;j<=n;j++)
			printf("%5.2lf",a[i][j]);
   int min=(m<=n)?m:n;
	for(i=1;i<=min;i++)
		if(!Cmp(a[i][i]))rank++;
	printf("Rank=%d\n",rank);
return 0;
}