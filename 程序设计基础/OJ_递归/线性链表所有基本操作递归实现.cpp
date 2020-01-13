//递归实现链表操作
#include<stdio.h>
#include<malloc.h>
struct node{
	int n;
	node*next;
};

//非递归的链表创建
/*node*creat(){
	int n;node*head,*p1,*p2;
	p1=p2=head=(node*)malloc(sizeof(node));
	while(1){
		printf("请输入链表节点的值:");
		scanf_s("%d",&n);
		if(n!=0){
			p1=p2;
			p1->n=n;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
		}else{
			p1->next=NULL;
			printf("输入结束!\n");
			break;
		}
	}
	return head;
}*/

//递归创建线性链表
node*creat(node*p){
	int n;
	printf("请输入链表节点信息(按0结束创建):");
	scanf_s("%d",&n);
	if(n==0)p=NULL;
	else{
		p=(node*)malloc(sizeof(node));
		p->n=n;
		p->next=creat(p->next);
	}
	return p;
}

//统计节点个数
int CountNode(node*p){
	if(p==NULL)return 0;
	else return CountNode(p->next)+1;
}

//链表元素和
int SumNode(node*p){
	if(p==NULL)return 0;
	else return SumNode(p->next)+p->n;
}

//递归实现顺序输出
void print(node*p1){

	if(p1!=NULL){
		printf("%d->",p1->n);
		print(p1->next);
	}else{
		printf("NULL\n");
		return;
	}
}

//递归实现链表逆序输出
void re_print(node*p,node*head){
	if(p!=NULL){
		re_print(p->next,head);
		printf("<-%d",p->n);
		if(p==head)printf("\n");
	}else{
		printf("NULL");
		return;
	}
}

//递归实现链表倒序
//先解决小部分链表的倒序问题，之后将其前一个节点连接到倒序后的链表之后
node*reverse(node*head){
	if(head==NULL||head->next==NULL)return head;
	node*next=head->next;
	head->next=NULL;
	node*rest=reverse(next);
	next->next=head;
	return rest;
}

//递归实现查找节点
void search(node*p,int n,int i){
	if(p==NULL)printf("未找到节点信息！\n");
	else{
		if(p->n==n)printf("节点位置：%d\n",i);
		else search(p->next,n,i+1);
	}
	return ;
}

//递归实现递增插入
node*insert_up(node*p1,node*p,node*pre,node*head){
	if(p1==NULL&&pre==NULL){
		head=p;p->next=NULL;
	}else if(p1==NULL&&pre!=NULL){
		pre->next=p;
		p->next=NULL;
	}else{
		if(p->n>p1->n){
			return insert_up(p1->next,p,p1,head);
		}else if(p1!=head){
			pre->next=p;
			p->next=p1;
		}
		else if(p1==head){
			head=p;p->next=p1;
		}
	}
	return head;
}

//递归实现递减插入
node*insert_down(node*p1,node*p,node*pre,node*head){
	if(p1==NULL&&pre==NULL){
		head=p;p->next=NULL;
	}else if(p1==NULL&&pre!=NULL){
		pre->next=p;
		p->next=NULL;
	}else{
		if(p->n<p1->n){
			return insert_down(p1->next,p,p1,head);
		}else if(p1!=head){
			pre->next=p;
			p->next=p1;
		}
		else if(p1==head){
			head=p;p->next=p1;
		}
	}
	return head;
}

//递归实现删除节点
node*del(node*p,int n,node*pre,node*head){
	if(head==NULL);
	else{
		if(p==NULL){
			printf("要删除的节点信息不存在!\n");
		}else{	
			if(p->n!=n)return del(p->next,n,p,head);
			else if(p->n==n&&p->next==NULL){
				pre->next=NULL;
			}else if(p->n==n&&p==head){
				head=p->next;
			}else {
				pre->next=p->next;
			}
		}
	}
	return head;
}

//递归实现删除全部指定节点
node*DelAll(node*p,int n,node*pre,node**head,bool flag){
	if(*head==NULL)return NULL;
	else{
		if(p==NULL&&flag==false){
			printf("要删除的节点信息不存在!\n");
		}else if(p!=NULL){	
			if(p->n!=n)DelAll(p->next,n,p,head,flag);
			else{
				flag=1;
				if(p->next==NULL){
					pre->next=NULL;
				}else if(p==*head){
					*head=p->next;
					DelAll(p,n,p,head,flag);
				}else{
					pre->next=p->next;
					DelAll(p->next,n,pre,head,flag);
				}
			}
		}else if(p==NULL){
			return *head;
		}
	}
	return *head;
}

