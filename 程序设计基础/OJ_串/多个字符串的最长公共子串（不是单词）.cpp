#include<stdio.h>
#include<string.h>
#include<malloc.h>
void search(char**str,int n,char*word)
{
	char*tmp,*maxword;
	char temp[100];
	tmp=temp;maxword=word;
	int i,j,k=0,max=0,flag=0;
	for(i=0;str[0][i]!='\0';i++)
	{
		*(tmp+k++)=str[0][i];
		*(tmp+k)='\0';
		for(j=1;j<n;j++)
		{
			if(strstr(str[j],tmp)==NULL)
			{
				flag=0;
				break;
			}
			flag=1;
		}
		if(k>max&&flag==1)
		{
			max=k;
			strcpy_s(maxword,strlen(tmp)+1,tmp);
		}
		else{
			k=0;
			*(tmp+k)='\0';
		}
	}
}
int main()
{
	char word[20],tmp[100];
	int n,i;
	printf("please input the number of strings:\n");
	scanf_s("%d",&n);
	char**str;
	str=(char**)malloc(n*sizeof(char*));
	for(i=0;i<n;i++)
		str[i]=(char*)malloc(100*sizeof(char));
	fflush(stdin);
	if(str!=NULL)
	{
		printf("please input your strings:\n");
		for(i=0;i<n;i++)
		{
			gets_s(tmp);
			strcpy_s(str[i],100,tmp);
			tmp[0]='\0';
		}
		search(str,n,word);
		printf("最长公共子串为：\n");
		printf("%s\n",word);
	}
	else printf("分配内存失败！\n");
	return 0;
}
