#include<stdio.h>
#include<string.h>

int main()
{
	char str1[100],str[10];
	int i,j,k;
    printf("Please input str1: ");
	scanf_s("%s",str1,100);
	getchar();
	printf("Please input str: ");
	scanf_s("%s",str,10);
	int len1=strlen(str1),len2=strlen(str);
	printf("The new string is: ");
	for(i=0;i<len1;i++)
	{
	   k=1;
	   for(j=0;i+j<len1&&j<len2;j++)
		   if(str1[i+j]!=str[j]){k=0;break;}
	   if(!k)putchar(str1[i]);
	   else i+=len2-1;
	}
	printf("\n");
	return 0;
}
