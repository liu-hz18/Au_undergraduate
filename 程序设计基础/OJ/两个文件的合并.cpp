#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void swap(char*a,char*b)
{
	char tmp[10];
	strcpy_s(tmp,10,a);
	strcpy_s(a,10,b);
	strcpy_s(b,10,tmp);
}
int main()
{
	FILE*fp1,*fp2,*fp3;
	char s[20][10],ch;
	int i=0,j=0,count,len;
	if((fp1=fopen("D:\\大一上\\程设\\作业\\第八次\\8-1-dict1.txt","r"))==NULL){
		printf("Cannot open file '8-1-dict1.txt'\n");
		exit(0);
	}
	if((fp2=fopen("D:\\大一上\\程设\\作业\\第八次\\8-1-dict2.txt","r"))==NULL){
		printf("Cannot open file '8-1-dict1.txt'\n");
		exit(0);
	}
	if((fp3=fopen("D:\\大一上\\程设\\作业\\第八次\\8-1-dict3.txt","w+"))==NULL){
		printf("Cannot open file '8-1-dict3.txt'\n");
		exit(0);
	}
	//将文件中的信息存在数组s中
	while((ch=fgetc(fp1))!=EOF){
		s[i][j++]=ch;
		if(ch=='\n'){s[i][j]='\0';i++;j=0;}
	}
	s[i][j]='\0';i++;j=0;
	while((ch=fgetc(fp2))!=EOF){
		s[i][j++]=ch;
		if(ch=='\n'){s[i][j]='\0';i++;j=0;}
	}
	s[i][j]='\0';count=i;
	//进行排序
	for(i=count;i>=0;i--){
		for(j=0;j<i;j++){
			if(strcmp(s[j],s[j+1])>0)swap(s[j],s[j+1]);
		}
	}
	//进行删除
	for(i=0;i<count;i++){
		if(strcmp(s[i],s[i+1])==0){s[i+1][0]='\0';i++;}
	}
	for(i=0;i<count;i++){
		len=strlen(s[i]);
		if(s[i][len-1]!='\n'&&strcmp(s[i],"\0")!=0){s[i][len]='\n';s[i][len+1]='\0';}
	}
	//向新文件输出字符串内容
	for(i=0;i<=count;i++){
		if(strcmp(s[i],"\0")!=0){
			fwrite(s[i],strlen(s[i]),1,fp3);
		}
	}
	fclose(fp1);fclose(fp2);fclose(fp3);
	fp1=fp2=fp3=NULL;
	return 0;
}
