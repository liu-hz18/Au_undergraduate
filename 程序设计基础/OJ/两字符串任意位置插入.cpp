#include<stdio.h>
#include<string.h>
void mystrins(char a[],char b[],int m)
{
	char c[120];
	int len1=strlen(a),len2=strlen(b);
	int i;
	if(m>len1)
	{
		for(i=0;a[i]!='\0';i++)
			c[i]=a[i];
		for(i=0;b[i]!='\0';i++)
			c[len1+i]=b[i];
		c[len1+i]='\0';
		printf("在str1后插入str2):\n");
	}
	else if(m<0)
	{
		for(i=0;b[i]!='\0';i++)
			c[i]=b[i];
		for(i=0;a[i]!='\0';i++)
			c[len2+i]=a[i];
		c[len2+i]='\0';
		printf("在str1前连接str2):\n");
	}
	else if(m>=0&&m<=len1)
	{
		for(i=0;i<m;i++)
			c[i]=a[i];
		for(i=m;b[i-m]!='\0';i++)
			c[i]=b[i-m];
		for(i=m;a[i]!='\0';i++)
			c[len2+i]=a[i];
		c[len2+i]='\0';
		printf("在str1的第%d位插入str2):\n",m);
	}
	puts(c);
}
int main()
{
    int m;
	char str1[60],str2[60],ch=1;
	printf("请输入字符串1：\n");
	gets_s(str1);
	printf("请输入字符串2：\n");
	gets_s(str2);
	
	
		printf("请输入插入位置:");
			scanf_s("%d",&m);
			printf("新字符串(");
			mystrins(str1,str2,m);
			putchar(10);
	
return 0;
}
