#include<stdio.h>
#include<string.h>
int judge(char a)//�ж�һ����ĸ�Ƿ����ڵ���
{
	if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||a=='-')
		return 1;
	return 0;
}
void search(char*str1,char*str2,char*str3,char*word)
{
	char*tmp,*maxword;
	char temp[100];
	tmp=temp;maxword=word;
	int len[3]={strlen(str1),strlen(str2),strlen(str3)};
	int i,k,max=0;
	for(i=0;*(str1+i)!='\0';i++)
	{
		if(judge(*(str1+i)))
		{
			k=0;
				*(tmp+k++)=*(str1+i);
			*(tmp+k)='\0';
			if(k>max&&(strstr(str2,tmp)!=NULL)&&(strstr(str3,tmp)!=NULL))
			{
				max=k;
				strcpy_s(maxword,strlen(tmp)+1,tmp);
			}
		}
	}
}
void main()
{
	char word[20];
	char str[3][60]={{"What the local bus?"},{"Name some local bus."},{"A Local bus is high speed I/O close to the processor."}};
	search(*str,*(str+1),*(str+2),word);
	printf("������Ӵ�Ϊ��\n");
	printf("%s\n",word);
}
