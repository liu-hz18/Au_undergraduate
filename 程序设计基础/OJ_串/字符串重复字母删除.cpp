//�ַ���ѹ��
#include<stdio.h>
#include<string.h>
char*StringCompression(char*p,int n)
{
	int i,j,k=0;
	int count;
	static char b[200];
	char*pointer;
	pointer=b;
	for(i=0;i<n;i++)
	{
		if(*(p+i)==' ')
			*(pointer+k++)=*(p+i);
		else{
			for(count=0,j=0;j<i;j++)
			{
				if(*(p+j)==*(p+i))count++;
			}
			if(count==0||count==2||count==5)
				*(pointer+k++)=*(p+i);
			//���ַ�������һ���µ����飬��������õı�����ԭ���ַ��������ʣ�ʹ�ô����ļ�������������
		}
	}
	*(pointer+k)='\0';
	return (pointer);
}
int main()
{
	char s[200];
	char*pointer,*newstr;
	int len;
	pointer=s;
	printf("please input a string:\n");
	gets_s(s);
	len=strlen(s);
	newstr=StringCompression(pointer,len);
	printf("the new string is:\n%s\n",newstr);
	return 0;
}
