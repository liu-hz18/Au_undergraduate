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
//要产生一个从X到Y的随机数，可以这样：s=rand()%(x-Y+1)+Y，这表示从X到Y范围内的随机数
struct node *create()
{
	int n = 0;
	struct node *p1, *p2, *head;
	int i;
	int randomIndex ;
    head=NULL;
	p1=NULL;
	p2=NULL;
	while(n==0)//环链的长度随机
		n=((int)rand())%20;
	for(i=0;i<n;i++)
	{
		p1=(struct node*)malloc(sizeof(struct node));
		p1->next = NULL;
		p1->num = ((int)rand());//每节点内容随机
		if(i == 0)
			head = p1;
		else
			p2->next = p1;
		p2=p1;
	}
	//此时p1保留了尾节点的信息
    if (head!=NULL)//当链表不为空时，随机成环
	{
		randomIndex =((int)rand())%n; //随机成环的节点
		p2=head;
		for(i=0; i<randomIndex; i++)
			p2 = p2->next;//找到成环的节点
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
	//动态创建内存是不能遇到一个创建一个的，这和节点不同因为不存在递推关系，但是可以通过realloc函数在原来空间的基础上再申请若干空间
	while(1){
		flag=0;
		*(add+i)=(int)(p1);//动态创建数组存储链表每个节点的地址，即&(*p)等价于p
		//(*p)指向下一个节点的地址，每个节点的地址存储了该节点的唯一特征（由于采用随机数，所以不能以节点数据为判断依据）
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
	printf("当前链表内容为：\n");
	while(p1!=NULL){
		printf("%d -> ",p1->num);
		p1=p1->next;
	}
	if(p1==NULL)printf("NULL\n");
}
