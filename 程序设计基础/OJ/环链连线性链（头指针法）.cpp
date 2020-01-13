#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct node{
	char serial_num[20];
	node*next;
};
void PrintList(node*head,int n)//�����������
{
	node*p1=head;
	printf("��ǰ��������:\n");
	switch(n){//��1��������������2����ѭ������
		case 1:
			while(p1!=NULL){
				printf("%s -> ",p1->serial_num);
				p1=p1->next;
			}
			break;
		case 2:
			printf("%s -> ",p1->serial_num);
			while(p1->next!=head){
				p1=p1->next;
				printf("%s -> ",p1->serial_num);				
			}
			break;
	}
	putchar(10);
}
node*LineInsert(node*head,node*p0)//�����������
{
	node*p1,*p2;
	p1=p2=head;
	if(head==NULL){head=p0;p0->next=NULL;}
	else{
		while(strcmp(p0->serial_num,p1->serial_num)>0&&p1->next!=NULL){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->serial_num,p1->serial_num)<=0){
			if(p1==head){
				head=p0;
				p0->next=p1;
			}else{
				p2->next=p0;
				p0->next=p1;
			}
		}else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	return head;
}
node*CircleInsert(node*head,node*p0)//�����������
{
	node*p1,*p2,*p3;
	p1=p2=head;
	if(head==NULL){head=p0;p0->next=head;}
	else{
		while(p1->next!=head&&head!=NULL){p1=p1->next;}
		p3=p1;p1=head;
		while(strcmp(p0->serial_num,p1->serial_num)>0&&p1->next!=head){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->serial_num,p1->serial_num)<=0){
			if(p1==head){
				head=p0;
				p0->next=p1;
				p3->next=head;
			}else{
				p2->next=p0;
				p0->next=p1;
			}
		}else{
			p1->next=p0;
			p0->next=head;
		}
	}
	return head;
}
void create(node**head1,node**head2)
{
	node*p1,*p2;
	int n1,n2,i;
	p1=*head1;p2=*head2;
	printf("please input number of elements of aList:");
	scanf_s("%d",&n1);
	printf("please input the elements of aList:\n");
	for(i=0;i<n1;i++){
		p1=(node*)malloc(sizeof(node));
		scanf_s("%s",p1->serial_num,20);
		*head1=CircleInsert(*head1,p1);
		PrintList(*head1,2);
		fflush(stdin);
	}
	printf("\nplease input number of elements of bList:");
	scanf_s("%d",&n2);
	printf("please input the elements of sList:\n");
	for(i=0;i<n2;i++){
		p2=(node*)malloc(sizeof(node));
		scanf_s("%s",p2->serial_num,20);
		*head2=LineInsert(*head2,p2);
		PrintList(*head2,1);
		fflush(stdin);
	}
}
node*combin(node*head1,node*head2)
{
	node*p1;
	p1=head1;
	while(p1->next!=head1){
		p1=p1->next;
	}
	p1->next=head2;
	return head1;
}
void SaveList(node*head,int n,char**fname1)//��������������뵽Ӳ���ļ�
{
	FILE*fp1;
	node*p1;
	p1=head;
	printf("\n�������½�.txt�ļ�����");
	scanf_s("%s",*fname1,20);
	if((fp1=fopen(*fname1,"w+"))==NULL){
		printf("cannot open file %s\n",*fname1);
		return;
	}
	switch(n){
		case 2:
			do{
				if((fwrite(p1,20*sizeof(char),1,fp1)!=1))//�����������ݣ�������ָ��
					printf("file1 write error!\n");
				p1=p1->next;
			}while(p1!=head);
			break;
		case 1:
			do{
				if((fwrite(p1,20*sizeof(char),1,fp1))!=1)
					printf("file2 write error!\n");
				p1=p1->next;
			}while(p1!=NULL);
			break;
	}
	fclose(fp1);
}
void LoadList(char**fname_p)//��Ӳ���ļ���������
{
	int n,i;node tmp[20];
	char fname[20];FILE*fp;
	printf("\n������Ҫ�򿪵�.txt�ļ���:\n");
	scanf_s("%s",fname,20);
	if(strcmp(fname,*fname_p)==0||strcmp(fname,*(fname_p+2))==0)n=2;
	else if(strcmp(fname,*(fname_p+1))==0)n=1;
	else {printf("error!\n");return ;}
	if((fp=fopen(fname,"r"))==NULL){
		printf("cannot open file!\n");
		return ;
	}
	//ָ����д���ļ�֮���ڳ������֮��Ӳ���ļ���Ȼ������ָ�����Ϣ���������ļ�����֮���ڴ��е�ָ��ָ������ݻ���ʧ
	//������´򿪳���֮�������ڴ���Ϣ���¿��ٵģ���ʱ�ٶ���Ӳ�����ָ�룬�ͻ�ʹ��ָ��ָ������û��������Ϣ
	//��ˣ������������ļ�������ָ����ߴ��ļ��ж���ָ����Ϣ
	printf("��ǰ��������:\n");
	switch(n){
	case 1:
		i=0;
		rewind(fp);
		while(!feof(fp)){
			fread(&tmp[i].serial_num,20*sizeof(char),1,fp);//���������ȡ�˽ṹ���Ա�е����飬��ζ�ȡָ����Ϣ������һ�������أ�
			if(feof(fp))break;
			printf("%s -> ",tmp[i].serial_num);
			i++;
		};
		break;
	case 2:
		i=0;
		rewind(fp);
		while(!feof(fp)){
			fread(&tmp[i].serial_num,20*sizeof(char),1,fp);
			if(feof(fp))break;
			printf("%s -> ",tmp[i].serial_num);
			i++;
		};
		break;
	}
	fclose(fp);
	return;
}
int main()
{
	node*head1,*head2;
	char fname[3][20];
	char*fname_p[3]={fname[0],fname[1],fname[2]};
	head1=NULL;head2=NULL;
	create(&head1,&head2);
	//create��������֮���β���ʧ�ˣ����Ե��Ӻ������ܶ�ͷ�������޸ĵ�ʱ��Ӧ�ô�ͷ���ĵ�ַ
	SaveList(head1,2,&fname_p[0]);
	SaveList(head2,1,&fname_p[1]);
	LoadList(fname_p);
	LoadList(fname_p);//�����ڴ沢�������Ļ
	head1=combin(head1,head2);
	SaveList(head1,1,&fname_p[2]);
	printf("�ϲ����������:\n");
	PrintList(head1,1);
	return 0;
}
