//
//最长单词查找，支持标点符号和连字符‘-’
#include<stdio.h>
#include<string.h>
int judge(char a)
{
	int k;
	if((a>='a'&&a<='z')||(a>='A')&&(a<='Z')||a=='-')k=1;
	else k=0;
	return k;
}
char *search(char s[],int n)
{
	int i,j,k=1,count[100],max=0;
	static char b[20];
	if(judge(s[0]))
	{
		for(i=0;s[i]!=' ';i++);
		count[0]=i;
		max=count[0];
	}
    for(i=0;i<n;i++)
		if(!judge(s[i])&&judge(s[i+1]))
		{
			for(j=i+1;judge(s[j]);j++);
      		count[k]=j-i-1;
			if(count[k]>max)max=count[k];
			k++;
			i=j-1;
		}
	if(judge(s[0]))
	{
		for(i=0;judge(s[i]);i++);
		if(max==i)
		{
			for(j=0,i=0;s[i]!=' ';i++)
				b[j++]=s[i];
		}
	}
    for(i=0;i<n;i++)
		if(!judge(s[i])&&judge(s[i+1]))
		{
			for(j=i+1;judge(s[j]);j++);
    		if(max==j-i-1)
			{
				for(j=0,i=i+1;judge(s[i]);i++)
				{
					b[j++]=s[i];
				}
				break;
			}
			i=j-1;
		}
	b[j]='\0';
	return b;
}
int main()
{
	int i;
	char s[1000];
	for(i=0;(s[i]=getchar())!='\n';i++);
	s[i]='\0';
	printf("最长单词为:\n");
	puts(search(s,i));
return 0;
}
