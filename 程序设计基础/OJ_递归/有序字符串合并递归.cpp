#include<stdio.h>
#include<string.h>
int  mystrlen(char*s){
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}
int check(char*s){
	int i,len=mystrlen(s),flag=0;
	for(i=0;i<len-1;i++){
		if(s[i]>s[i+1]){flag=1;break;}
	}
	return flag;
}
void input(char**str1,char**str2){
	while(1){
		printf("please input string1:\n");
		gets_s(*str1,100);
		printf("please input string2:\n");
		gets_s(*str2,100);
		if(check(*str1)==0&&check(*str2)==0)break;
		else printf("您输入的两个字符串不符合递增顺序！请重新输入！\n");
	}
	return ;
}
int mystrcmp(char*s1,char*s2){
	int i,flag=0;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++){
		if(s1[i]>s2[i]){flag=1;break;}
		else if(s1[i]<s2[i]){flag=-1;break;}
	}
	return flag;
}
void run(char*str1,char*str2,char**s,int *i,int *j,int *loc){
	if(*i>=mystrlen(str1)&&*j>=mystrlen(str2)){
		(*s)[mystrlen(str1)+mystrlen(str2)]='\0';
		*i=*j=*loc=0;
		return ;
	}
	if(*i<mystrlen(str1)&&*j<mystrlen(str2)){
		if(str1[*i]<str2[*j]){
			(*s)[*loc]=str1[*i];(*i)++;(*loc)++;
			run(str1,str2,s,i,j,loc);
		}
		else{
			(*s)[*loc]=str2[*j];(*j)++;(*loc)++;
			run(str1,str2,s,i,j,loc);
		}
	}else{
		if(*i==mystrlen(str1)){
			(*s)[*loc]=str2[*j];(*j)++;(*loc)++;
			run(str1,str2,s,i,j,loc);
		}
		else if(*j==mystrlen(str2)){
			(*s)[*loc]=str1[*i];(*i)++;(*loc)++;
			run(str1,str2,s,i,j,loc);
		}
	}
	return ;
}
int main(){
	char str1[100],str2[100],newstr[100],s[10];
	char *p_str1=str1,*p_str2=str2,*p=newstr;
	int i=0,j=0,loc=0;
	while(1){
		printf("程序是否继续执行？按quit 或exit结束程序:");
		gets_s(s);
		if(mystrcmp(s,"quit")==0||mystrcmp(s,"exit")==0)break;
		input(&p_str1,&p_str2);
		run(p_str1,p_str2,&p,&i,&j,&loc);
		printf("合并后的有序字符串:\n%s\n",p);
	}
	return 0;
}
