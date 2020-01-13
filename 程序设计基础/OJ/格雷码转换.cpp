//格雷码转换
#include<stdio.h>
void input(char*str,char ch){
	if(ch=='g'){
		printf("please input the gary code:\n");
	}else if(ch=='b'){
		printf("please input the binary code:\n");
	}
	gets_s(str,10);//gets会吸收回车和换行，不用getchar!!!
}
void tran(char*str,char ch,char*newstr){
	int i;
	if(ch=='b'||ch=='B'){
		for(i=3;i>=0;i--){
			if(i!=0){
				if(str[i]!=str[i-1])newstr[i]='1';
				else newstr[i]='0';
			}else{
				if(str[i]!='0')newstr[i]='1';
				else newstr[i]='0';
			}
		}
		newstr[4]='\0';
	}else if(ch=='g'||ch=='G'){
		for(i=0;i<4;i++){
			if(i!=0){
				if(i!=0&&str[i]!=newstr[i-1])newstr[i]='1';
				else newstr[i]='0';
			}
			else{
				if(str[i]!='0')newstr[i]='1';
				else newstr[i]='0';
			}
		}
		newstr[4]='\0';
	}
}
void output(char*str,char ch){
	if(ch=='G'||ch=='g'){
		printf("its binary code is:\n");
		puts(str);
	}else if(ch=='b'||ch=='B'){
		printf("its gray code is:\n");
		puts(str);
	}
}
int main()
{
	char str[10],newstr[10],ch;
	while(1){
		printf("input gray code or binary code,press 'q' to quit:");
		ch=getchar();getchar();
		if(ch!='q'){
			input(str,ch);
			tran(str,ch,newstr);
			output(newstr,ch);
		}
		else break;
	}
	return 0;
}