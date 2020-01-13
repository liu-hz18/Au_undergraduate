#include<stdio.h>
#include<math.h>
int main()
{
  int i,m,n,t,j,k=0,sum=0;
  printf("Please input m and n:");
  scanf_s("%d %d",&m,&n); 
  for(i=m;i<=n;i++)
  {
	  t=sqrt((double)i);
	for(j=2;j<=t+1;j++)
		{
			if(!(i%j))break;
			if(j>=t+1){k+=1;sum=sum+i;break;}
		}
   }
   if(m==2){k+=1;sum+=2;}
   if(m==1)sum+=1;
   printf("numbers are %d,sum is %d\n",k,sum);
return 0;
}
