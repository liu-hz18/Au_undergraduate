/*yqy 2016.1*/
/*链表函数很固定，先编好感觉会变得牛逼w
收录了：
1、灵活的insert函数
2、删除结点的Del函数
3、print函数
还有想到的就是交换结点函数，那个太多情况了不会编orz*/ 
#include<stdlib.h>
#include<stdio.h>

typedef struct node{
	int len;
	struct node *next;
}NODE;
NODE *insert(NODE *head)//将一个结点顺序加入链表,可在后半部分加入所谓的“添加” 
{
	NODE *p1=head,*p2,*current;
	current=(NODE *)malloc(sizeof(NODE));
	printf("输入结点信息：\n");scanf("%d",&current->len);
	current->next=NULL;//新节点信息
	
	while(p1!=NULL && p1->len<current->len)
	{
		p2=p1;
		p1=p1->next;
	}
	if (p1==NULL)
	{
		if (p1==head) head=current;
		else 
			p2->next=current;
	}
	else 
	{
		if (p1->len>current->len)//插入
		{
			if(p1==head)
			{
				current->next=head;
				head=current;
			}
			else
			{
				p2->next=current;
				current->next=p1;
			}
		}
		else//添加
			;
	}
	return head; 
}
NODE *Del(NODE *head,int len)//从链表中删除值为len的结点 
{
	NODE *p1=head,*p2;
	while(p1!=NULL && p1->len!=len)
	{
		p2=p1;
		p1=p1->next;
	}
	if (p1==NULL) printf("error!\n");
	else
	{
		if (p1==head)
			head=p1->next;
		else
			p2->next=p1->next;
		free(p1);
	}
	return head;
}
void print(NODE *head)
{
	NODE *p=head;
	//printf("the records are\n");
	while(1)
	{
		printf("%d->",p->len);
		p=p->next;
		if(p==NULL)
		{
			printf("NULL\n");
			break;
		} 
	}
}
int main()
{
	NODE *head=NULL;
	int i,n=5;
	for(i=0;i<5;i++)
	{
		head=insert(head);
		print(head);
	}
	printf("删除%d后\n",n);
	head=Del(head,n);
	print(head);
	return 0;
} 
