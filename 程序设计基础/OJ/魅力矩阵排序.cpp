#include<stdio.h>
#include<math.h>
int main()
{
	int m,n,a[22][22],b[21][21],tmp[110];
	printf("Please input the value of m and n:");
	scanf_s("%d%d",&m,&n);
	int i,j,t,k=1,flag;
	printf("Please input the elements of a:\n");
	for(i=1;i<=m;i++)for(j=1;j<=n;j++)scanf_s("%d",&a[i][j]);
	printf("\n Matrix a:\n");
	for(i=1;i<=m;i++)//�������a
	{
		for(j=1;j<=n;j++)printf("%4d",a[i][j]);
		printf("\n");
	}
	printf("\n Matrix b:\n");
	for(i=0;i<=m;i++){a[i][0]=0;a[i][n+1]=0;}
	for(j=0;j<=n;j++){a[0][j]=0;a[m+1][j]=0;}//ʹ�߽�Ԫ�ص�ֵΪ0
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			b[i][j]=a[i-1][j]+a[i+1][j]+a[i][j-1]+a[i][j+1];
	for(i=1;i<=m;i++)//�������b���������һά����tmp
	{
		for(j=1;j<=n;j++)
		{
			tmp[k]=b[i][j];
			k++;
			printf("%4d",b[i][j]);
		}
		printf("\n");
	}
	printf("\n Matrix c:\n");

	for(k=m*n;k>=1;k--)//ð������
		for(j=1;j<k;j++)
			if(tmp[j]<tmp[j+1]){t=tmp[j];tmp[j]=tmp[j+1];tmp[j+1]=t;}
    for(k=1;k<=m*n;k++)//�ҵ�b��������tmp[k]��Ӧ��Ԫ�ز��������a�еĶ�ӦԪ��
	{
		flag=0;
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=n;j++)
	    	   if(b[i][j]==tmp[k])
			   {
				   printf("%4d",a[i][j]);
				   b[i][j]=tmp[1]+1;
				   flag=1;
				   break;
			   }
            if(flag)break;
		}
	    if(!(k%n))printf("\n");//ÿ�е�Ԫ�������ʱ������
	}
	printf("\n");
	return 0;
}
