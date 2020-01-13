#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct node{
	char num[20];
	char name[30];
	int stuclass;
	float score;
	node*next;
};
node*creat(){
	int flag;
	node*p1,*p2,*head,*p3,*tmp;
	head=p1=p2=(node*)malloc(sizeof(node));
	printf("请输入学生信息:\n");
	do{
		tmp=p1;p1=p2;
		while(1){
			p3=head;flag=1;
			scanf_s("%s%s%d%f",p1->num,20,p1->name,30,&p1->stuclass,&p1->score);
			getchar();
			while(p3!=p1&&p1!=head){
				if(strcmp(p3->num,p1->num)==0){flag=0;printf("此学号已经输入，请重新输入!\n");break;}
				p3=p3->next;
			}
			if(flag==1)break;
		}
		p2=(node*)malloc(sizeof(node));
		p1->next=p2;
	}while(p1->stuclass!=0);
	tmp->next=NULL;
	return head;
}
void print(node*head){
	node*p1;
	if(head!=NULL){
		p1=head;
		printf("学号        姓名                  班级 成绩\n");
		while(p1!=NULL){
			printf("%10s %-22s%2d%10.2f\n",p1->num,p1->name,p1->stuclass,p1->score);
			p1=p1->next;
		};
	}
	else printf("Error!链表为空!\n");
}
void division(node*head,node**head1,node**head2,node**head3){
	node*p1,*tmp1,*p2,*tmp2,*p3,*tmp3,*p0,*p,*tmp;
	p0=head;*head1=*head2=NULL;
	*head3=p3=tmp3=(node*)malloc(sizeof(node));
	while(p0!=NULL){
		//三班按输入顺序排序
		if(p0->stuclass==3){
			p3=tmp3;
			strcpy_s(p3->name,30,p0->name);strcpy_s(p3->num,20,p0->num);p3->score=p0->score;p3->stuclass=p0->stuclass;
			tmp3=(node*)malloc(sizeof(node));
			p3->next=tmp3;
		}
		//一班递减排序
		if(p0->stuclass==1){
			if(*head1==NULL){
				*head1=p1=tmp1=(node*)malloc(sizeof(node));
				strcpy_s(p1->name,30,p0->name);strcpy_s(p1->num,20,p0->num);p1->score=p0->score;p1->stuclass=p0->stuclass;
				p1->next=NULL;
			}else{
				tmp1=(node*)malloc(sizeof(node));p=*head1;
				while((p0->score)<=(p->score)&&p->next!=NULL){
					tmp=p;p=p->next;
				};
				if(p->next!=NULL){
					p1=tmp1;
					strcpy_s(p1->name,30,p0->name);strcpy_s(p1->num,20,p0->num);p1->score=p0->score;p1->stuclass=p0->stuclass;
					if(p!=*head1){p1->next=p->next;p->next=p1;}
					else {*head1=p1;p1->next=p;}
				}else if(p->next==NULL){
					p1=tmp1;
					strcpy_s(p1->name,30,p0->name);strcpy_s(p1->num,20,p0->num);p1->score=p0->score;p1->stuclass=p0->stuclass;
					p->next=p1;p1->next=NULL;
				}
			}
		}
		//二班递增排序
		if(p0->stuclass==2){
			if(*head2==NULL){
				*head2=p2=tmp2=(node*)malloc(sizeof(node));
				strcpy_s(p2->name,30,p0->name);strcpy_s(p2->num,20,p0->num);p2->score=p0->score;p2->stuclass=p0->stuclass;
				p2->next=NULL;
			}else{
				tmp2=(node*)malloc(sizeof(node));p=*head2;
				while((p0->score)>=(p->score)&&p->next!=NULL){
					tmp=p;p=p->next;
				};
				if(p->next!=NULL){
					p2=tmp2;
					strcpy_s(p2->name,30,p0->name);strcpy_s(p2->num,20,p0->num);p2->score=p0->score;p2->stuclass=p0->stuclass;
					if(p!=*head2){
						p2->next=p;tmp->next=p2;
					}else{
						*head2=p2;
						p2->next=p;
					}
				}else if(p->next==NULL){
					p2=tmp2;
					strcpy_s(p2->name,30,p0->name);strcpy_s(p2->num,20,p0->num);p2->score=p0->score;p2->stuclass=p0->stuclass;
					p->next=p2;p2->next=NULL;
				}
			}
		}
		p0=p0->next;
	};
	p3->next=NULL;
	return ;
}
int calculate(node*head,float score){
	node*p1;int rank=1;
	p1=head;
	while(p1!=NULL){
		if(score<p1->score)rank++;
		p1=p1->next;
	}
	return rank;
}
int rank(node*head1,node*head2,node*head3,int*stuclass,char num[]){
	int rank=0;node*p1;
	p1=head1;
	while(p1!=NULL){
		if(strcmp(p1->num,num)==0){
			*stuclass=p1->stuclass;
			rank=calculate(head1,p1->score);
			break;
		}
		p1=p1->next;
	}
	p1=head2;
	while(p1!=NULL){
		if(strcmp(p1->num,num)==0){
			*stuclass=p1->stuclass;
			rank=calculate(head2,p1->score);
			break;
		}
		p1=p1->next;
	}
	p1=head3;
	while(p1!=NULL){
		if(strcmp(p1->num,num)==0){
			*stuclass=p1->stuclass;
			rank=calculate(head3,p1->score);
			break;
		}
		p1=p1->next;
	}
	return rank;
}
void output(node*head,node*head1,node*head2,node*head3){
	printf("全部学生信息:\n");print(head);
	printf("一班学生信息:\n");print(head1);
	printf("二班学生信息:\n");print(head2);
	printf("三班学生信息:\n");print(head3);
}
void search(node*head1,node*head2,node*head3){
	int r,stuclass;char num[20];
	while(1){
		printf("请输入要查找的学生学号:(输入0000000000时结束)");
		gets_s(num);
		if(strcmp(num,"0000000000")!=0){
			r=rank(head1,head2,head3,&stuclass,num);
			if(r!=0){
				printf("该学生班级为；%d,名次为:%d\n",stuclass,r);
			}else printf("该学生不存在!\n");
		}else break;
	}
}
int main(){
	node*head1=NULL,*head2=NULL,*head3=NULL,*head;
	head=creat();
	division(head,&head1,&head2,&head3);
	output(head,head1,head2,head3);
	search(head1,head2,head3);
	return 0;
}
