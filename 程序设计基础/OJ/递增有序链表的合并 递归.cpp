#include<stdio.h>
#include<malloc.h>
struct node{
	int n;
	node*next;
};

node*creat(node*p){
	int n;
	printf("����������ڵ���Ϣ(��0��������):");
	scanf_s("%d",&n);
	if(n==0)p=NULL;
	else{
		p=(node*)malloc(sizeof(node));
		p->n=n;
		p->next=creat(p->next);
	}
	return p;
}
//��������Ƿ��������
int Check(node*head){
	node*p=head;
	if(head==NULL){
		printf("����Ϊ�գ�\n");
	}else{
		while(p->next!=NULL){
			if(p->n>p->next->n)return 0;
			p=p->next;
		}
	}
	return 1;
}
void CombinNode(node*p1,node*p2,node**p){
	node*pre;
	if(p1!=NULL&&p2!=NULL){
		if(p1->n<p2->n){
			*p=(node*)malloc(sizeof(node));
			(*p)->n=p1->n;
			CombinNode(p1->next,p2,&((*p)->next));
		}else if(p1->n<=p2->n){
			*p=(node*)malloc(sizeof(node));
			(*p)->n=p2->n;
			CombinNode(p1,p2->next,&((*p)->next));
		}
	};
	if(p1==NULL&&p2!=NULL){
		*p=(node*)malloc(sizeof(node));
		(*p)->n=p2->n;
		CombinNode(p1,p2->next,&((*p)->next));
	}
	if(p1!=NULL&&p2==NULL){
		*p=(node*)malloc(sizeof(node));
		(*p)->n=p1->n;
		CombinNode(p1->next,p2,&((*p)->next));
	}
	if(p1==NULL&&p2==NULL){
		*p=NULL;return ;
	};
}

void print(node*p1){
	if(p1!=NULL){
		printf("%d->",p1->n);
		print(p1->next);
	}else{
		printf("NULL\n");
		return;
	}
}
int main(){
	node*head1,*head2,*head;
	head1=head2=NULL;
	while(1){
		printf("����������1:\n");head1=creat(head1);
		printf("����������2:\n");head2=creat(head2);
		if(Check(head1)&&Check(head2))break;
		printf("���������������������ģ�\n");
	};
	printf("����1:\n");print(head1);
	printf("����2:\n");print(head2);
	CombinNode(head1,head2,&head);
	printf("�ϲ��������:\n");
	print(head);
	return 0;
}
