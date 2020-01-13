//生成动态三维数组
#include<stdio.h>
#include<malloc.h>
int***CreateGrid(int m,int n,int t)
{
	int ***arr;
	int i,j;
    if((arr=(int***)malloc(m*sizeof(int**)))==NULL)return NULL;
	else{
		for(i=0;i<m;i++)
			if((*(arr+i)=(int**)malloc(n*sizeof(int*)))==NULL)return NULL;
			else{
				for(j=0;j<n;j++)
					if((*(*(arr+i)+j)=(int*)malloc(t*sizeof(int)))==NULL)return NULL;
			}
	}
	return arr;
}
void FreeGrid(int***arr,int n,int m,int t)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			free(*(*(arr+i)+j));
		}
		free(*(arr+i));
	}
	free(arr);
	arr=NULL;
}
int main()
{
	int m,n,t,ele=1,i,j,k;
	int*p,***a;
	p=&ele;
	printf("please input the value of m n t:");
	scanf_s("%d%d%d",&m,&n,&t);
	a=CreateGrid(m,n,t);
	if(a!=NULL)
	{
		for(i=0;i<m;i++)
			for(j=0;j<n;j++)
				for(k=0;k<t;k++)
				{
					*(*(*(a+i)+j)+k)=*p;//用整数指针赋值
					(*p)++;
				}
		printf("the array is:\n");
		for(i=0;i<m;i++,printf("\n"))
			for(j=0;j<n;j++,printf("\n"))
				for(k=0;k<t;k++)
				{
					printf("%4d",(*(a+i))[j][k]);//用指针数组输出每个平面
				}
		FreeGrid(a,m,n,t);
	}
	a=NULL;
	return 0;
}
