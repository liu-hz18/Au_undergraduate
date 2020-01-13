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
         //�ӶԽ���Ԫ�ؿ�ʼ��������ÿ�е�Ԫ��,ֱ��ĳһ�г��ַ���Ԫ������ѭ��
		        for(j=i;j<=m&&Cmp(a[j][i]);j++);
				if(j>m)continue;//����n�ͻ���һ��
				if(i^j)//i!=j
					for(k=1;k<=n;k++)
						swap(a[i][k],a[j][k]);//��a[i][i]Ϊ��ʱ��Ϊʹ����㣬������i�к͵�j��
				for(j=1;j<=m;j++)//��j=1��ʼ�ǹؼ����������ջ�ʹ����Ϊ�ԽǾ�������������Ǿ���
				{
					if(i^j&&!Cmp(a[j][i]))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n;k++)
						{
							a[j][k]-=a[i][k]*tmp;//�õ�i����ȥ��j�У�ʹ�õ�j�еĵ�j��Ԫ��Ϊ0��
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