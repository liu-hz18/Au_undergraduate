//数组静态分区。
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void CountEvensAndOdds(int *a,int len,int*even,int*odd)
{
	int i;
	for(i=0;i<len;i++)
	{
		if((*(a+i))%2)(*even)++;
		else (*odd)++;
	}
}
void Partition(int *a,int len,int*evens,int*len_even,int*odds,int*len_odd)
{
	int i,j=0,k=0;
	CountEvensAndOdds(a,len,len_even,len_odd);
	for(i=0;i<len;i++)
	{
		if((*(a+i))%2)
		{
			*(evens+j++)=*(a+i);
		}
		else
		{
			*(odds+k++)=*(a+i);
		}
	}
}
int main()
{
	int a[100],evens[100],odds[100],n,len_even=0,len_odd=0;
	int*p1,*p2;
	p1=&len_even;
	p2=&len_odd;
	while(1)
	{
		printf("please input n:");
		scanf_s("%d",&n);
		if(n>=0&&n<100)
		{
			srand((unsigned)time(NULL));
			for(int i=0;i<n;i++)
				a[i]=rand()%100+1;
			Partition(a,n,evens,p1,odds,p2);
			printf("\n原始数组：len=%d\n",n);
			for(int i=0;i<(*p1)+(*p2);i++)
				printf("%3d",a[i]);
			printf("\n奇数数组：len=%d\n",*p1);
			for(int i=0;i<*p1;i++)
				printf("%3d",evens[i]);
			printf("\n偶数数组：len=%d\n",*p2);
			for(int i=0;i<*p2;i++)
				printf("%3d",odds[i]);
			putchar(10);
			break;
		}
		else printf("Error!please input 0<=n<100!\n"); 
	}
	return 0;
}
