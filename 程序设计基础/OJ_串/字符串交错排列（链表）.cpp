#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct node{
	char ch;
	node*next;
};
node*insert(char*p){
	int i;node*head,*p1,*p2;
	head=p1=(node*)malloc(sizeof(node));
	for(i=0;i<(int)strlen(p)-1;i++){
		p1->ch=p[i];
		p2=(node*)malloc(sizeof(node));
		p1->next=p2;
		p1=p2;
	}
	p1->ch=p[i];p1->next=NULL;
	return head;
}
void list(node*head){
	node*p1=head;
	while(p1!=NULL){
		printf("%c->",p1->ch);
		p1=p1->next;
	};
	printf("NULL\n");
	return ;
}
node*interlaced(node*head1,node*head2){
	node*p1,*p2,*ptr1,*ptr2,*head;
	if(head1!=NULL&&head2!=NULL){
		ptr1=head1;ptr2=head2;
		head=p1=p2=(node*)malloc(sizeof(node));
		while(ptr1!=NULL&&ptr2!=NULL){
			p1=p2;p1->ch=ptr1->ch;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
			p1=p2;ptr1=ptr1->next;
			p1->ch=ptr2->ch;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
			ptr2=ptr2->next;
		};
		while(ptr1!=NULL&&ptr2==NULL){
			p1=p2;p1->ch=ptr1->ch;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
			ptr1=ptr1->next;
		};
		while(ptr1==NULL&&ptr2!=NULL){
			p1=p2;p1->ch=ptr2->ch;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
			ptr2=ptr2->next;
		};
		p1->next=NULL;
	}
	return head;
}
void input(char**str1,char**str2){
	printf("ÇëÊäÈë×Ö·û´®1:\n");
	gets_s(*str1,100);
	printf("ÇëÊäÈë×Ö·û´®2:\n");
	gets_s(*str2,100);
	return ;
}
void FreeNode(node*head){
	node*p1=head,*p2;
	if(head!=NULL){
		while(p1->next!=NULL){
			p2=p1->next;
			free(p1);
			p1=p2;
		};
		free(p1);
	}
	return ;
}
int main(){
	char ch,s1[100],s2[100],*p1=s1,*p2=s2;
	node*head1,*head2,*head;
	while((ch=getchar())!='@'){
		input(&p1,&p2);
		head1=insert(p1);head2=insert(p2);
		printf("×Ö·û´®1:\n");list(head1);
		printf("×Ö·û´®2:\n");list(head2);
		head=interlaced(head1,head2);
		printf("½»´íÅÅÁÐµÄ×Ö·û´®:\n");
		list(head);
		FreeNode(head);FreeNode(head2);FreeNode(head1);
		printf("ÊÇ·ñ¼ÌÐø?°´@½áÊø³ÌÐò:");
	};
	return 0;
}
