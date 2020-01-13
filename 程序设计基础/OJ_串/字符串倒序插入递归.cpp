#include<stdio.h>
#include<string.h>
void tran(char*a,char*b,int i,int len,int count){
	if(i<len){
		b[count++]=a[len-1-i],b[count++]=a[i];
		tran(a,b,i+1,len,count);
	}
	if(i==len)b[count]='\0';
}
int main()
{
	char a[100],str[200];
	printf("please input str1:\n");
	gets_s(a);
	tran(a,str,0,strlen(a),0);
	printf("µ¹Ðò²åÈëºóµÄ×Ö·û´®:\n%s\n",str);
	return 0;
}
