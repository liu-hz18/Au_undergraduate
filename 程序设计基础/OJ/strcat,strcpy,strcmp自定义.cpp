#include<stdio.h>
#include<string.h>
char*strncpy(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=strlen(s);
	len2=strlen(t);
	if(len2<n)n=len2;//对于n超过t的长度的处理
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+i)=*(t+i);
	if(len1<n)*(s+n)='\0';
	return(s);
}
char*strncat(char*s,char*t,int n)
{
	int i,len1,len2;
	len1=strlen(s);
	len2=strlen(t);
	if(len2<n)n=len2;//对于n超过t的长度的处理
	for(i=0;i<n&&*(t+i)!='\0';i++)
		*(s+len1+i)=*(t+i);
    *(s+len1+n)='\0';
	return(s);
}
int strncmp(char*s,char*t,int n)
{
	int m,i=1;
	while(*s==*t)
	{
		if(i==n||*s=='\0'||*t=='\0')return 0;
		s++;
		t++;
		i++;
	}
	m=*s-*t;
	if(m>0)m=1;
	else m=-1;
	return m;
}
void input(char*s,char*t,int*n)
{
	printf("please input str1:\n");
    gets_s(s,100);
	int len=strlen(s);
	printf("please iput str2:\n");
	gets_s(t,100);
	printf("please input n:");
	scanf_s("%d",n);
}
int main()
{
	char a[100],b[100];
	char*p1,*p2;
	int cmp,n,*p,len;
	p1=a;p2=b;p=&n;
	input(p1,p2,p);
	len=strlen(p1);
	cmp=strncmp(p1,p2,*p);
	printf("\nstrncmp函数：%d\n",cmp);
	strncat(p1,p2,*p);
    printf("strncat函数：\n%s\n",p1);
	*(p1+len)='\0';//重置字符串a为初始输入值
	strncpy(p1,p2,*p);
	printf("strncpy函数：\n%s\n",p1);
    return 0;
}
