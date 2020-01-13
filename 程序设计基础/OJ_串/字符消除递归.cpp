//递归编程
#include<stdio.h>
#include<string.h>
#include<malloc.h>
int mystrcmp(char*str1,char*str2){
	int i,flag=0;
	for(i=0;str1[i]!='\0'&&str2[i]!='\0';i++){
		if(str1[i]>str2[i]){flag=1;break;}
		else if(str1[i]<str2[i]){flag=-1;break;}
	}
	if(str1[i]=='\0'&&str2[i]!='\0')flag=1;
	else if(str1[i]!='\0'&&str2[i]=='\0')flag=-1;
	return flag;
}
char*input(){
	char*str;
	str=(char*)malloc(50*sizeof(char));
	printf("please inout the str:\n");
	gets_s(str,50);
	return str;
}
void eliminate(char*str){
	int len=strlen(str),count=0,i,j,k,flag=0;
	for(i=0;i<len;i++){
		count=0;
		for(j=i;j<len;j++){
			if(str[j]==str[i])count++;
			else {count=0;break;}
			if(count==3){
				flag=1;
				for(k=i;k<=len-3;k++){
					str[k]=str[k+3];
				}
				break;
			}
		}
	}
	if(flag==1)eliminate(str);
}

int main()
{
	char*str;
	while(1){
		printf("按任意键继续，按quit结束程序\n");
		str=input();
		if(mystrcmp(str,"quit")==0)break;
		eliminate(str);
		printf("处理后的字符串:\n%s\n",str);
	}
	return 0;
}
