//��Ʊ����ͳ��
#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct node{
	char time[11];
	char name[9];
	int num;
	float price_in;
	float price_out;
	float rate;
	float interest_rate;
};
void main()
{
	node*info;int i=0,count,j=0,num=0,k,flag=0;
	float sum[10]={0.0};char ch,name[10][10];
	info=(node*)malloc(1000*sizeof(node));
	FILE*fp1,*fp2;
	if((fp1=fopen("D:\\��һ��\\����\\��ҵ\\�ڰ˴�\\8-3-stock.txt","r"))==NULL){
		printf("cannot open file!\n");
		return;
	}
	ch=fgetc(fp1);
	while(!feof(fp1)){
		j=0;
		while(ch!=' '){
			info[i].time[j++]=ch;
			ch=fgetc(fp1);
		}
		info[i].time[j]='\0';
		ch=fgetc(fp1);j=0;
		while(ch!=' '){
			info[i].name[j++]=ch;
			ch=fgetc(fp1);
		}
		info[i].name[8]='\0';
		fscanf(fp1,"%d",&info[i].num);
		ch=fgetc(fp1);
		fscanf(fp1,"%f",&info[i].price_in);
		//fread��ȡ���ݿ�ĳ��ȣ�ʵ������txt�ļ��з�ӳΪһ���ֽڵĳ��ȣ�
		//��ʱ�������ȡsizeof(float)�ĳ��ȣ�ֻ���ȡ4���ֽڣ�������һ����������
		//��ȡ�����͸����������Բ���fscanf����
		//��Ȼ�ᷢ�����ݵĴ�λ
		ch=fgetc(fp1);
		fscanf(fp1,"%f",&info[i].price_out);
		ch=fgetc(fp1);
		ch=fgetc(fp1);
		if(ch==EOF)break;
		i++;
	}
	count=i;
	strcpy_s(name[++num],10,info[0].name);
	for(i=0;i<=count;i++){
		info[i].interest_rate=(info[i].price_out-info[i].price_in)/info[i].price_in;
		for(k=1;k<=num;k++){
			if(strcmp(info[i].name,name[k])==0){
				sum[k]+=(info[i].num)*(info[i].price_in);
				flag=1;
				break;
			}
		}
		if(flag==0){
			strcpy_s(name[++num],12,info[i].name);
			sum[num]+=(info[i].num)*(info[i].price_in);
		}
		flag=0;
	}
	for(i=0;i<=count;i++){
		for(k=1;k<=num;k++){
			if(strcmp(info[i].name,name[k])==0){
				info[i].rate=(info[i].num)*(info[i].price_in)/sum[k];
				break;
			}
		}
	}
	if((fp2=fopen("D:\\��һ��\\����\\��ҵ\\�ڰ˴�\\8-3-stat.txt","w+"))==NULL){
		printf("cannot open file!\n");
		return ;
	}
	i=0;
	while(i<=count){
		fputs(info[i].time,fp2);
		fputc(' ',fp2);
		fputs(info[i].name,fp2);
		fputc(' ',fp2);
		fprintf(fp2,"%f%%  ",100*(info[i].rate));
		fprintf(fp2,"%f%%\n",100*(info[i].interest_rate));
		i++;
	}
	fclose(fp1);
	fclose(fp2);
	free(info);
}
