#include<stdio.h>
#include<string.h>
void input(char**s){
	printf("please input your string:\n");
	gets_s(*s,100);
	return;
}
int mystrlen(char*s){
	int len;
	for(len=0;s[len]!='\0';len++);
	return len;
}
void del(char**s){
	int i,j,k;
	for(i=0;i<mystrlen(*s);i++){
		if((*s)[i]==' '){
			for(j=i;(*s)[j]==' ';j++);//j-i-1�ǿո����䳤��
			if((*s)[j]=='\0')(*s)[i+1]='\0';
			else{
				for(k=i+1;s[k]!='\0';k++){
					(*s)[k]=(*s)[k+j-i-1];
				}
			}
		}
	}
	return;
}
void split(char*s,char**str1,char**str2){
	int i,j=0,k=0,len=mystrlen(s);
	for(i=0;i<len;i++){
		//��Ҫ�ڲ�����ʹ�������жϵĲ���ʽ��Ӧ��ʹ���߼������ ���� ����
		if('0'<=s[i]&&s[i]<='9'){
			(*str1)[j]=s[i];
			(*str2)[j++]=' ';
		}else if(('a'<=s[i]&&s[i]<='z')||('A'<=s[i]&&s[i]<='Z')){
			(*str1)[j]=' ';
			(*str2)[j++]=s[i];
		}else{
			printf("Error!Wrong input!\n");
			return ;
		}
	}
	(*str1)[j]='\0';(*str2)[j]='\0';
	del(str1);del(str2);
	return ;
}
void print(char*s,char*s1,char*s2){
	printf("ԭʼ�ַ���:\n%s\n�����ַ���:\n%s\n��ĸ�ַ���:\n%s\n�������ַ��� �� ��'@'��������\n",s,s2,s1);
	return;
}
int main(){
	char ch,s[100],str1[100],str2[100],*p=s,*ptr1,*ptr2;
	ptr1=str1,ptr2=str2;
	printf("�������ַ��� �� ��'@'��������");
	while((ch=getchar())!='@'){
		//getchar�������ջس���������������һ��getchar!!
		input(&p);
		split(p,&ptr1,&ptr2);
		print(p,ptr1,ptr2);
	}
	return 0;
}
