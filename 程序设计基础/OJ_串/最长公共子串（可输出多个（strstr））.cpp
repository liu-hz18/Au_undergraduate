#include<stdio.h>
#include<string.h>
#include<malloc.h>
void search(char**str,char word[][20],int*num)
{
	char*tmp,p[100];
	char temp[100];
	temp[0]='\0';
	tmp=temp;
	int i,j,k=0,max=0,flag=0,t=*num;
	for(i=0;str[0][i]!='\0';i++)
	{
		strcpy_s(p,strlen(tmp)+1,tmp);
		*(tmp+k++)=str[0][i];
		*(tmp+k)='\0';
		for(j=1;j<3;j++)
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
			for(t=0;t<=(*num)+1;t++)word[t][0]='\0';
			(*num)=0;
			strcpy_s(word[*num],strlen(tmp)+1,tmp);
		}
		else if(k==max&&flag==1)
		{
			(*num)++;
			strcpy_s(word[*num],strlen(tmp)+1,tmp);
		}
		else if(flag==0)
		{
			k=0;
			*(tmp+k)='\0';
			for(j=1;j<3;j++)
				if(strstr(str[j],p)==NULL)
				{
					flag=0;
					break;
				}
				else flag=1;
			if(flag==1&&p[0]!='\0')i--;
		}
	}
}
int main()
{
	char word[20][20],tmp[100];
	int i,num=-1,*p;
	p=&num;
	char**str;
	str=(char**)malloc(2*sizeof(char*));
	for(i=0;i<3;i++)
		str[i]=(char*)malloc(100*sizeof(char));
	fflush(stdin);
	if(str!=NULL)
	{
		printf("please input your strings:\n");
		for(i=0;i<3;i++)
		{
			gets_s(tmp);
			strcpy_s(str[i],100,tmp);
			tmp[0]='\0';
		}
		search(str,word,p);
		if(num==-1)printf("��������Ӵ���\n");
		else{
			printf("������Ӵ���%d��\n",num+1);
			printf("������Ӵ�Ϊ:\n");
			for(i=0;i<=num;i++)
				printf("%s\n",word[i]);
		}
	}
	return 0;
}
