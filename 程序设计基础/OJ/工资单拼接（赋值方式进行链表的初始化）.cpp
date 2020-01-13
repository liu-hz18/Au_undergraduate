#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct salary{
	char num[10];
	char name[20];
	int money;
	salary*next;
};
salary*insert(salary*head,salary*p0)//����������µĽڵ�
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
		tmp=p1->next;//���ò��뷨���ֱ����ÿ���ڵ�������Ǽ�����е�
		list=insert(list,p1);
		p1=tmp;//Ӧ��ע����p1����������֮��ԭ�ȵ�ָ���ϵ���ƻ�����ʱӦ������һ��tmpָ������ʱ�洢֮ǰ��ָ���ϵ
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
	printf("��������Ϊ��\n");
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
	//ѡ������
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
	printf("\n����������Ľ��Ϊ:\n");
	for(int i=0;i<7;i++){
		printf("%s,%s,%d\n",p[i]->num,p[i]->name,p[i]->money);
	}
}
int main()
{
	//�����ʼ��
	salary a3={"003","name003",3500,NULL},a2={"005","name005",2500,&a3},a1={"002","name002",3000,&a2};
	salary b4={"007","name007",3600,NULL},b3={"001","name001",3000,&b4},b2={"004","name004",3700,&b3},b1={"006","name006",2800,&b2};
	salary*list1,*list2,*list,*p[7];
	list1=&a1;list2=&b1;
	list=combin(list1,list2);//Ӧ��ע����ǣ���Ȼ�������������������ж���ľֲ�������������һ��ʼ����ı�ͷ����ָ�룬ÿ���ڵ�Ҳ����ָ�룬�������ָ����ȥ�Ϳ��Եõ���������
	print(list);
	rank(list,p);
	print_p(p);
	return 0;
}
