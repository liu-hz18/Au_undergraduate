#include<stdio.h>
#include<math.h>
const int maxn=205;
double a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
bool Cmp(double x){return fabs(x)<1e-7;}
void swap(double&y,double&z){double temp=y;y=z;z=temp;}
int main()
{
	int i,j,m,k,n,l;
	double tmp,det=1.0,t;
	printf("please input the order of matrix A:");
	scanf_s("%d",&n);
	printf("please inut the elements of matrix A:\n");
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			det=1.0;
			for(m=1;m<n;m++)
			{
				if(m<i)
					for(k=1;k<n;k++)
					{
						if(k<j)b[m][k]=a[m][k];
						else if(k>=j)b[m][k]=a[m][k+1];
					}
				else if(m>=i)
					for(k=1;k<n;k++)
					{
						if(k<j)b[m][k]=a[m+1][k];
						else if(k>=j)b[m][k]=a[m+1][k+1];
					}
			}
            for(k=1;k<n;k++)
			{
				for(m=k;m<n&&Cmp(b[m][k]);m++);
				if(m>=n)continue;
				if(m!=k)
					for(l=1;l<n;l++)
						swap(b[m][l],b[k][l]);
                for(m=1;m<n&&m!=k;m++)
				{
					tmp=b[m][k]/b[k][k];
					for(l=1;l<n;l++)
						b[m][l]-=tmp*b[k][l];
				}
			}
			for(k=1;k<n;k++)det*=b[k][k];
			c[i][j]=det;
		}

		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{	
				t=1.0;
				for(m=1;m<=i+j;m++)t*=-1.0;
		        c[i][j]*=t;
			}
		printf("matrix A* is:\n");
        for(i=1;i<=n;i++,putchar(10))
			for(j=1;j<=n;j++)
				printf("%8.2f",c[j][i]);
		return 0;
}
