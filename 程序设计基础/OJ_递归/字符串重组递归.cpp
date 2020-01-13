#include<stdio.h>
#include<string.h>

void input(char**s,int*n){
	printf("pleass input your string:\n");
	gets_s(*s,100);
	printf("请输入重组位置:");
	scanf_s("%d",n);
	return ;
}

void ReArrange(char*s,char**newstr,int n,int i,int loc,char ch,int*flagLeft,int*flagRight){
	if(ch=='L'){
		if(n-loc>=0){
			(*newstr)[i]=s[n-loc];
		}else *flagLeft=0;
		if(i==strlen(s)+1){
			(*newstr)[i]='\0';return;
		}
		if(*flagLeft!=0)ReArrange(s,newstr,n,i+1,loc+1,'R',flagLeft,flagRight);
		else ReArrange(s,newstr,n,i,loc+1,'R',flagLeft,flagRight);
	}else if(ch=='R'){
		if(s[n+loc]!='\0'){
			(*newstr)[i]=s[n+loc];
		}else *flagRight=0;
		if(i==strlen(s)){
			(*newstr)[i]='\0';return;
		}
		if(*flagRight!=0)ReArrange(s,newstr,n,i+1,loc,'L',flagLeft,flagRight);
		else ReArrange(s,newstr,n,i,loc,'L',flagLeft,flagRight);
	}
	return;
}

void print(char*s){
	printf("重组后的字符串：%s\n",s);
	return;
}

int main(){
	char s[100],newstr[100],*p=s,*p_str=newstr;
	int flagLeft=1,flagRight=1,n;
	input(&p,&n);
	ReArrange(p,&p_str,n-1,0,0,'L',&flagLeft,&flagRight);
	print(p_str);
	return 0;
}
