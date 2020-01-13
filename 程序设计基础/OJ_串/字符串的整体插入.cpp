#include<stdio.h>
#include<string.h>
int main()
{
	char insert(char a[100],char b[100],int n);
	char a[100],b[100];int n;
	printf("please input the loacation:");
	scanf_s("%d",&n);
	printf("please input the original string:");
	scanf_s("%s",a,100);getchar();//getchar()吸收缓冲区中的回车。输入字符串是应在scanf_s中加入限定长度
	printf("please input the string being inserted:");
	scanf_s("%s",b,100);//输入字符串不需要加取址符！
	a[100]=insert(a,b,n);//输出结果出现“烫”是因为字符串没有结尾"\0",注意应加上'\0'!
    printf("%s\n",a);
return 0;
}
char insert(char a[100],char b[100],int n)
{
	char t[100];
	int len1=strlen(a);
	int len2=strlen(b);
	int i,j=0;
	for(i=n-1;i<len1;i++)t[j++]=a[i];
	int len3=j;j=n-1;
	for(i=0;i<len2;i++)a[j++]=b[i];
	for(i=0;i<len3;i++)a[j++]=t[i];
	a[j]='\0';//补充字符串结束标志
	return a[100];
}
