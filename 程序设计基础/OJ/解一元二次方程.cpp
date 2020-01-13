#include <stdio.h>
#include <math.h>
 int main()
{
	double d;
	int a,b,c;
	double x1,x2;
	double f;
	printf("请输入a,b,c：");
	scanf_s("%d,%d,%d",&a,&b,&c);
	d = b*b-4*a*c;
	f = sqrt(d);
	  if( d > 0)
	  {
		  x1 = ( ( -1 ) * b + f ) / ( 2 * a );	
		  x2 = ( ( -1 ) * b - f ) / ( 2 * a ); 
		  printf("有两个实根：x1 = %f  x2 = %f\n",x1,x2);
	  }
	  else if( d == 0 )
	  {
		  x1 = ( ( -1 ) * b ) / ( 2 * a );
		  printf("此方程只有一个实根：x1 = x2 = %f\n",x1);
	  }
	  else
		  printf("此方程没有实根\n");
   return 0;
}
 