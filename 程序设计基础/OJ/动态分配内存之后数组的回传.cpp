#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>
void CountEvensAndOdds(int a[],int n,int*counteven,int*countodd)
{
	int i;
	//此处不宜设置新的odd和even计数变量，因为会使指针指向新的地址，而这个地址在函数调用之后会消失！
	*counteven=0;
	*countodd=0;
	for(i=0;i<n;i++)
		if((*(a+i))%2)(*counteven)++;
		else (*countodd)++;
}
void Partition(int a[],int n,int**arr1,int*counteven,int**arr2,int*countodd)
//函数中的所有参数都是形参，把动态空间赋给形参是没有任何意义的，更不会改变实参，所以需要传入实参的地址
//形参为指向指针的指针，将*b和*c的地址传入,创建空间直接赋给*arr1(即b)和*arr2(即c)
//堆中申请的内存地址存放在形参*arr1中当函数结束的时候形参消失，保存的地址也就随之消失
//采用**arr1的方式可以将数组b的地址传入，将堆空间的地址存入b，c中，防止地址的丢失
//不能在子函数里释放申请的空间，函数执行完之后堆中就没有了空间，无法访问。故在main函数里释放
{
	while((*arr1=(int*)malloc((*counteven)*sizeof(int)))==NULL);
	while((*arr2=(int*)malloc((*countodd)*sizeof(int)))==NULL);
	int i,j,k;
	for(i=0,k=0,j=0;i<n;i++)
	{
		if((*(a+i)%2))*((*arr1)+k++)=*(a+i);
		else *((*arr2)+j++)=*(a+i);
	}
}
int main()
{
	int *a,n,even,odd;
	int *b,*c;//定义两个空指针*b,*c
	int *p1,*p2;
	p1=&even;
	p2=&odd;
	srand((unsigned int)time(NULL));
	n=rand()%50+1;//随机生成数组长度（1到50）
    while((a=(int*)malloc(n*sizeof(int)))==NULL);
	printf("随机数组:len=%d\n",n);
	for(int i=0;i<n;i++)
	{
		*(a+i)=rand()%100;
		printf("%3d",*(a+i));
	}
	CountEvensAndOdds(a,n,p1,p2);
	Partition(a,n,&b,p1,&c,p2);//传b,c的地址
	printf("\n奇数数组:len=%d\n",*p1);
	for(int i=0;i<(*p1);i++)
		printf("%3d",*(b+i));
	printf("\n偶数数组:len=%d\n",*p2);
	for(int i=0;i<(*p2);i++)
		printf("%3d",*(c+i));
	putchar(10);
	free(a);
	free(b);
	free(c);
return 0;
}
