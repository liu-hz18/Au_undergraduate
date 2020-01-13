#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
	char str[200];
	int num[200],i,j,k;
	for(i=1;(str[i]=getchar())!='\n';i++);
	str[i]='\0';
	for(i=1;i<200;i++)num[i]=0;
	int len=strlen(str);
	int count=1;
	for(i=1;i<=len;i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			putchar(str[i]);
			if(!(str[i-1]>='0'&&str[i-1]<='9'))
			{
				for(j=i;str[j]>='0'&&str[j]<='9';j++);
				for(k=1;k<=j-i;k++)
					num[count]+=((int)(str[k-1+i]-'0'))*pow(10.0,j-i-k);
			}
		}
		else if(str[i-1]>='0'&&str[i-1]<='9')
		{	
		     putchar(' ');
			 count++;
		}
		else continue;
	}
	putchar(10);
	for(j=count;j>0;j--)
		for(i=1;i<j;i++)
			if(num[i]<num[i+1])
			{
				int t=num[i];
				num[i]=num[i+1];
				num[i+1]=t;
			}
    for(i=1;i<count;i++)
		printf("%d ",num[i]);
	putchar(10);
	return 0;
}

