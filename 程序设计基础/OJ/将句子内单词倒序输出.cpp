#include<stdio.h>
#include<string.h>
int main()
{
	char s[100];int len,i,j=0,t,k;
	printf("please input a string:\n");
	gets_s(s);
	len=strlen(s);
	t=0;
	for(i=len-1;i>=0;i--)
		{
			if(s[i]!=' ')t++;
			if(s[i]==' '){for(j=1;j<=t;j++)printf("%c",s[i+j]);t=0;printf("%c",s[i]);}
		}
	for(i=0;i<=t;i++)printf("%c",s[i]);//最后输出第一个单词
	printf("\n");
return 0;
}

第二种思路：
#include<stdio.h>
#include<string.h>
int main()
{
	char s[100];int len,i,j=0,t,k;
	printf("please input a string:\n");
	gets_s(s);
	len=strlen(s);
	t=0;
	for(i=len-1;i>=0;i--)
		{
			if(((s[i]<='z')&&(s[i]>='a'))||((s[i]>='A')&&(s[i]<='Z')))k=1;else k=0;
			if(k==1)t++;
			if(k==0){for(j=1;j<=t;j++)printf("%c",s[i+j]);t=0;printf("%c",s[i]);}
		}
	for(i=0;i<=t;i++)printf("%c",s[i]);
	printf("\n");
return 0;
}