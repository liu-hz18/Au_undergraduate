#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct salary{
	char num[10];
	char name[20];
	int money;
	salary*next;
};
salary*insert(salary*head,salary*p0)//按升序插入新的节点
{
	salary*p1,*p2;
	p1=p2=head;
	if(head==NULL){head=p0;p0->next=NULL;}
	else{
		while(strcmp(p0->num,p1->num)>0&&p1->next!=NULL){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->num,p1->num)<=0){
			if(p1==head){
				head=p0;
				p0->next=p1;
			}
			else{
				p2->next=p0;
				p0->next=p1;
			}
		}
		else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	return head;
}
salary*combin(salary*list1,salary*list2)
{
	salary*list,*p1,*p2,*tmp;
	p1=list1;list=NULL;
	while(p1!=NULL){
		tmp=p1->next;//采用插入法来分别插入每个节点的内容是简便易行的
		list=insert(list,p1);
		p1=tmp;//应该注意在p1插入新链表之后，原先的指向关系被破坏，这时应该设置一个tmp指针来暂时存储之前的指向关系
	}
	p2=list2;
	while(p2!=NULL){
		tmp=p2->next;
		list=insert(list,p2);
		p2=tmp;
	}
	return list;
}
void print(salary*list)
{
	salary*p;
	p=list;
	printf("链表内容为：\n");
	while(p!=NULL){
		printf("%s,%s,%d\n",p->num,p->name,p->money);
		p=p->next;
	}
}
void rank(salary*list,salary*pointer[])
{
	salary*p;
	int min;
	p=list;
	for(int i=0;i<7;i++){
		pointer[i]=p;
		p=p->next;
	}
	//选择排序
	for(int i=0;i<7;i++){
		min=pointer[i]->money;
		for(int j=i;j<7;j++){
			if(pointer[j]->money<min)min=pointer[j]->money;
			if(min!=pointer[i]->money){
				salary*tmp=pointer[i];
				pointer[i]=pointer[j];
				pointer[j]=tmp;
			}
		}
	}
}
void print_p(salary*p[])
{
	printf("\n按工资排序的结果为:\n");
	for(int i=0;i<7;i++){
		printf("%s,%s,%d\n",p[i]->num,p[i]->name,p[i]->money);
	}
}
int main()
{
	//链表初始化
	salary a3={"003","name003",3500,NULL},a2={"005","name005",2500,&a3},a1={"002","name002",3000,&a2};
	salary b4={"007","name007",3600,NULL},b3={"001","name001",3000,&b4},b2={"004","name004",3700,&b3},b1={"006","name006",2800,&b2};
	salary*list1,*list2,*list,*p[7];
	list1=&a1;list2=&b1;
	list=combin(list1,list2);//应当注意的是，虽然两个链表是在主函数中定义的局部变量，但由于一开始传入的表头含有指针，每个节点也都有指针，这样层层指引下去就可以得到整个链表
	print(list);
	rank(list,p);
	print_p(p);
	return 0;
}
