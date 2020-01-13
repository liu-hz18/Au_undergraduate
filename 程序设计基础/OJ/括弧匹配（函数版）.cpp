#include<stdio.h>
#include<string.h>
void input(char**p,int*k,int**count){
	int i;
	printf("please input your code:\n");
	for(i=0;((*p)[i]=getchar())!=4;i++);
	(*p)[i]='\0';
	getchar();
    int len=strlen(*p);
	for(i=0;i<len;i++)(*count)[i]=0;
	for(i=0;i<len;i++){//在位置上标记
		if((*p)[i]=='(')(*count)[i]=1;
		else if((*p)[i]==')')(*count)[i]=-1;
		else (*count)[i]=0;
	}
	*k=i;
}
void check(int count[],int*flag,int k){
	int i,j;*flag=1;
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
			*flag=0;
			break;
		}
	}
}
void print(int count[],int k,int flag){
	int i;
	if(flag==0){
		printf("Error！\n");
		for(i=0;i<k;i++){
			if(count[i]==1){
				printf("代码%d位置处左圆括号未匹配！\n",i+1);
				break;
			}
		}
		for(i=k-1;i>=0;i--){
			if(count[i]==-1){
				printf("代码%d位置处右圆括号未匹配！\n",i+1);
				break;
			}
		}
	}
	else printf("你是个优秀的程序猿！\n");
}
int main()
{
	char s[1000],*p=s,ch;int count[100]={0},k,flag=1,*ptr=count;
	while((ch=getchar())!='@'){
		flag=1;
		input(&p,&k,&ptr);
		check(count,&flag,k);
		print(count,k,flag);
		printf("是否继续？按@结束程序\n");
	}
	return 0;
}
//如果想输出第几个花括号为匹配，需要重新设置一个数组loca[]记录每个花括号的位置，然后输出错误的位置
