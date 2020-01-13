#include<stdio.h>
#include<math.h>
void main()
{
    int s=1,i,n;
	float result=1;
	float k=1.0;
    for(i=3;(1/k)>1e-6;i+=2)
    {
	  k=i*(i-1)*k;
	  s=-s;
	  result+=(1/k)*s;
    }
	n=(i-1)/2;
	printf("result=%lf,n=%d\n",result,n);
}