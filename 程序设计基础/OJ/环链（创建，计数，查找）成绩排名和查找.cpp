 //ѭ������
#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct student{
	char num[20];
	char name[10];
	student*next;
};
student*insert(student*head,student*stu)//���������½ڵ㣬����ѭ������
{
	student*p0,*p1,*p2,*last;
	p0=stu;p1=head;
	while(head!=NULL&&p1->next!=head){
		p2=p1;p1=p1->next;
	}
	last=p1;//�ҵ���β
	p1=head;
	if(head==NULL){head=p0;p0->next=head;}
	else{
		while(strcmp(p0->num,p1->num)>0&&(p1->next!=head)){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->num,p1->num)<=0){
			if(head==p1){//�����±�ͷ���ԭ��β����
				head=p0;
				last->next=head;
			}
			else p2->next=p0;
			p0->next=p1;
		}
		else{
			p1->next=p0;
			p0->next=head;
		}
	}
	return head;
}
student*creat()
{
	void list(student*head);
	student*head,*p1;int count=0,n;
	printf("please input the number of students:");
	scanf_s("%d",&n);
	printf("please input the information of students:\n");
	head=NULL;
	do{
		p1=(student*)malloc(sizeof(student));
		scanf_s("%s%s",p1->num,20,p1->name,10);
		head=insert(head,p1);
		list(head);//ÿ�β���������ǰ����
		count++;
	}while(count<n);
	return head;
}
int f(student*head)//�ڵ����
{
	student*p1;int count=0;
	p1=head;
	while(p1->next!=head){
		p1=p1->next;
		count++;
	}
	count++;
	return count;
}
student*fv(student*head)//����������
{
	student*p1,*p2,*p3;
	p1=head;
	p2=p3=head->next;
	while(p2!=head){
		p3=p2->next;
		p2->next=p1;
		p1=p2;
		p2=p3;
	}
	p2->next=p1;
	return p1;
}
void list(student*head)//�����������
{
	student*p1;
	int count=1;
	p1=head;
	printf("��ǰ����:\n head -> ");
	do{
		if(count%4==0)putchar(10);
		printf("number:%s  name��%s -> ",p1->num,p1->name);
		count++;
		p1=p1->next;
	}while(p1!=head);
	printf("head\n");
}
student*search(student*head,char*num)//������Ϣ
{
	student*p1;
	p1=head;
	do{
		if(strcmp(num,p1->num)==0)return p1;
		p1=p1->next;
	}while(p1!=head);
	return NULL;
}
void myfree(student*head)//�ͷ��ڴ�
{
	student*p,*tmp;
	p=head->next;
	head->next=NULL;//�Ƚ⻷���ͷ�
	while(p!=NULL){
		tmp=p;
		p=p->next;
		free(tmp);
	}
}
int main()
{
	student*head,*result;
	char num[20];
	head=creat();
	if(head==NULL)printf("������\n");
	else{
		printf("\n�ڵ������%d\n",f(head));
		head=fv(head);
		printf("\n����������\n");
		list(head);
		printf("\nplease input the num you wanna search:");
		scanf_s("%s",num,20);
		if((result=search(head,num))!=NULL)
			printf("ѧ��:%s,����:%s\n",result->num,result->name);
		else printf("��ѧ�Ų����ڣ�\n");
	}
	myfree(head);
	return 0;
}
