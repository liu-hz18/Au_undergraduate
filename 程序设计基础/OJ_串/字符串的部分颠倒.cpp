#include<stdio.h>
int main()
{
	void move(int*p,int x,int y);
	int m,n,a[100];
	int *pointer;
	pointer=a;
	printf("please input the value of n:");
	scanf_s("%d",&n);
	printf("please inpuit the elements of a[]:\n");
	for(int i=1;i<=n;i++)
		scanf_s("%d",pointer+i);//pointer+i=&a[i]
	while(1)
	{
		printf("please input the value of  m:");
			scanf_s("%d",&m);
		if(m>=0&&m<=n)break;//判断输入是否合理
		else printf("Error!please input m again!\n");
	}
	move(pointer,n,m);
	for(int i=1;i<=n;i++)
	{
		printf("%d ",*(pointer+i));//*(pointer+i)=a[i];
	}
	putchar(10);
	return 0;
}
void move(int*p,int x,int y)
{
	for(int i=x;i>0;i--)
		*(p+i+y)=*(p+i);//*(p+i+x)=a[i+x]
	for(int i=x+1;i<=x+y;i++)
		*(p+i-x)=*(p+i);
}

