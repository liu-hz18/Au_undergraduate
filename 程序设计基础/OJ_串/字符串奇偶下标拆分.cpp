#include<stdio.h>
#include<string.h>

void input(char**s){
	printf("please input the string:\n");
	gets_s(*s,100);
	return ;
}

void split(char*s,char**str1,char**str2){
	int i,j=0,k=0;
	for(i=0;s[i]!='\0';i++){
		if((i+1)%2){
			(*str1)[j++]=s[i];
		}else{
			(*str2)[k++]=s[i];
		}
	}
	(*str1)[j]=(*str2)[k]='\0';
}

void print(char*str1,char*str2){
	printf("ÆæÊı×Ö·û´®£º\n%s\nÅ¼Êı×Ö·û´®:\n%s\n",str1,str2);
}

int main(){
	char s[100],str1[100],str2[100],*p=s,*p_str1=str1,*p_str2=str2;
	input(&p);
	split(s,&p_str1,&p_str2);
	print(p_str1,p_str2);
	return 0;
}
