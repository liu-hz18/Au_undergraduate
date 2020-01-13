#include<stdio.h>
#include<string.h>
int main()
{
	char str1[20],str2[20];
	printf("Please input str1: ");
	scanf_s("%s",str1,20);
	printf("Please input str2: ");
	scanf_s("%s",str2,20);
	int i;
	int len1=strlen(str1),len2=strlen(str2);
  	int len=(len1<=len2)?len1:len2;
	for(i=0;i<len;i++)//先输出有配对字符的字符部分
	{
		putchar(str1[i]);
		putchar(str2[i]);
	}
	if(len!=len2)for(i=len;i<len2;i++)putchar(str2[i]);//再输出不能配对的剩余字符部分
	else for(i=len;i<len1;i++)putchar(str1[i]);
	printf("\n");
	return 0;
}
