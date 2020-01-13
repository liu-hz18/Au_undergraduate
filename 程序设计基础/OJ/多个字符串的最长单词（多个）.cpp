//输出最长的多个单词
#include<stdio.h>
#include<string.h>
#include<malloc.h>
int judge(char a)
{
	if(a>='a'&&a<'z'||a>'A'&&a<'Z'||a=='-')return 1;
	return 0;
}
void search(char**str,char word[][20],int n,int*num)
{
	int max=0,i,j,k=0,flag=0,t;
	char tmp[20];
	for(i=0;str[0][i]!='\0';i++)
	{
		tmp[0]='\0';t=0;
		if(judge(str[0][i]))
		{
			t=1;
			for(j=i;judge(str[0][j])&&str[0][j]!='\0';j++)
			{
				tmp[k++]=str[0][j];
			}
			tmp[k]='\0';
			i+=k-1;
		}
		for(j=1;t==1&&j<n;j++)
		{
			if(strstr(str[j],tmp)!=NULL)
				flag=1;
			else flag=0;
		}
		if(flag==1&&max<k)
		{
			max=k;
			for(t=0;t<=(*num)+1;t++)word[t][0]='\0';//注意此处的优先级，需要加括号！！！
			(*num)=0;
			strcpy_s(word[*num],20,tmp);
		}
		else if(flag==1&&max==k)
		{
			(*num)++;
			strcpy_s(word[*num],20,tmp);
		}
		flag=0;
		k=0;
	}
}

int main()
{
	char **str;
	char maxword[20][20];
	int n,i,num=-1;
	int*p;
	p=&num;
	printf("please input the number of the strings:");
	scanf_s("%d",&n);
	printf("please input strings:（字符串长度不超过50）\n");
	str=(char**)malloc(n*sizeof(char*));
	fflush(stdin);
	for(i=0;i<n;i++)
		str[i]=(char*)malloc(52*sizeof(char));
	for(i=0;i<n;i++)
		gets_s(str[i],50);
	search(str,maxword,n,p);
	if(num==-1)printf("无公共单词!\n");
	else{
		printf("最长公共单词有%d个\n",num+1);
		for(i=0;i<=num;i++)
			printf("%s\n",maxword[i]);
	}
	return 0;
}
