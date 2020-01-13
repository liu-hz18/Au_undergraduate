#include<stdio.h>
#include<malloc.h>
struct node{
	int n;
	node*next;
};
void print(node*head){
	node*p1;
	if(head!=NULL){
		p1=head;
		while(p1!=NULL){
			printf("%d->",p1->n);
			p1=p1->next;
		};
		printf("NULL\n");
	}
}
node*creat(int*count){
	int n;node*p1,*p2,*head;*count=0;
	p1=p2=head=(node*)malloc(sizeof(node));
	while(1){
		printf("请输入整数:");
		scanf_s("%d",&n);
		if(n!=0){
			p1=p2;
			p1->n=n;(*count)++;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
		}else{
			p1->next=NULL;
			break;
		}
	}
	return head;
}
node*exchange(node*head,int count){
	int i,j,k,m;node*p1,*tmp1,*p2,*tmp2,*p3,*tmp3;
	while(head!=NULL){
		printf("请输入两个节点编号:");
		scanf_s("%d%d",&i,&j);
		if(i>0&&i<=count&&j>0&&j<=count){
			p1=p2=p3=head;
			for(k=1;k<i;k++){tmp1=p1;p1=p1->next;}
			for(m=1;m<j;m++){tmp2=p2;p2=p2->next;}
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
			break;
		}else{
			printf("您输入的节点位置有误,请重新输入!\n");
		}
	}
	return head;
}
int main(){
	char ch;node*head;int count;
	while((ch=getchar())!='@'){
		head=creat(&count);
		printf("交换前的链表:\n");print(head);
		head=exchange(head,count);
		printf("交换后的链表:\n");print(head);
		getchar();
		printf("是否继续?按@结束程序");
	}
	return 0;
}
