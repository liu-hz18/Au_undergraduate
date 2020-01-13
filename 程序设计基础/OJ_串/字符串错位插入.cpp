//字符串的错位排列
#include<stdio.h>
#include<malloc.h>
char*interlaced(char*str1,char*str2){
	char*str3;int i,k,flag,j;
	str3=(char*)malloc(50*sizeof(char));
	//char*函数在结束之后定义的栈中数组会消失，所以要在堆中开辟数组！！！之后才能回传
	for(i=0,k=0;str1[i]!='\0'&&str2[i]!='\0';i++){
		str3[k++]=str1[i];
		str3[k++]=str2[i];
	}
	if(str1[i]=='\0')flag=1;
	else if(str2[i]=='\0')flag=2;
	if(flag==1){
		for(j=i;str2[j]!='\0';j++){
			str3[k++]=str2[j];
		}
	}else{
		for(j=i;str1[j]!='\0';j++){
			str3[k++]=str1[j];
		}
	}
	str3[k]='\0';
	return str3;
}
int main()
{
	char str1[20],str2[20],ch,*str3;
	while(1){
		printf("按任意键继续，按@键结束程序\n");
		if((ch=getchar())=='@')break;
		getchar();
		printf("please input str1:\n");gets_s(str1);
		printf("please input str2:\n");gets_s(str2);
		printf("重组后的新字符串：%s\n",str3=interlaced(str1,str2));		
	}
	free(str3);
	return 0;
}
