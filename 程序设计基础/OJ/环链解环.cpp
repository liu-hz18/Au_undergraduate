#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
struct node
{
	int num;
	struct node *next;
};
struct node *create();
void openloop(struct node *);
void print(struct node *);
void main()
{
	struct node *head;
	srand((unsigned)time(NULL));
	head = create();
	openloop(head);
	print(head);
}
//Ҫ����һ����X��Y�������������������s=rand()%(x-Y+1)+Y�����ʾ��X��Y��Χ�ڵ������
struct node *create()
{
	int n = 0;
	struct node *p1, *p2, *head;
	int i;
	int randomIndex ;
    head=NULL;
	p1=NULL;
	p2=NULL;
	while(n==0)//�����ĳ������
		n=((int)rand())%20;
	for(i=0;i<n;i++)
	{
		p1=(struct node*)malloc(sizeof(struct node));
		p1->next = NULL;
		p1->num = ((int)rand());//ÿ�ڵ��������
		if(i == 0)
			head = p1;
		else
			p2->next = p1;
		p2=p1;
	}
	//��ʱp1������β�ڵ����Ϣ
    if (head!=NULL)//������Ϊ��ʱ������ɻ�
	{
		randomIndex =((int)rand())%n; //����ɻ��Ľڵ�
		p2=head;
		for(i=0; i<randomIndex; i++)
			p2 = p2->next;//�ҵ��ɻ��Ľڵ�
		p1->next = p2;
	}
	return head;
}
void openloop(node*head)
{
	node*p1,*p2;
	int count=0,i=0,j,*add,flag=0;
	p1=p2=head;
	add=(int*)malloc(20*sizeof(int));
	//��̬�����ڴ��ǲ�������һ������һ���ģ���ͽڵ㲻ͬ��Ϊ�����ڵ��ƹ�ϵ�����ǿ���ͨ��realloc������ԭ���ռ�Ļ��������������ɿռ�
	while(1){
		flag=0;
		*(add+i)=(int)(p1);//��̬��������洢����ÿ���ڵ�ĵ�ַ����&(*p)�ȼ���p
		//(*p)ָ����һ���ڵ�ĵ�ַ��ÿ���ڵ�ĵ�ַ�洢�˸ýڵ��Ψһ���������ڲ�������������Բ����Խڵ�����Ϊ�ж����ݣ�
		for(j=0;j<i;j++){
			if(*(add+j)==*(add+i)){flag=1;break;}
		}
		if(flag==1){
			p2->next=NULL;
			break;
		}
		else{ 
			p2=p1;
			p1=p1->next;
		}
		i++;
	}
}
void print(node*head)
{
	node*p1;
	p1=head;
	printf("��ǰ��������Ϊ��\n");
	while(p1!=NULL){
		printf("%d -> ",p1->num);
		p1=p1->next;
	}
	if(p1==NULL)printf("NULL\n");
}
