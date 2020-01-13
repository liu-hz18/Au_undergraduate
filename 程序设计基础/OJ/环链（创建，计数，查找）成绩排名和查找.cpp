 //循环链表
#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct student{
	char num[20];
	char name[10];
	student*next;
};
student*insert(student*head,student*stu)//递增插入新节点，创建循环链表
{
	student*p0,*p1,*p2,*last;
	p0=stu;p1=head;
	while(head!=NULL&&p1->next!=head){
		p2=p1;p1=p1->next;
	}
	last=p1;//找到表尾
	p1=head;
	if(head==NULL){head=p0;p0->next=head;}
	else{
		while(strcmp(p0->num,p1->num)>0&&(p1->next!=head)){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->num,p1->num)<=0){
			if(head==p1){//创建新表头后和原表尾连接
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
		list(head);//每次插入后输出当前链表
		count++;
	}while(count<n);
	return head;
}
int f(student*head)//节点计数
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
student*fv(student*head)//环形链表倒序
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
void list(student*head)//输出链表数据
{
	student*p1;
	int count=1;
	p1=head;
	printf("当前链表:\n head -> ");
	do{
		if(count%4==0)putchar(10);
		printf("number:%s  name：%s -> ",p1->num,p1->name);
		count++;
		p1=p1->next;
	}while(p1!=head);
	printf("head\n");
}
student*search(student*head,char*num)//查找信息
{
	student*p1;
	p1=head;
	do{
		if(strcmp(num,p1->num)==0)return p1;
		p1=p1->next;
	}while(p1!=head);
	return NULL;
}
void myfree(student*head)//释放内存
{
	student*p,*tmp;
	p=head->next;
	head->next=NULL;//先解环后释放
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
