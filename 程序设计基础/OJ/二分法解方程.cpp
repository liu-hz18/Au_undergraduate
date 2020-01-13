#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,x;
	a=10.0,b=-10.0;
	double f(double x);
	do{
		x=(a+b)/2;
		if(f(x)*f(a)<0)b=x;
		if(f(x)*f(b)<0)a=x;
		if(!f(x)){printf("The solution of the equation is: x=%lf\n",x);break;}
	   }while(fabs(f(x))>1e-6);
	printf("The solution of the equation is: x=%lf\n",x);
return 0;
}
double f(double x)
{
	double f;
	f=2*x*x*x-4*x*x+3*x-6;
	return f;
}