//������������,֧�����ַ�'-',������������Ӵ�������
//������"aaaaa""aaaa""aaa"ʱ�������ǲ�ͬ�ĵ��ʣ���˻���Ϊû����������ʣ���
#include<stdio.h>
#include<string.h>
#include<malloc.h>
int judge(char a)//�ж�һ����ĸ�Ƿ����ڵ���
{
	if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='-')
		return 1;
	return 0;
}
void search(char**str,int n,char*word)
{
	char*tmp,*maxword;
	char temp[100];
	tmp=temp;maxword=word;
	int i,j,k,t,max=0,flag=0;
	for(i=0;(str[0][i])!='\0';i++)
	{
		if(judge(str[0][i]))
		{
			k=0;
			for(j=i;judge(str[0][j])&&(str[0][j])!='\0';j++)
			{
				*(tmp+k++)=(str[0][j]);
			}
			*(tmp+k)='\0';
			for(t=1;t<n;t++)
			{
				if(strstr(str[t],tmp)==NULL)
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
			i+=k-1;
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
		printf("���������Ϊ��\n");
		printf("%s\n",word);
	}
	else printf("�����ڴ�ʧ�ܣ�\n");
	return 0;
}
