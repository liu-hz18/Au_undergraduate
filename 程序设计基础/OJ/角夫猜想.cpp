#include<stdio.h>
void f(int a)
{
	while(a!=1)
	{
		printf("%d ",a);
		if(a%2)a=3*a+1;
		else a/=2;
	}
	printf("1");
}
int main()
{
	int a;
	while(1)
	{
		printf("\nplease input a number:");
		scanf_s("%d",&a);
		if(a==0)break;
		if(a<0)printf("Error!������һ����Ȼ��!");
		if(a>0)f(a);
	}
	return 0;
}
//�˳��� ��Ҫ�Ľ�
