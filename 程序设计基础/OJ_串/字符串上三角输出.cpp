#include<stdio.h>

void input(char**s){
	printf("ÇëÊäÈë×Ö·û´®:\n");
	gets_s(*s,100);
}
int mystrlen(char*s){
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}
int mystrcmp(char*s1,char*s2){
	int i,flag=0;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++){
		if(s1[i]>s2[i]){flag=1;break;}
		else if(s1[i]<s2[i]){flag=-1;break;}
	}
	return flag;
}
void triangle_matrix(char*s){
	int i,j;
	for(i=mystrlen(s)-1;i>=0;i--){
		for(j=0;j<i;j++)printf("%d ",j);
		printf("%c\n",s[j]);
	}
}
int main(){
	char s[100],*p=s;
	while(1){
		input(&p);
		if(s[0]=='\0')
		{
			printf("³ÌÐò½áÊø£¡\n");
			break;
		}
		triangle_matrix(s);
	}
	return 0;
}