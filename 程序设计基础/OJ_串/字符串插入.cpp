#include<stdio.h>
#include<string.h>
void input(char**s,char**t,int*n){
	int len;
	printf("\nplease input str1:\n");
	gets_s(*s,100);
	printf("please input str2:\n");
	gets_s(*t,100);
	while(1){
		printf("please input n:");
		scanf_s("%d",n);
		len=strlen(*s);
		if(*n<0||*n>=len)printf("Wrong input!please input n again!\n");
		else break;
	}
	getchar();
	return;
}
char*insert(char*s,char*t,int n){
	int i,j,m,k=0;
	if(s[n]!=' '){
		for(m=n;s[m]!='\0'&&s[m]!=' ';m++);
	}
	if(s[m]==' '){
		k=0;
		for(i=m+1;s[i]!='\0';i++);
		for(j=i;j>m;j--){
			s[j+strlen(t)]=s[j];
		}
		s[i+strlen(t)+1]='\0';
		for(i=m+1;t[k]!='\0';i++){
			s[i]=t[k++];
		}
	}else if(s[m]=='\0'){
		k=0;
		for(i=m;t[k]!='\0';i++){
			s[i]=t[k++];
		}
		s[i]='\0';
	}
	return s;
}
int main(){
	char s[100],t[100],*ptr1=s,*ptr2=t,str[20];
	int n;
	while(1){
		printf("程序是否继续执行？按quit或exit结束程序！");
		gets_s(str);
		if(strcmp(str,"exit")==0||strcmp(str,"quit")==0)break;
		input(&ptr1,&ptr2,&n);
		printf("新字符串：%s\n",insert(s,t,n));
	}	
	return 0;
}
