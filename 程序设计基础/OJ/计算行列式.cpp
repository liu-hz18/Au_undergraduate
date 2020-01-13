//
//  Mat.cpp
//  
#include <stdio.h>
using namespace std;
const int maxn=105;
double a[maxn][maxn];
bool Judge(double x){return x>-1e-7&&x<1e-7;}
void swap(double &x,double &y){double z=x;x=y,y=z;}
int main()
{
    int n,i,j,k;
	scanf_s("%d",&n);double ans=1;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf_s("%lf",&a[i][j]);
    for(i=1;i<=n;i++){
        for(j=i;Judge(a[j][i])&&j<=n;j++);
        if(j>n){puts("empty");return 0;}
        if(i^j)for(ans=-ans,k=i;k<=n;k++)swap(a[i][k],a[j][k]);
        for(j=i+1;j<=n;j++)if(!Judge(a[j][i])){
            long double tmp=a[j][i]/a[i][i];
            for(k=i;k<=n;k++)a[j][k]-=tmp*a[i][k];
        }
    }
    for(i=1;i<=n;i++)ans*=a[i][i];
    printf("%.f\n",ans);
} 
