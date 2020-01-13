#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct student{
	char num[20];
	char name[10];
	student*next;
};
student*insert(student*head,student*stu)//递增插入新节点
{
	student*p0,*p1,*p2;
	p0=stu;p1=head;
	if(head==NULL){head=p0;p0->next=NULL;}
	else{
		while(strcmp(p0->num,p1->num)>0&&(p1->next!=NULL)){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->num,p1->num)<=0){
			if(head==p1)head=p0;
			else p2->next=p0;
			p0->next=p1;
		}
		else{
			p1->next=p0;
			p0->next=NULL;
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
		list(head);//每次插入后输出当前链表
		count++;
	}while(count<n);
	return head;
}
int f(student*head)//节点计数
{
	student*p1;int count=0;
	p1=head;
	while(p1->next!=NULL){
		p1=p1->next;
		count++;
	}
	count++;
	return count;
}
student*fv(student*head)//链表倒序
{
	student*p1,*p2,*p3;
	p1=head;
	p2=p3=head->next;
	while(p2!=NULL){
		p3=p2->next;
		p2->next=p1;
		p1=p2;
		p2=p3;
	}
	head->next=NULL;
	return p1;
}
void list(student*head)//输出链表数据
{
	student*p1;
	int count=1;
	p1=head;
	printf("当前链表:\nhead -> ");
	while(p1!=NULL){
		if(count%4==0)putchar(10);
		printf("number:%s  name：%s -> ",p1->num,p1->name);
		count++;
		p1=p1->next;
	}
	printf("NULL\n");
}
student*search(student*head,char*num)//查找信息
{
	student*p1;
	p1=head;
	while(p1!=NULL){
		if(strcmp(num,p1->num)==0)return p1;
		p1=p1->next;
	}
	return NULL;
}
void myfree(student*head)//释放内存，单向链表释放内存需要遍历释放
{
	student*p;
	while(head!=NULL){
		p=head;
		head=head->next;
		free(p);
	}
}
int main()
{
	student*head,*result;
	char num[20];
	head=creat();
	if(head==NULL)printf("空链表！\n");
	else{
		printf("\n节点个数：%d\n",f(head));
		head=fv(head);
		printf("\n倒序后的链表：\n");
		list(head);
		printf("\nplease input the num you wanna search:");
		scanf_s("%s",num,20);
		if((result=search(head,num))!=NULL)
			printf("学号:%s,姓名:%s\n",result->num,result->name);
		else printf("该学号不存在！\n");
	}
	myfree(head);
	return 0;
}
