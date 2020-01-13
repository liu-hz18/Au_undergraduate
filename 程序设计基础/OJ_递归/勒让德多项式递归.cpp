#include<stdio.h>
double legendre(int n,double x)
{
	if(n==0)return 1;
	else if(n==1)return (x);
	else return (((2*n-1)*x*legendre(n-1,x)-(n-1)*legendre(n-2,x))/n);
}
int main()
{
	int n;
	double x,s;
	while(1)
	{
		printf("please input the value of n and x:");
		scanf_s("%d%lf",&n,&x);
		if(n<0){
			printf("Error!Try again!\n\n");
			fflush(stdin);
		}
		else{
			 s=legendre(n,x);
			 printf("y=%.3f\n",s);
			 break;
		}
	}
return 0;
}
