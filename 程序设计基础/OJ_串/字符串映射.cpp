#include<stdio.h>
#include<malloc.h>
void inputStr(char**s){
	printf("请输入字符串：\n");
	gets_s(*s,20);
}
int mystrlen(char*s){
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}
void inputSeq(char**strnum,char*s){
	int flag=1,i,num[20];
	while(1){
		flag=1;
		printf("请输入仅由数字构成的字符串:\n");
		gets_s(*strnum,20);
		if(mystrlen(*strnum)!=mystrlen(s))flag=0;	
		for(i=0;i<mystrlen(s);i++)num[i]=0;
		for(i=0;(*strnum)[i]!='\0';i++){
			num[(*strnum)[i]-'0']++;
		}
		for(i=0;i<mystrlen(*strnum);i++){
			if(num[i]!=1){
				flag=0;break;
			}
		}
		if(flag==0)printf("您的输入有误！请重新输入!\n");
		else if(flag==1)break;
	}
}
char*mapping(char*s,char*t){
	int i;
	char*newstr;
	newstr=(char*)malloc(20*sizeof(char));
	for(i=0;i<mystrlen(t);i++){
		newstr[t[i]-'0']=s[i];
	}
	newstr[i]='\0';
	return newstr;
}
int main(){
	char s[20],*p=s,strnum[20],*ptr=strnum,ch,*newstr;
	while((ch=getchar())!='@'){
		inputStr(&p);
		inputSeq(&ptr,p);
		newstr=mapping(s,strnum);
		printf("映射后的字符串：%s\n",newstr);
		free(newstr);
		printf("是否继续？按@结束程序\n");
	}
	return 0;
}
