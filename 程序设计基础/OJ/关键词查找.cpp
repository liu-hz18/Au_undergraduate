#include<stdio.h>
#include<string.h>
char**search(char*p[],char*s,char **str,int len,int*num)
{
	char**result,*re[8];//定义二级指针和指针数组
	result=re;
	int i,j,flag,count=0;
	for(i=0;i<8;i++)*(re+i)=*(str+i);//指针初始化
	for(i=0;i<8;i++)
	{
		flag=0;
		for(j=0;j<len;j++)
			if(p[i][j]!=*(s+j))
			{
				flag=-1;
				break;
			}
			if(flag==0)
			{
				strcpy_s(*(result+count),20,*(p+i));
				count++;
			}
	}
	*num=count;
	if(count>0)return result;
	else return NULL;//返回空指针
}
int main()
{
	int i,count=0,*num;
	num=&count;
	char*p[8]={"FORTRAN","PASCAL","Python","BASIC","C","C++","COBOL","SMALLTALK"};//指针数组
	char s[10],*pointer,str[8][10],*str_pointer[8];
	for(i=0;i<8;i++)*(str_pointer+i)=*(str+i);//指针数组初始化
	pointer=s;
	gets_s(s);
	int len=strlen(s);
	if((search(p,pointer,str_pointer,len,num))!=NULL)
	{
		printf("possible language:\n");
		for(i=0;i<*num;i++)printf("%s\n",*(search(p,pointer,str_pointer,len,num)+i));
	}
	else printf("NULL\n");
	return 0;
}
