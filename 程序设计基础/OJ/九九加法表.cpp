#include<stdio.h>
int main()
{
    int a[11][11],i,j,n;
	printf("Please input the value of n:");
	scanf_s("%d",&n);
	for(j=1;j<=n;j++)a[0][j]=j;
	for(i=1;i<=n;i++)a[i][0]=i;
	for(i=1;i<=n;i++)
		for(j=1;j<=i;j++)
			a[i][j]=a[i][0]+a[0][j];
	printf("  +");
	for(j=1;j<=n;j++)printf("%3d",a[0][j]);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=i;j++)printf("%3d",a[i][j]);
		printf("\n");
	}
    return 0;
}