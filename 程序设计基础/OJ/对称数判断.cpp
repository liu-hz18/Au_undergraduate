#include<stdio.h>
#include<math.h>
int main()
{
	int Begin=95859,End,delta;
	int v;
	int Judge(int x);
	if(Judge(12345))printf("1");
	for(End=95859+30*2;End<=95859+120*2;End++)
    {
		delta=End-Begin;
		if(Judge(End))
		{
			v=delta/2;
			printf("The symmetrical number is: %d\nThe speed is:%3d km/h\n",End,v);
		}
	}
return 0;
}

int Judge(int x)//判断一个五位数是否为对称数
{
	int a[6],i=1,flag=1;
	for(i=1;i<=5;i++)
	{
		a[i]=x%10;
		x/=10;
	}
	for(i=1;i<=3;i++)
		if(a[i]!=a[6-i]){flag=0;break;}
	return flag;
}
