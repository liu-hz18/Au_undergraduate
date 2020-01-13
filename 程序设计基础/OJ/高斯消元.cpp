//Gauss消元
、
#include <stdio.h>

using namespace std;
const int maxn=205;
double a[maxn][maxn];

bool Cmp(double x){return x<1e-7&&x>-1e-7;}

void Swap(double &x,double &y){double z=x;x=y,y=z;}//定义交换函数

int main()
{
    
int n,i,j,k;double tmp;
    
scanf_s("%d",&n);
   
 for(i=1;i<=n;i++)
for(j=1;j<=n+1;j++)
scanf_s("%lf",&a[i][j]);//输入一个二维数组
   
 for(i=1;i<=n;i++){
       
 for(j=i;j<=n&&Cmp(a[j][i]);j++);
      
  if(j>n)continue;
        
if(i^j)//ij均不为0
			
for(k=0;k<=n+1;k++)Swap(a[i][k],a[j][k]);//第i行和第j行交换
           
 for(j=1;j<=n;j++)
			
if(i^j&&!Cmp(a[j][i]))
            
for(tmp=a[j][i]/a[i][i],k=1;k<=n+1;k++)
                
a[j][k]-=a[i][k]*tmp;//用第i行乘以某个系数后消去第j行的第一个元素
       
 for(puts("="),j=1;j<=n;j++,putchar(10))
        
    for(k=1;k<=n+1;k++)
printf("%.3f ",a[j][k]);
    }
   
 for(i=1;i<=n;i++)
     
   printf("x%d=",i),Cmp(a[i][i])?
     
   puts(Cmp(a[i][n+1])?"Infinite.":"No solution."):
    
    printf("%.3f\n",a[i][n+1]/a[i][i]);
}

