#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct letter{
	char ch;
	int time;
	letter*next;
};

letter*create(letter*head,char lett){
	int flag=0;
	letter*p,*p1,*p2;p=head;
	if(head==NULL){
		p1=(letter*)malloc(sizeof(letter));
		p1->ch=lett;p1->time=1;p1->next=NULL;
		head=p1;
	}else{
		while(p!=NULL){
			if(p->ch==lett){
				flag=1;	
				p->time++;
				break;
			}
			p2=p;//为保证在结尾的插入顺利进行，需要用一个指针保存p的上一次的值，这样下面即可以直接连接新节点
			p=p->next;
		};
		if(flag==0){
			p1=(letter*)malloc(sizeof(letter));
			p1->ch=lett;p1->time=1;p1->next=NULL;
			p2->next=p1;
		}
	}
	return head;
}
letter*lettercount(char*str){
	int i,len=strlen(str);
	letter*head=NULL;
	for(i=0;i<len;i++){
		if(str[i]!=' ')head=create(head,str[i]);
	}
	return head;
}
void listcount(letter*head){
	letter*p;
	p=head;
	while(p!=NULL){
		printf("%c(%d) ",p->ch,p->time);
		p=p->next;
	}
}
int main()
{
	char str[100];
	letter*head;
	printf("please input the string:\n");
	gets_s(str);
	head=lettercount(str);
	listcount(head);
	return 0;
}
