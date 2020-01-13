#include<stdio.h>
#include<malloc.h>
#define NULL 0
#define LEN sizeof(struct student)//宏定义一个结构体的内存长度
struct student
{
	long num;
	float score;
	struct student*next;
};
int n;//全局，学生总数
struct student*creat()//动态生成链表，尾插法
{
	struct student*head;
	struct student*p1,*p2;
	//定义 两个 指针变量，使得下一个节点生成时，前一个指针依然保留了上一个节点的信息
	n=0;
	p1=p2=(struct student*)malloc(LEN);//生成头节点
	scanf_s("%ld,%f",&p1->num,&p1->score);
	head=NULL;
	while(p1->num!=0)//输入学号不是0时，生成新节点，并且是一个一个地生成节点
	{
		n++;//学生总数+1
		if(n==1)head=p1;
		else p2->next=p1;
		p2=p1;//同步移动p2
		p1=(struct student*)malloc(LEN);//生成新节点，此时p2仍指向上一个节点
		scanf_s("%ld,%f",&p1->num,&p1->score);
	}
	p2->next=NULL;//表尾置空
	return (head);//返回链表的首地址
}
/*头插法 核心算法
   p1=(struct student*)malloc(LEN);
   scanf_s("%ld,%f",&p1->num,&p1->score);
   p1->next=head;
   head=p1;此时的head既充当头指针的作用，又在发挥p2的作用
   注意表尾置空，即第一次创建的节点的指针置空
*/
void print(struct student *head)//输出链表存储内容
{
	struct student*p;//定义一个指针变量
	printf("\nnow,these %d records are:\n",n);
	p=head;//p指向表头
	if(head!=NULL)
	{
		do{
			printf("学号：%ld,成绩：%5.1f\n",p->num,p->score);
			p=p->next;//跳到下一个节点
		}while(p!=NULL);
	}
	else printf("list null!\n");
}
struct student *insert(struct student *head,struct student *stud)//插入节点函数，实现按照学号递增的顺序进行插入
{
	struct student *p0,*p1,*p2;//定义三个指针变量
	p1=head;//p1置初值指向表头
	p0=stud;//p0指向被插入的节点
	if(head==NULL)//空链表就插入到第一位，作为表头
	{
		head=p0;
		p0->next=NULL;
	}
	else{
		while((p0->num>p1->num)&&(p1->next!=NULL))//检索到正确的插入位置，并且保证不超出表尾
		{
			p2=p1;
			p1=p1->next;
		}
		if(p0->num<=p1->num)//表示在到达表尾之前找到了合法的插入位置
		{
			if(head==p1)head=p0;//若在表头位置，重新创建表头
			else{
				p2->next=p0;//在中间插入
				p0->next=p1;
			}
		}
		else{//当到表尾依然没有检索到合法的插入位置，就重建表尾
			p1->next=p0;
			p0->next=NULL;
		}
	}
	n++;//学生总数+1
	return head;
}
struct student*del(struct student*head,long num)//删除节点函数
{
	struct student *p1,*p2;//定义两个指针，分别指向相邻的两个节点，使得断点之间的连接有了依据
	if(head!=NULL)
	{
		printf("\nlist null!\n");
	}
	else{
		p1=head;
		while(num!=p1->num&&p1->next!=NULL)
		{
			p2=p1;
			p1=p1->next;
		}
		if(num==p1->num)//找到了应删除的节点，并且在p1为表尾时依然适用
		{
			if(p1==head)
				head=p1->next;//丢弃了原来的head，表头后移一位此时表头依然存在，但是不在链表中。
			else p2->next=p1->next;//丢弃p1
			printf("delete :%ld\n",num);
			n--;//学生总数-1
		}
		else printf("%ld not been found！\n",num);//到表尾依然没找到
	}
	return head;
}
int main()
{
	struct student*head,*stu;
	long del_num;
	printf("input records:\n");
	head=creat();
	print(head);
	printf("\ninput the deleted number:");
	scanf_s("%d",&del_num);
	while(del_num!=0)
	{
		head=del(head,del_num);
		print(head);
		printf("input the deleted number:");
		scanf_s("%ld",&del_num);
	}
	printf("\ninput the inserted record:");
	stu=(struct student*)malloc(LEN);//新创建节点存储输入的内容
	//如果此时不新创建节点，那么插入多个值时就，新的值会覆盖旧的值，进而改变了链表中对应位置的存储信息，
	//并且在insert函数中，第二次新插入的节点由于num值与第一次插入节点的num相等
	//会使得p0->next指向p0，从而在链表的中间会出现连向本身的节点，表尾丢失，会无终止地输出stu的信息
	scanf_s("%ld,%f",&stu->num,&stu->score);
	while(stu->num!=0)
	{
		head=insert(head,stu);
		printf("input the inserted record:");
		stu=(struct student*)malloc(LEN);//新创建节点存储输入的内容
		scanf_s("%ld,%f",&stu->num,&stu->score);
	}
	return 0;
}
