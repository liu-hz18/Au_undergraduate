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
			for(j=i;(*s)[j]==' ';j++);//j-i-1是空格区间长度
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
		//不要在操作中使用连续判断的不等式，应该使用逻辑运算符 与或非 ！！
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
	printf("原始字符串:\n%s\n数字字符串:\n%s\n字母字符串:\n%s\n请输入字符串 或 按'@'结束输入\n",s,s2,s1);
	return;
}
int main(){
	char ch,s[100],str1[100],str2[100],*p=s,*ptr1,*ptr2;
	ptr1=str1,ptr2=str2;
	printf("请输入字符串 或 按'@'结束输入");
	while((ch=getchar())!='@'){
		//getchar可以吸收回车符！！不用再来一次getchar!!
		input(&p);
		split(p,&ptr1,&ptr2);
		print(p,ptr1,ptr2);
	}
	return 0;
}
