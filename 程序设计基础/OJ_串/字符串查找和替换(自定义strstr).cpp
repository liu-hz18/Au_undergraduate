#include<stdio.h>
#include<string.h>

void input(char**str,char**stra,char**strb){
	printf("please input str:\n");
	gets_s(*str,100);
	printf("please input stra:\n");
	gets_s(*stra,30);
	printf("please input strb:\n");
	gets_s(*strb,30);
}	
int mystrstr(char*str,char*stra){
	int loc=-1,i,j,k=0;
	for(i=0;str[i]!='\0';i++){
		if(str[i]==stra[0]){
			k=0;loc=i;
			for(j=i;stra[k]!='\0';j++){
				if(str[j]!=stra[k++])loc=-1;
			}
			if(stra[k]=='\0')break;
		}
	}
	return loc;
}
char*replace(char*str,char*stra,char*strb){
	int i,k,loc,lenb=strlen(strb),lena=strlen(stra),len=strlen(str);
	while((loc=mystrstr(str,stra))!=-1){
		k=0;
		for(i=len;i>=loc+lena-1;i--){
			str[i+lenb-lena]=str[i];
		}
		for(i=loc;i<loc+lenb;i++){
			str[i]=strb[k++];
		}
	}
	str[len+lenb-lena+1]='\0';
	return str;
}
int main(){
	char str[100],stra[30],strb[30],*p=str,*pa=stra,*pb=strb,ch;
	printf("程序是否继续？按@结束程序！");
	while((ch=getchar())!='@'){
		input(&p,&pa,&pb);
		printf("替换后的字符串:%s\n",replace(str,stra,strb));
		printf("程序是否继续？按@结束程序！");
	}
	return 0;
}
