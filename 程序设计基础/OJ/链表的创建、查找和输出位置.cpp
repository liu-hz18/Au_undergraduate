#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct node{
	char s[30];
	node*next;
};
void print(node*head){
	node*p1;
	if(head==NULL){
		printf("����Ϊ��!\n");
	}else{
		printf("��ǰ����Ϊ:");
		p1=head;
		while(p1->next!=NULL){
			printf("%s->",p1->s);
			p1=p1->next;
		};
		printf("%s->NULL\n",p1->s);
	};
	return ;
}
node*creat(){
	char s[30];node*p1,*p2,*head;
	head=p2=(node*)malloc(sizeof(node));
	while(1){
		printf("�������½ڵ��ַ���(��stop��������)��");
		gets_s(s);
		if(strcmp(s,"stop")==0){
			printf("��������!\n");break;
		}else{
			p1=p2;
			strcpy_s(p1->s,30,s);
			p1->next=NULL;
			print(head);
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
		}
	}
	p1->next=NULL;
	return head;
}
node*search(node*head,char*s){
	node*p1,*pre;int i=1;
	if(head==NULL)printf("����Ϊ��!\n");
	else{
		p1=pre=head;
		while(p1!=NULL&&strcmp(p1->s,s)!=0){
			//&&�ж����������ж�ǰ����жϺ��棬���ǰ�治���������Ͳ��жϺ��棬
			//��������Ӧ�ý�p1!=NULL����ǰ�棬�������Ա���Կ�ָ����в���
			pre=p1;
			p1=p1->next;
			i++;
		};
		if(p1==NULL){
			printf("δ�ҵ���Ӧ�ڵ���Ϣ��\n");
		}else if(strcmp(p1->s,s)==0){
			printf("�������Ľڵ�λ�ã�%d\n",i);
			if(p1!=head){
				pre->next=p1->next;
				p1->next=head;
				head=p1;
			}
		}
	}
	return head;
}

int main(){
	node*head;char s[30];
	head=creat();
	while(1){
		printf("������Ҫ���ҵ��ַ���(����quit��������):");
		gets_s(s);
		if(strcmp(s,"quit")==0){
			printf("���ҽ���!\n");break;
		}else{
			head=search(head,s);
			print(head);
		}
	};
	return 0;
}
