/*yqy 2016.1*/
/*�������̶ܹ����ȱ�øо�����ţ��w
��¼�ˣ�
1������insert����
2��ɾ������Del����
3��print����
�����뵽�ľ��ǽ�����㺯�����Ǹ�̫������˲����orz*/ 
#include<stdlib.h>
#include<stdio.h>

typedef struct node{
	int len;
	struct node *next;
}NODE;
NODE *insert(NODE *head)//��һ�����˳���������,���ں�벿�ּ�����ν�ġ���ӡ� 
{
	NODE *p1=head,*p2,*current;
	current=(NODE *)malloc(sizeof(NODE));
	printf("��������Ϣ��\n");scanf("%d",&current->len);
	current->next=NULL;//�½ڵ���Ϣ
	
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
		if (p1->len>current->len)//����
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
		else//���
			;
	}
	return head; 
}
NODE *Del(NODE *head,int len)//��������ɾ��ֵΪlen�Ľ�� 
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
	printf("ɾ��%d��\n",n);
	head=Del(head,n);
	print(head);
	return 0;
} 
