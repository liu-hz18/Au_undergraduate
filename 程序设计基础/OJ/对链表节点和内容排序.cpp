#include<stdio.h>
#include<malloc.h>
struct node{
	int n;
	node*next;
};

node*creat(node*p){
	int n;
	printf("please input a num(press 0 to end)");
	scanf_s("%d",&n);
	if(n==0){
		p=NULL;
	}else{
		p=(node*)malloc(sizeof(node));
		p->n=n;
		p->next=creat(p->next);
	}
	return p;
}

//交换两节点 
node*SwapNode(node*head,node*p1,node*p2){
	node*tmp1,*tmp2,*tmp3;
	tmp1=tmp2=head;
	if(p1!=head)
		while(tmp1->next!=p1&&tmp1!=NULL){
			tmp1=tmp1->next;
		};
	if(p2!=head)
		while(tmp2->next!=p2&&tmp2!=NULL){
			tmp2=tmp2->next;
		};
	if(p1->next!=p2&&p2->next!=p1){
				if(p1!=head&&p2!=head){
					tmp3=p2->next;
					tmp1->next=p2;
					p2->next=p1->next;
					tmp2->next=p1;
					p1->next=tmp3;
				}else if(p1==head){
					head=p2;tmp3=p2->next;
					p2->next=p1->next;
					tmp2->next=p1;
					p1->next=tmp3;
				}else if(p2==head){
					head=p1;tmp3=p1->next;
					p1->next=p2->next;
					tmp1->next=p2;
					p2->next=tmp3;
				}
			}else{
				if(p1->next==p2){
					if(p1!=head){
						p1->next=p2->next;
						p2->next=p1;
						tmp1->next=p2;
					}else{
						p1->next=p2->next;
						head=p2;
						p2->next=p1;
					}
				}else if(p2->next==p1){
					if(head!=p2){
						p2->next=p1->next;
						p1->next=p2;
						tmp2->next=p1;
					}else{
						p2->next=p1->next;
						head=p1;
						p1->next=p2;
					}
				}
			}
	return head;
}

//链表递增排序,节点排序
node*SortNode(node*head){
	node*p1,*p2,*tmp;
	if(head==NULL)return head;
	p1=p2=head;
	while(p1!=NULL){
		p2=p1->next;
		while(p2!=NULL){
			if(p2->n<p1->n){
				tmp=p1;
				head=SwapNode(head,p1,p2);
				p1=p2;p2=tmp;
			}
			p2=p2->next;
		}
		p1=p1->next;
	};
	return head;
}

//链表递增排序，内容排序
node*SortValue(node*head){
	node*p1,*p2;int tmp;
	if(head==NULL)return head;
	p1=p2=head;
	while(p1!=NULL){
		p2=p1->next;
		while(p2!=NULL){
			if(p2->n<p1->n){
				tmp=p1->n;
				p1->n=p2->n;
				p2->n=tmp;
			}
			p2=p2->next;
		}
		p1=p1->next;
	};
	return head;
}

void print(node*p){
	if(p!=NULL){
		printf("%d->",p->n);
		print(p->next);
	}else{
		printf("NULL\n");
	}
	return ;
}

int main(){
	node*head=NULL;
	head=creat(head);
	head=SortNode(head);//对节点排序
	head=SortValue(head);//对内容排序
	print(head);
	return 0;
}
