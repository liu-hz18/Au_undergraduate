#include <stdio.h>
#include <math.h>
 int main()
{
	double d;
	int a,b,c;
	double x1,x2;
	double f;
	printf("������a,b,c��");
	scanf_s("%d,%d,%d",&a,&b,&c);
	d = b*b-4*a*c;
	f = sqrt(d);
	  if( d > 0)
	  {
		  x1 = ( ( -1 ) * b + f ) / ( 2 * a );	
		  x2 = ( ( -1 ) * b - f ) / ( 2 * a ); 
		  printf("������ʵ����x1 = %f  x2 = %f\n",x1,x2);
	  }
	  else if( d == 0 )
	  {
		  x1 = ( ( -1 ) * b ) / ( 2 * a );
		  printf("�˷���ֻ��һ��ʵ����x1 = x2 = %f\n",x1);
	  }
	  else
		  printf("�˷���û��ʵ��\n");
   return 0;
}
 