//交换两节点 
node*SwapNode(node*head,node*p1,node*p2){
	node*tmp1,*tmp2,*tmp3;
	tmp1=tmp2=head;
	if(p1!=head)
		while(tmp1->next!=p1&&tmp1!=NULL){
			tmp1=tmp1->next;
		};
	if(p2!=head)
		while(tmp2->next!=p2&&tmp2!=NULL){
			tmp2=tmp2->next;
		};
	if(p1->next!=p2&&p2->next!=p1){
				if(p1!=head&&p2!=head){
					tmp3=p2->next;
					tmp1->next=p2;
					p2->next=p1->next;
					tmp2->next=p1;
					p1->next=tmp3;
				}else if(p1==head){
					head=p2;tmp3=p2->next;
					p2->next=p1->next;
					tmp2->next=p1;
					p1->next=tmp3;
				}else if(p2==head){
					head=p1;tmp3=p1->next;
					p1->next=p2->next;
					tmp1->next=p2;
					p2->next=tmp3;
				}
			}else{
				if(p1->next==p2){
					if(p1!=head){
						p1->next=p2->next;
						p2->next=p1;
						tmp1->next=p2;
					}else{
						p1->next=p2->next;
						head=p2;
						p2->next=p1;
					}
				}else if(p2->next==p1){
					if(head!=p2){
						p2->next=p1->next;
						p1->next=p2;
						tmp2->next=p1;
					}else{
						p2->next=p1->next;
						head=p1;
						p1->next=p2;
					}
				}
			}
	return head;
}

//链表递增排序,节点排序
node*SortNode(node*head){
	node*p1,*p2,*tmp;
	if(head==NULL)return head;
	p1=p2=head;
	while(p1!=NULL){
		p2=p1->next;
		while(p2!=NULL){
			if(p2->n<p1->n){
				tmp=p1;
				head=SwapNode(head,p1,p2);
				p1=p2;p2=tmp;
			}
			p2=p2->next;
		}
		p1=p1->next;
	};
	return head;
}

//链表递增排序，内容排序
node*SortValue(node*head){
	node*p1,*p2;int tmp;
	if(head==NULL)return head;
	p1=p2=head;
	while(p1!=NULL){
		p2=p1->next;
		while(p2!=NULL){
			if(p2->n<p1->n){
				tmp=p1->n;
				p1->n=p2->n;
				p2->n=tmp;
			}
			p2=p2->next;
		}
		p1=p1->next;
	};
	return head;
}


//递归实现链表从某一部分开始倒序
node*SubSort(node*p,node*pre,node*head,int n,bool flag){
	node*tmp,*rest;
	if(flag==false){
		if(p->n==n){
			tmp=p->next;
			p->next=NULL;
			rest=SubSort(tmp,p,head,n,1);
			pre->next=rest;
			tmp->next=p;
			return head;
		}else{
			SubSort(p->next,p,head,n,0);
			return head;
		}
	}else if(flag==true){
		if(p!=NULL&&p->next!=NULL){
			tmp=p->next;
			p->next=NULL;
			rest=SubSort(tmp,p,head,n,1);			
			tmp->next=p;
			return rest;
		}else return p;
	}
	return head;
}

//递归删除重复节点
void DelRepeat(node*p,node*head){
	if(p==NULL||p->next==NULL);
	else{
		if(p->next->n==p->n&&p->next!=NULL){
			p->next=p->next->next;
			DelRepeat(p,head);
		}else{
			DelRepeat(p->next,head);
		}
	}
}

//递归释放链表节点
void FreeNode(node*p){
	if(p!=NULL){
		if(p->next!=NULL){
			node*tmp=p->next;
			free(p);
			p=tmp;
		}else{
			free(p);
			return;
		}
	}else printf("链表为空！\n");
}

int main(){
	node*head=NULL,*p;int n,i,denum;
	head=creat(head);
	printf("顺序输出节点信息:\n");print(head);

	printf("节点个数:%d\n",CountNode(head));
	printf("节点元素和=%d\n",SumNode(head));

	printf("逆序输出节点信息:\n");re_print(head,head);
	printf("倒序后的节点信息:\n");head=reverse(head);print(head);
	printf("请输入要查找的节点信息:");
	scanf_s("%d",&n);
	search(head,n,1);

	//递增插入
	printf("请输入要插入的节点信息：");scanf_s("%d",&i);
	p=(node*)malloc(sizeof(node));p->n=i;
	head=insert_up(head,p,head,head);
	print(head);

	//递减插入
	printf("请输入要插入的节点信息：");scanf_s("%d",&i);
	p=(node*)malloc(sizeof(node));p->n=i;
	head=insert_down(head,p,head,head);
	print(head);

	//删除链表节点
	printf("请输入要删除的节点信息;");scanf_s("%d",&denum);
	head=del(head,denum,head,head);
	printf("删除特定节点后的链表：\n");
	print(head);
	
	//从某一节点开始倒序
	printf("请输入倒序开始的节点信息:");
	scanf_s("%d",&n);
	head=SubSort(head,head,head,n,0);
	printf("从指定节点之后倒序的链表:\n");
	print(head);
	
	//删除连续重复节点
	DelRepeat(head,head);
	printf("删除连续重复节点后的链表:\n");
	print(head);

	//递归删除指定全部节点
	printf("请输入要全部删除的节点数据:");
	scanf_s("%d",&n);
	DelAll(head,n,head,&head,0);
	printf("删除全部特征节点之后的链表:\n");
	print(head);

	head=SortNode(head);//对节点排序
	print(head);

	head=SortValue(head);//对内容排序
	print(head);

	FreeNode(head);
 	return 0;
}
