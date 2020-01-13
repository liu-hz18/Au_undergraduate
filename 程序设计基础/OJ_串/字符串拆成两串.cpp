#include<stdio.h>
void input(char*str,int *n){
	printf("please input str:\n");
	gets_s(str,100);
	printf("please input the location you want to split:");
	scanf_s("%d",n);
	getchar();
}
void split(char*str,int n,char*str1,char*str2){
	int i;
	for(i=0;str[i]!='\0';i++){
		if(i>=n)str2[i-n]=str[i];
		else if(i<n)str1[i]=str[i];
	}
	str2[i-n]='\0';
	str1[n]='\0';
}
void output(char*str1,char*str2){
	printf("str1:%s    str2:%s\n",str1,str2);
	printf("按任意键继续，@结束程序");
}
int main(){
	int n;char str[100],str1[100],str2[100],ch;
	while((ch=getchar())!='@'){
		input(str,&n);
		split(str,n,str1,str2);
		output(str1,str2);
	}
	return 0;
}