#include<stdio.h>
#include<math.h>
int main()
{
	int repeat,i;
	double a,b,c,s,perimeter,area;
	printf("Please input the times of repetition you want(0<repeat<10)£º");
	scanf_s("%d",&repeat);fflush(stdin);
	for(i=1;i<=repeat;i++)
		{
			printf("Please input the length of three sides:");
		    scanf_s("%lf,%lf,%lf",&a,&b,&c);
		    if((a+b>c)&&(b+c>a)&&(a+c>b))
			{
			  perimeter=a+b+c;
		      s=perimeter/2;
		      area=sqrt(s*(s-a)*(s-b)*(s-c));
			  printf("area=%.2lf,perimeter=%.2lf\n\n",area,perimeter);
			}
			else printf("These sides do not correspond to a valid triangle\n\n");
	    }
return 0;
}