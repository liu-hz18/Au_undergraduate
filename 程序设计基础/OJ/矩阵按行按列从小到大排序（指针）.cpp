#include<stdio.h>
#include<malloc.h>
void sort1(int *a[],int m,int n)//ָ������
{
	int**p;
	p=a;
	int i,j,k,min;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)//ѡ������
		{
			min=j;
			for(k=j+1;k<n;k++)
				if(*(*(p+i)+min)>*(*(p+i)+k))min=k;
			if(min!=j)
			{
				int tmp=*(*(p+i)+min);//ָ������Ԫ�ص�ָ��
				*(*(p+i)+min)=*(*(p+i)+j);
				*(*(p+i)+j)=tmp;
			}
		}
	}
}
void sort2(int *a[],int m,int n)
{
	int**p;
	p=a;
	int i,j,k,min;
	sort1(a,m,n);//��ʱÿ�����һ��Ԫ�����
	for(i=0;i<m;i++)
	{
		min=i;
		for(k=i+1;k<m;k++)
			if(*(*(p+min)+n-1)>*(*(p+k)+n-1))min=k;
		if(min!=i)
		{
			for(j=0;j<n;j++)//������
			{
				int tmp=*(*(p+min)+j);
				*(*(p+min)+j)=*(*(p+i)+j);
				*(*(p+i)+j)=tmp;
			}
		}
	}
}
void sort3(int *a[],int m,int n)
{
	int*p,*min,*k,t=0,i=0,count1=0;
	//ѡ������
	for(p=*a;count1<=m*n;p++)//ָ��һά�����ָ��
	{
		if(p==*(a+i)+n&&i<m-1)//����
		{
			i++;
			p=*(a+i);
		}
		if(p==(*(a+m-1))+n)break;
		min=p;
		count1++;
		for(k=p+1,t=i;k<=*(a+t)+n&&t<m;k++)
		{
			if(k==(*(a+t))+n&&t<m-1)//����
			{
				t++;
				k=*(a+t);
			}
			if(k==(*(a+m-1))+n)break;
			if((*min)>(*k))min=k;
		}
		if(min!=p)
		{
			int tmp=(*min);
			(*min)=(*p);
			(*p)=tmp;
		}
	}
}
int main()
{
	int m,n,**a;
	printf("please input m n:");
	scanf_s("%d%d",&m,&n);
	a=(int**)malloc(m*sizeof(int*));//��̬�����ڴ�
	for(int i=0;i<m;i++)
		*(a+i)=(int*)malloc(n*sizeof(int));
	printf("please input the elements of the matrix:\n");
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf_s("%d",(*(a+i)+j));
	sort1(a,m,n);
	printf("\nThe result of sort1:\n");
	for(int i=0;i<m;i++,putchar(10))
		for(int j=0;j<n;j++)
			printf("%4d",*(*(a+i)+j));
	sort2(a,m,n);
	printf("\nThe result of sort2:\n");
	for(int i=0;i<m;i++,putchar(10))
		for(int j=0;j<n;j++)
			 printf("%4d",*(*(a+i)+j));
	sort3(a,m,n);
	printf("\nThe result of sort3:\n");
	for(int i=0;i<m;i++,putchar(10))
		for(int j=0;j<n;j++)
			printf("%4d",*(*(a+i)+j));
	for(int i=0;i<m;i++)
		free(*(a+i));
	free(a);
	return 0;
}
