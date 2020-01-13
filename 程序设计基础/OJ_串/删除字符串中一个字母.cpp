#include<stdio.h>
#include<string.h>
int main()
{
	char a[100],ch;
	printf("please input the string: ");
	scanf_s("%s",a,100);
	printf("please input the char you want to delete: ");
	getchar();
	scanf_s("%c",&ch);
	int len=strlen(a);
    for(int i=0;i<=len;i++)
		if(a[i]==ch)for(int j=i+1;j<=len+1;j++)a[j-1]=a[j];
	printf("the new string is: %s\n",a);
	return 0;
}
