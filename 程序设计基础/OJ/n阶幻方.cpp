#include<stdio.h>
void swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
void odd(int cube[][100],int N,int min)
{
	int n=(N+1)/2;
	cube[1][n]=min;
	int i=2*n-1;
	int j=n+1;
	for(int k=min+1;k<=(2*n-1)*(2*n-1)+min-1;k++)
	{
		cube[i][j]=k;
		i--;j++;
		if(i==0&&j==2*n){i+=2;j--;}
		if(i==0)i=2*n-1;
		if(j==2*n)j=1;
		if(cube[i][j]){i+=2;j--;}
	}
}
void doueven(int cube[][100],int N)
{
	int k=1,i,j;
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			cube[i][j]=k++;
	for(i=1;i<=N/2;i++)
	    for(j=1;j<=N;j++)
		{
			int x=i%4,y=j%4;
			if((x==y)||(x+y)%4==1)
				swap(cube[i][j],cube[N+1-i][N+1-j]);
		}
}
void sineven(int cube[][100],int N)
{
	int cubeA[100][100]={0},cubeB[100][100]={0},cubeC[100][100]={0},cubeD[100][100]={0};
	odd(cubeA,N/2,1);
	odd(cubeD,N/2,N*N/4+1);
	odd(cubeB,N/2,N*N/2+1);
	odd(cubeC,N/2,N*N*3/4+1);
	int mid=(N+2)/4,num=(N-2)/4;
	int i,j;
	for(j=mid;j<mid+num;j++)
		swap(cubeA[mid][j],cubeC[mid][j]);
	for(i=1;i<=N/2;i++)
		if(i!=mid)
			swap(cubeA[i][1],cubeC[i][1]);
	for(j=mid;j>mid-(num-1);j--)
		for(i=1;i<=N/2;i++)
			swap(cubeB[i][j],cubeD[i][j]);
	for(i=1;i<=N/2;i++)
		for(j=1;j<=N/2;j++)
		{
			cube[i][j]=cubeA[i][j];
	        cube[i][j+N/2]=cubeB[i][j];
			cube[i+N/2][j]=cubeC[i][j];
			cube[i+N/2][j+N/2]=cubeD[i][j];
		}
}
int main()
{
	int N,i,j,begin,sum=0;
	int cube[100][100]={0};
	printf("请输入幻方阶数：\n");
	scanf_s("%d",&N);
	if(N<=2)
	    printf("幻方不存在！\n");
	else
	{
	    printf("输出%d阶幻方：\n",N);
		if(N%2)
	    {
			printf("请输入幻方最小数字：\n");
			scanf_s("%d",&begin);
			odd(cube,N,begin);
		}
		if(!(N%4))doueven(cube,N);
		if(N%4==2&&N!=2)sineven(cube,N);
		for(i=1;i<=N;i++,putchar(10))
		{
			sum+=cube[i][1];
			for(j=1;j<=N;j++)
				printf("%4d",cube[i][j]);
		}
    printf("\n行列及对角线和为%d\n\n",sum);
	}
	return 0;
}
