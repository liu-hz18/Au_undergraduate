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
		printf("链表为空!\n");
	}else{
		printf("当前链表为:");
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
		printf("请输入新节点字符串(按stop结束创建)：");
		gets_s(s);
		if(strcmp(s,"stop")==0){
			printf("创建结束!\n");break;
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
	if(head==NULL)printf("链表为空!\n");
	else{
		p1=pre=head;
		while(p1!=NULL&&strcmp(p1->s,s)!=0){
			//&&判断条件是先判断前面后判断后面，如果前面不符合条件就不判断后面，
			//所以这里应该将p1!=NULL放在前面，这样可以避免对空指针进行操作
			pre=p1;
			p1=p1->next;
			i++;
		};
		if(p1==NULL){
			printf("未找到对应节点信息！\n");
		}else if(strcmp(p1->s,s)==0){
			printf("检索到的节点位置；%d\n",i);
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
		printf("请输入要查找的字符串(输入quit结束查找):");
		gets_s(s);
		if(strcmp(s,"quit")==0){
			printf("查找结束!\n");break;
		}else{
			head=search(head,s);
			print(head);
		}
	};
	return 0;
}
