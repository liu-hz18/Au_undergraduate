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
	for(i=0;i<len;i++){//��λ���ϱ��
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
		printf("Error��\n");
		for(i=0;i<k;i++){
			if(count[i]==1){
				printf("����%dλ�ô�������δƥ�䣡\n",i+1);
			}
			if(count[i]==-1){
				printf("����%dλ�ô��һ�����δƥ�䣡\n",i+1);
			}
		}
	}
	else printf("���Ǹ�����ĳ���Գ��\n");
	return 0;
}
//���������ڼ���������Ϊƥ�䣬��Ҫ��������һ������loca[]��¼ÿ�������ŵ�λ�ã�Ȼ����������λ��
