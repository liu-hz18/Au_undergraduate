#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define LEN 1000
//define 后面的变量后面不能加‘=’，也不能在语句末尾加‘;’
char*reverse(char*str,int len){
	char tmp;
	for(int i=0;i<len/2;i++){
		tmp=str[i];
		str[i]=str[len-i-1];
		str[len-i-1]=tmp;
	}
	str[len]='\0';
	return str;
}
void opreate(char**num1,char**num2,char**result)
{
	int i,flag=0;int minlen;
	*result=(char*)malloc(sizeof(char)*LEN);
	for(i=0;i<LEN-1;i++)(*result)[i]='0';(*result)[LEN-1]='\0';
	if(strlen(*num1)>strlen(*num2)){minlen=strlen(*num2);flag=1;
	}else{minlen=strlen(*num1);flag=2;}
	strcpy_s(*num1,strlen(*num1)+1,reverse(*num1,strlen(*num1)));
	strcpy_s(*num2,strlen(*num2)+1,reverse(*num2,strlen(*num2)));
	if(flag==1){
		for(i=minlen;(*num1)[i]!='\0';i++)(*num2)[i]='0';
		(*num2)[i]='\0';
	}
	else if(flag==2){
		for(i=minlen;(*num2)[i]!='\0';i++)(*num1)[i]='0';
		(*num1)[i]='\0';
	}
}
int compare(char*num1,char*num2)
{
	if(strlen(num1)>strlen(num2))return 1;
	else if(strlen(num1)<strlen(num2))return -1;
	else{
		for(int i=0;num1[i]!='\0';i++){
			if(num1[i]>num2[i])return 1;
			if(num1[i]<num2[i])return -1;
		}
	}
	return 0;
}
char*add(char*num1,char*num2)
{
	int i,flag=0;char *result;
	opreate(&num1,&num2,&result);
	for(i=0;num1[i]!='\0'&&num2[i]!='\0';i++){
		if(num1[i]-'0'+num2[i]-'0'+result[i]-'0'>=10)result[i+1]+=1;
		result[i]=((num1[i]-'0'+num2[i]-'0'+result[i]-'0')%10)+'0';
	}
	if(result[i]!='0')result[i+1]='\0';else result[i]='\0';
	strcpy_s(result,strlen(result)+1,reverse(result,strlen(result)));
	strcpy_s(num1,strlen(num1)+1,reverse(num1,strlen(num1)));
	strcpy_s(num2,strlen(num2)+1,reverse(num2,strlen(num2)));
	return result;
}
char*subtraction(char*num1,char*num2)
{
	char*result,tmp[LEN];int i,flag=compare(num1,num2);
	if(flag==-1){strcpy_s(tmp,LEN,num1);strcpy_s(num1,LEN,num2);strcpy_s(num2,LEN,tmp);}
	else if(flag==0)return "0";
	opreate(&num1,&num2,&result);
	for(i=0;num1[i]!='\0'&&num2[i]!='\0';i++){
		if((num1[i]-'0')-(num2[i]-'0')<0){
			num1[i+1]-=1;
			result[i]=((num1[i]-'0')+10-(num2[i]-'0'))+'0';
		}
		else result[i]=((num1[i]-'0')-(num2[i]-'0'))+'0';
	}
	if(result[i-1]!='0'){
		if(flag==1)result[i]='\0';
		else {result[i]='-';result[i+1]='\0';}
	}else {
		if(flag==1)result[i-1]='\0';
		else {result[i-1]='-';result[i]='\0';}
	}
	strcpy_s(result,strlen(result)+1,reverse(result,strlen(result)));
	strcpy_s(num1,strlen(num1)+1,reverse(num1,strlen(num1)));
	strcpy_s(num2,strlen(num2)+1,reverse(num2,strlen(num2)));
	if(flag==-1){strcpy_s(tmp,LEN,num1);strcpy_s(num1,LEN,num2);strcpy_s(num2,LEN,tmp);}
	return result;
}
char*multiply(char*num1,char*num2)
{
	int i,j,flag=0,count;char *p,**result,tmp;
	opreate(&num1,&num2,&p);
	result=(char**)malloc((strlen(num2)+1)*sizeof(char*));
	for(i=0;i<(int)strlen(num2)+1;i++){
		*(result+i)=(char*)malloc(LEN*sizeof(char));
		for(j=0;j<LEN-1;j++)result[i][j]='0';result[i][j]='\0';
	}
	for(j=0;num2[j]!='\0';j++){
		for(i=0;num1[i]!='\0';i++){
			if((num1[i]-'0')*(num2[j]-'0')+result[j][i]-'0'>=10)result[j][i+1]+=((num1[i]-'0')*(num2[j]-'0')+result[j][i]-'0')/10;
			result[j][i]=((num1[i]-'0')*(num2[j]-'0')+result[j][i]-'0')%10+'0';
		}
		if(result[j][i]!='0'){result[j][i+1]='\0';count=i+1;}else {result[j][i]='\0';count=i;}
		strcpy_s(result[j],strlen(result[j])+1,reverse(result[j],strlen(result[j])));
		for(i=count;i<count+j;i++)result[j][i]='0';result[j][i]='\0';
		strcpy_s(p,LEN,add(p,result[j]));
	}
	for(flag=0;p[flag]=='0';flag++);
	for(i=flag;p[i]!='\0';i++){tmp=p[i-flag];p[i-flag]=p[i];p[i]=tmp;}
	p[i-flag]='\0';
	strcpy_s(num1,strlen(num1)+1,reverse(num1,strlen(num1)));
	strcpy_s(num2,strlen(num2)+1,reverse(num2,strlen(num2)));
	return p;
}
int main()
{
	char num1[LEN],num2[LEN];
	printf("    a = ");gets_s(num1);
	printf("    b = ");gets_s(num2);
	printf("a + b = %s\n",add(num1,num2));
	printf("a - b = %s\n",subtraction(num1,num2));
	printf("a * b = %s\n",multiply(num1,num2));
	return 0;
}
