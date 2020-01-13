#include<stdio.h>
#include<malloc.h>
#define NULL 0
#define LEN sizeof(struct student)//�궨��һ���ṹ����ڴ泤��
struct student
{
	long num;
	float score;
	struct student*next;
};
int n;//ȫ�֣�ѧ������
struct student*creat()//��̬��������β�巨
{
	struct student*head;
	struct student*p1,*p2;
	//���� ���� ָ�������ʹ����һ���ڵ�����ʱ��ǰһ��ָ����Ȼ��������һ���ڵ����Ϣ
	n=0;
	p1=p2=(struct student*)malloc(LEN);//����ͷ�ڵ�
	scanf_s("%ld,%f",&p1->num,&p1->score);
	head=NULL;
	while(p1->num!=0)//����ѧ�Ų���0ʱ�������½ڵ㣬������һ��һ�������ɽڵ�
	{
		n++;//ѧ������+1
		if(n==1)head=p1;
		else p2->next=p1;
		p2=p1;//ͬ���ƶ�p2
		p1=(struct student*)malloc(LEN);//�����½ڵ㣬��ʱp2��ָ����һ���ڵ�
		scanf_s("%ld,%f",&p1->num,&p1->score);
	}
	p2->next=NULL;//��β�ÿ�
	return (head);//����������׵�ַ
}
/*ͷ�巨 �����㷨
   p1=(struct student*)malloc(LEN);
   scanf_s("%ld,%f",&p1->num,&p1->score);
   p1->next=head;
   head=p1;��ʱ��head�ȳ䵱ͷָ������ã����ڷ���p2������
   ע���β�ÿգ�����һ�δ����Ľڵ��ָ���ÿ�
*/
void print(struct student *head)//�������洢����
{
	struct student*p;//����һ��ָ�����
	printf("\nnow,these %d records are:\n",n);
	p=head;//pָ���ͷ
	if(head!=NULL)
	{
		do{
			printf("ѧ�ţ�%ld,�ɼ���%5.1f\n",p->num,p->score);
			p=p->next;//������һ���ڵ�
		}while(p!=NULL);
	}
	else printf("list null!\n");
}
struct student *insert(struct student *head,struct student *stud)//����ڵ㺯����ʵ�ְ���ѧ�ŵ�����˳����в���
{
	struct student *p0,*p1,*p2;//��������ָ�����
	p1=head;//p1�ó�ֵָ���ͷ
	p0=stud;//p0ָ�򱻲���Ľڵ�
	if(head==NULL)//������Ͳ��뵽��һλ����Ϊ��ͷ
	{
		head=p0;
		p0->next=NULL;
	}
	else{
		while((p0->num>p1->num)&&(p1->next!=NULL))//��������ȷ�Ĳ���λ�ã����ұ�֤��������β
		{
			p2=p1;
			p1=p1->next;
		}
		if(p0->num<=p1->num)//��ʾ�ڵ����β֮ǰ�ҵ��˺Ϸ��Ĳ���λ��
		{
			if(head==p1)head=p0;//���ڱ�ͷλ�ã����´�����ͷ
			else{
				p2->next=p0;//���м����
				p0->next=p1;
			}
		}
		else{//������β��Ȼû�м������Ϸ��Ĳ���λ�ã����ؽ���β
			p1->next=p0;
			p0->next=NULL;
		}
	}
	n++;//ѧ������+1
	return head;
}
struct student*del(struct student*head,long num)//ɾ���ڵ㺯��
{
	struct student *p1,*p2;//��������ָ�룬�ֱ�ָ�����ڵ������ڵ㣬ʹ�öϵ�֮���������������
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
		if(num==p1->num)//�ҵ���Ӧɾ���Ľڵ㣬������p1Ϊ��βʱ��Ȼ����
		{
			if(p1==head)
				head=p1->next;//������ԭ����head����ͷ����һλ��ʱ��ͷ��Ȼ���ڣ����ǲ��������С�
			else p2->next=p1->next;//����p1
			printf("delete :%ld\n",num);
			n--;//ѧ������-1
		}
		else printf("%ld not been found��\n",num);//����β��Ȼû�ҵ�
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
	stu=(struct student*)malloc(LEN);//�´����ڵ�洢���������
	//�����ʱ���´����ڵ㣬��ô������ֵʱ�ͣ��µ�ֵ�Ḳ�Ǿɵ�ֵ�������ı��������ж�Ӧλ�õĴ洢��Ϣ��
	//������insert�����У��ڶ����²���Ľڵ�����numֵ���һ�β���ڵ��num���
	//��ʹ��p0->nextָ��p0���Ӷ���������м�����������Ľڵ㣬��β��ʧ��������ֹ�����stu����Ϣ
	scanf_s("%ld,%f",&stu->num,&stu->score);
	while(stu->num!=0)
	{
		head=insert(head,stu);
		printf("input the inserted record:");
		stu=(struct student*)malloc(LEN);//�´����ڵ�洢���������
		scanf_s("%ld,%f",&stu->num,&stu->score);
	}
	return 0;
}
