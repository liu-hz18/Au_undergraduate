#include<stdio.h>
#include<string.h>

void strsearch(char a[],char b[],int*s)
{
	int len2=strlen(b);
	int i,j,flag;
	for(i=0;a[i]!='\0';i++)
		if(a[i]==b[0])
		{
			flag=1;
			for(j=i+1;j<i+len2;j++)
				if(a[j]!=b[j-i])
				{
					flag=0;
					break;
				}
			if(flag)s[1]++;
			if(s[1]==1)s[0]=i+1;
		}
}
int main()
{
	char a[100],b[100];
	int result[2]={-1,0};
	printf("please input str1:\n");
	gets_s(a);
	printf("please input str2:\n");
	gets_s(b);
	strsearch(a,b,result);
	if(result[1])
		printf("\n首次出现位置:第%d位\n出现次数:%d次\n",result[0],result[1]);
	else
		printf("\n %d (未出现)\n次数：%d\n",result[0],result[1]);
	return 0;
}
