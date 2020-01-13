#include<stdio.h>
#include<string.h>
int main()
{
	char s[1000];
	int i,count[100]={0},loca[100],k,j,flag=1;
	printf("please input your code:\n");
	for(i=0;(s[i]=getchar())!=4;i++);
	s[i]='\0';
    int len=strlen(s);
	for(i=0;i<len;i++){//在位置上标记
		if(s[i]=='{')count[i]=1;
		if(s[i]=='}')count[i]=-1;
		else count[i]=0;
	}
	k=i;
	for(i=0;i<k;i++){
		if(count[i]==-1){
			for(j=i-1;j>=0;j--){
				if(count[j]==1){
					count[i]=0;
					count[j]=0;
					break;
				}
			}
		}
	}
	for(i=0;i<k;i++){
		if(count[i]!=0){
			flag=0;
			break;
		}
	}
	if(flag==0){
		printf("Error！\n");
		for(i=0;i<k;i++){
			if(count[i]==1){
				printf("代码%d位置处左花括号未匹配！\n",i+1);
			}
			if(count[i]==-1){
				printf("代码%d位置处右花括号未匹配！\n",i+1);
			}
		}
	}
	else printf("你是个优秀的程序猿！\n");
	return 0;
}
//如果想输出第几个花括号为匹配，需要重新设置一个数组loca[]记录每个花括号的位置，然后输出错误的位置
