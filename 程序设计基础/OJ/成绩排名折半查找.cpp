#include<stdio.h>
#include<string.h>
#include<math.h>
void swapnum(int&a,int&b){int t=a;a=b;b=t;}
void swapstr(char s1[],char s2[])
{
	char t[20];
	strcpy_s(t,20,s1);
	strcpy_s(s1,20,s2);
	strcpy_s(s2,20,t);
}
int ChangetoNum(char*str)//将字符串转化为数字
{
	int len=strlen(str);
	int num=0;
	for(int i=0;i<len;i++)
		num+=(int)pow(10.0,len-i-1)*(int)(str[i]-'0');
	return num;
}
void input(int a[],char b[][20],int c[],int n)
{
	int i;
	printf("please input the information of students:\n");
	for(i=1;i<=n;i++)
	{
		scanf_s("%d",&a[i]);
		scanf_s(" %s",b[i],20);
		scanf_s("%d",&c[i]);
		fflush(stdin);
	}
}
void rank(int a[],char b[][20],int c[],int d[],int n)
{
	int i,j;
	for(i=n;i>1;i--)//按成绩递减排序
		for(j=1;j<i;j++)
		{
			if((c[j]<c[j+1])||(c[j]==c[j+1]&&a[j]>a[j+1]))
			{
				swapnum(c[j],c[j+1]);
				swapnum(a[j],a[j+1]);
				swapstr(b[j],b[j+1]);
			}
		}
	for(i=1,d[1]=1;i<n;i++)//排名
	{
		if(c[i+1]<c[i])d[i+1]=i+1;
		else if(c[i+1]==c[i])d[i+1]=d[i];
	}
}
void bsearch(int a[],char b[][20],int c[],int d[],int n)
{
	int low,high,mid,flag,num;
	char numstr[20];
	int i,j;
	for(i=n;i>1;i--)//按学号递增排序
		for(j=1;j<i;j++)
		{
			if(a[j]>a[j+1])
			{
				swapnum(c[j],c[j+1]);
				swapnum(a[j],a[j+1]);
				swapnum(d[j],d[j+1]);
				swapstr(b[j],b[j+1]);
			}
		}
    while(1)
	{
		printf("please input the number you want to search:");
		scanf_s("%s",numstr,20);
		fflush(stdin);
		low=1;high=n;flag=0;
		if(strcmp(numstr,"0000000000")==0)break;
		else
		{
			num=ChangetoNum(numstr);
			while(low<=high)//折半查找
			{
				mid=(low+high)/2;
				if(a[mid]==num)
				{
					printf("name:%s  score:%d  rank:%d\n",b[mid],c[mid],d[mid]);
					flag=1;
					break;
				}
				else if(a[mid]<num)
					low=mid+1;
				else if(a[mid]>num)
					high=mid-1;
			}
			if(flag==0)printf("Error!this number doesn't exist!\n");
		}
	}	
}
int main()
{
	int N;
	int number[200],score[200],r[200];
	char name[200][20];
	printf("please input the number of students:");
	scanf_s("%d",&N);
	input(number,name,score,N);
	rank(number,name,score,r,N);
	bsearch(number,name,score,r,N);
	return 0;
}
