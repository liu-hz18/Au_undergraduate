#include <stdio.h>
#include <math.h>
#include<stdlib.h>
const int maxn=205;
double a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
bool Cmp(double x){return x<1e-7&&x>-1e-7;}//精度接近0就返回1；否则返回0；
void swap(double&c,double&d){double temp=c;c=d;d=temp;}
//声明在主函数之前的函数，主函数中不需要进行函数调用；
//在主函数之后定义的函数需要在主函数中进行函数调用。
//全局变量中的字母在后续函数体中不可再出现。
int main()
{
	system("color 30");
	char ch;
	printf("Please input the letter code for the operation you want to perform:\nA/解线性方程组,B/计算行列式,C/求方块矩阵的逆,D/矩阵乘法,E/求伴随矩阵,F/求秩,Q/退出程序:");
	int n,i,j,k,m,l,judge=0;
	double tmp,result=1.0;
    while((ch=getchar())!='Q')
	{
	 switch(ch)
	 {
	   case'A':
	   {
			puts("please input the number of equations:");
	        scanf_s("%d",&n);
			puts("please input the coefficient ([A|b]) of each equaltion:");
            for(i=1;i<=n;i++)for(j=1;j<=n+1;j++)scanf_s("%lf",&a[i][j]);
            for(i=1;i<=n;i++)
	        {
                //从对角线元素开始，纵向检查每列的元素,直到某一行出现非零元素跳出循环
		        for(j=i;j<=n&&Cmp(a[j][i]);j++);
				if(j>n)continue;//超过n就换下一列
				if(i^j)//i!=j
					for(k=0;k<=n+1;k++)
						swap(a[i][k],a[j][k]);//在a[i][i]为零时，为使其非零，交换第i行和第j行
				for(j=1;j<=n;j++)//从j=1开始是关键，这样最终会使矩阵化为对角矩阵而不是上三角矩阵。
				{
					if(i^j&&!Cmp(a[j][i]))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n+1;k++)
						{
							a[j][k]-=a[i][k]*tmp;//用第i行消去第j行，使得第j行的第j行元素为0；
						}
					}
				}
				puts("=");
				for(j=1;j<=n;j++,putchar(10))//10对应ASCII码中的换行！
				{
					 for(k=1;k<=n+1;k++)
					printf("%.3f ",a[j][k]);
				}
             }
			//Gauss消元结束,此时化为了对角矩阵，上下三角均为0，下面输出结果
			printf("\nThe solution is:\n");
			for(i=1;i<=n;i++)
			{
				if(Cmp(a[i][i])&&(!Cmp(a[i][n+1])))
				{
				printf("\nNo solution.\n");
				judge=1;
				break;
				}
			}
			if(!judge)
			{
				for(i=1;i<=n;i++)
				{
					if(Cmp(a[i][i]))
					{
						if(Cmp(a[i][n+1]))printf("x%d=Arbitrary.\n",i);
					}
					else printf("x%d=%.3f\n",i,a[i][n+1]/a[i][i]);
				}
			}
		break;
		}
	   case'B':
		{
			printf("please input the order of determinant:");
			scanf_s("%d",&n);
			printf("please input the elements of the determinant:\n");
			for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
			for(i=1;i<=n;i++)
			{
				for(j=i;j<=n&&Cmp(a[j][i]);j++);
				if(j>n)continue;
				if(j!=i)
				{
					result*=-1.0;
					for(k=1;k<=n;k++)
					{
							swap(a[i][k],a[j][k]);
					}
				}
				for(j=1;j<=n;j++)
				{
					if((j!=i)&&(!Cmp(a[j][i])))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n;k++)
					    {
						    a[j][k]-=tmp*a[i][k];
						}
					}
				}
			}
			for(i=1;i<=n;i++)
			{
				if(i==(n+1)/2)printf("%2.0lf * |",result);
				else printf("     |");
				for(j=1;j<=n;j++)
					printf("%6.3lf ",a[i][j]);
				printf("|\n");
			}
			for(i=1;i<=n;i++)
				result=result*a[i][i];
			printf("result=%.3lf\n",result);
			break;
		}
	   case'C':
	   {
		   printf("please input the order of the matrix:");
			scanf_s("%d",&n);
			for(i=1;i<=n;i++)for(j=1;j<=n;j++){if(i!=j)b[i][j]=0;else b[i][j]=1;}
			printf("please input the elements of the matrix:\n");
			for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
			for(i=1;i<=n;i++)
			{
				for(j=i;j<=n&&Cmp(a[j][i]);j++);
				if(j>n)continue;
				if(j!=i)
				{
					for(k=1;k<=n;k++)
					{
							swap(a[i][k],a[j][k]);
					        swap(b[i][k],b[j][k]);
					}
				}
				for(j=1;j<=n;j++)
				{
					if((j!=i)&&(!Cmp(a[j][i])))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n;k++)
					    {
						    a[j][k]-=tmp*a[i][k];
							b[j][k]-=tmp*b[i][k];
						}
					}
				}
			}
			for(i=1;i<=n;i++)result*=a[i][i];
			if(result)
			{
			printf("\nA^(-1) is:\n");
			for(i=1;i<=n;i++)
			 {
				printf(" |");
				for(j=1;j<=n;j++)
					printf("%6.3lf ",b[i][j]/a[i][i]);
				printf("|\n");
			}
			}
			else printf("This matrix is irreversible!\n");
			break;
	    }
	   case'D':
	   {
			printf("As for A[k][l],B[l][s],please input k,l,s:");
			int k,l,s;int i,j,m;
			scanf_s("%d%d%d",&k,&l,&s);
			printf("please input matrix A:\n");
			for(i=1;i<=k;i++)for(j=1;j<=l;j++)scanf_s("%lf",&a[i][j]);
			printf("please input matrix B:\n");
			for(i=1;i<=l;i++)for(j=1;j<=s;j++)scanf_s("%lf",&b[i][j]);
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
				for(j=1;j<=s;j++)printf("%6.2f",c[i][j]);
				printf("\n");
			}
			break;
        }
	   case 'E':
		{
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
			break;
		  }
	   case 'F':
	  {
            int rank=0;
			printf("please input the row and column:");
			scanf_s("%d%d",&m,&n);
			printf("please input the elements of the matrix:\n");
			for(i=1;i<=m;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
			for(i=1;i<=n;i++)
			{
                 for(j=i;j<=m&&Cmp(a[j][i]);j++);
				 if(j>m)continue;
				 if(i^j)
					 for(k=1;k<=n;k++)
						swap(a[i][k],a[j][k]);
				 for(j=1;j<=m;j++)
				 {
					if(i^j&&!Cmp(a[j][i]))
					{
						tmp=a[j][i]/a[i][i];
						for(k=1;k<=n;k++)
						{
							a[j][k]-=a[i][k]*tmp;
						}
					}
				 }
			}
			for(i=1;i<=m;i++,putchar(10))
				for(j=1;j<=n;j++)
					printf("%7.2lf",a[i][j]);
			for(i=1;i<=((m<=n)?m:n);i++)
				if(!Cmp(a[i][i]))rank++;
			printf("Rank=%d\n",rank);
		  break;
	  }
      default: 
	   {
			 printf("Unreasonable input!Please try again!\n");
			 break;
		} 
       }
		fflush(stdin);
		printf("\nPlease input the letter code for the operation you want to perform:\nA/解线性方程组,B/计算行列式,C/求方块矩阵的逆,D/矩阵乘法,E/求伴随矩阵,F/求秩,Q/退出程序:");
	   }
   system("pause");
   return 0;
}
