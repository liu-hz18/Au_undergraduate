#include<stdio.h>
#include<string.h>
int main()
{
	char insert(char a[100],char b[100],int n);
	char a[100],b[100];int n;
	printf("please input the loacation:");
	scanf_s("%d",&n);
	printf("please input the original string:");
	scanf_s("%s",a,100);getchar();//getchar()���ջ������еĻس��������ַ�����Ӧ��scanf_s�м����޶�����
	printf("please input the string being inserted:");
	scanf_s("%s",b,100);//�����ַ�������Ҫ��ȡַ����
	a[100]=insert(a,b,n);//���������֡��̡�����Ϊ�ַ���û�н�β"\0",ע��Ӧ����'\0'!
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
	a[j]='\0';//�����ַ���������־
	return a[100];
}
