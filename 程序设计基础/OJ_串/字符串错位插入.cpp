//�ַ����Ĵ�λ����
#include<stdio.h>
#include<malloc.h>
char*interlaced(char*str1,char*str2){
	char*str3;int i,k,flag,j;
	str3=(char*)malloc(50*sizeof(char));
	//char*�����ڽ���֮�����ջ���������ʧ������Ҫ�ڶ��п������飡����֮����ܻش�
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
		printf("���������������@����������\n");
		if((ch=getchar())=='@')break;
		getchar();
		printf("please input str1:\n");gets_s(str1);
		printf("please input str2:\n");gets_s(str2);
		printf("���������ַ�����%s\n",str3=interlaced(str1,str2));		
	}
	free(str3);
	return 0;
}
