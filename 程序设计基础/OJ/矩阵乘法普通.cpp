#include<stdio.h>
int main()
{
	const int n=200;
	int a[n][n],b[n][n],c[n][n];
	printf("as for A[k][l],B[l][s],please input k,l,s(they all <100):");
	int k,l,s;int i,j,m;
	scanf_s("%d%d%d",&k,&l,&s);
	printf("please input matrix A:\n");
	for(i=1;i<=k;i++)for(j=1;j<=l;j++)scanf_s("%d",&a[i][j]);
	printf("please input matrix B:\n");
	for(i=1;i<=l;i++)for(j=1;j<=s;j++)scanf_s("%d",&b[i][j]);
	printf("matrix AB is:\n");
	for(i=1;i<=k;i++)
		for(j=1;j<=s;j++)
		{
			c[i][j]=0;
			for(m=1;m<=l;m++)
				c[i][j]+=a[i][m]*b[m][j];
		}
	for(i=1;i<=k;i++)
	{
       for(j=1;j<=s;j++)printf("%3d",c[i][j]);
	   printf("\n");
	}
	return 0;
}
