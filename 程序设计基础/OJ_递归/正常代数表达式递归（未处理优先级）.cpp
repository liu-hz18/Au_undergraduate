//如何处理优先级的问题？？？
#include<stdio.h>
#include<math.h>
#include<string.h>
double calculation(double a,double b,char c)
{
	double result;
	switch(c){
	case '+':result=a+b;break;case '-':result=a-b;break;
	case '*':result=a*b;break;case '/':result=a/b;break;
	case '^':result=pow(a,b);break;
	}
	return result;
}
int judge(char x){
	if(x>='0'&&x<='9')return 1;
	if(x=='+'||x=='-'||x=='*'||x=='/'||x=='^')return 0;
	else return -1;
}
char*move(char*str,int i){
	int k;
	for(k=i;str[k+2]!='\0';k++){
		str[k]=str[k+2];
	}
	str[k]='\0';
	return str;
}
//递归检查表达式是否正确
void Check(char*str,int i,int*flag){
	if(judge(str[i])==1)Check(str,i+1,flag);
	else if(judge(str[i])==0){
		if(judge(str[i-1])!=1||judge(str[i+1])!=1){*flag=0;return ;}
		else{
			str[i-1]='1';
			move(str,i);
			Check(str,i,flag);
		}
	}
	else if(judge(str[i])==-1){*flag=0;return;}
	if(str[i]=='\0'){*flag=1;return;}
}
//递归实现计算
void run(char*str,int i,double*result){
	if(judge(str[i])==1)run(str,i+1,result);
	else if(judge(str[i])==0){
		str[i-1]=(char)(((*result)=calculation(str[i-1]-'0',str[i+1]-'0',str[i]))+'0');
		move(str,i);
		run(str,i,result);
	}
	if(str[i]=='\0')return;
}
int main(){
    char s[100],tmp[100];int flag;double result=0.0;
	while(1){
		flag=1;
		printf("please input your expression：\n");
		gets_s(s);
		strcpy_s(tmp,100,s);
		Check(tmp,0,&flag);
		if(flag==0){
			printf("Error!please input again!\n");
			getchar();
		}
		if(flag){
			run(s,0,&result);
			printf("=%.3f\n",result);
			break;
		}
	}
	return 0;
}