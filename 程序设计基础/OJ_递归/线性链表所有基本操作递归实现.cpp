//�ݹ�ʵ���������
#include<stdio.h>
#include<malloc.h>
struct node{
	int n;
	node*next;
};

//�ǵݹ��������
/*node*creat(){
	int n;node*head,*p1,*p2;
	p1=p2=head=(node*)malloc(sizeof(node));
	while(1){
		printf("����������ڵ��ֵ:");
		scanf_s("%d",&n);
		if(n!=0){
			p1=p2;
			p1->n=n;
			p2=(node*)malloc(sizeof(node));
			p1->next=p2;
		}else{
			p1->next=NULL;
			printf("�������!\n");
			break;
		}
	}
	return head;
}*/

//�ݹ鴴����������
node*creat(node*p){
	int n;
	printf("����������ڵ���Ϣ(��0��������):");
	scanf_s("%d",&n);
	if(n==0)p=NULL;
	else{
		p=(node*)malloc(sizeof(node));
		p->n=n;
		p->next=creat(p->next);
	}
	return p;
}

//ͳ�ƽڵ����
int CountNode(node*p){
	if(p==NULL)return 0;
	else return CountNode(p->next)+1;
}

//����Ԫ�غ�
int SumNode(node*p){
	if(p==NULL)return 0;
	else return SumNode(p->next)+p->n;
}

//�ݹ�ʵ��˳�����
void print(node*p1){

	if(p1!=NULL){
		printf("%d->",p1->n);
		print(p1->next);
	}else{
		printf("NULL\n");
		return;
	}
}

//�ݹ�ʵ�������������
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

//�ݹ�ʵ��������
//�Ƚ��С��������ĵ������⣬֮����ǰһ���ڵ����ӵ�����������֮��
node*reverse(node*head){
	if(head==NULL||head->next==NULL)return head;
	node*next=head->next;
	head->next=NULL;
	node*rest=reverse(next);
	next->next=head;
	return rest;
}

//�ݹ�ʵ�ֲ��ҽڵ�
void search(node*p,int n,int i){
	if(p==NULL)printf("δ�ҵ��ڵ���Ϣ��\n");
	else{
		if(p->n==n)printf("�ڵ�λ�ã�%d\n",i);
		else search(p->next,n,i+1);
	}
	return ;
}

//�ݹ�ʵ�ֵ�������
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

//�ݹ�ʵ�ֵݼ�����
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

//�ݹ�ʵ��ɾ���ڵ�
node*del(node*p,int n,node*pre,node*head){
	if(head==NULL);
	else{
		if(p==NULL){
			printf("Ҫɾ���Ľڵ���Ϣ������!\n");
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

//�ݹ�ʵ��ɾ��ȫ��ָ���ڵ�
node*DelAll(node*p,int n,node*pre,node**head,bool flag){
	if(*head==NULL)return NULL;
	else{
		if(p==NULL&&flag==false){
			printf("Ҫɾ���Ľڵ���Ϣ������!\n");
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

//�������ڵ� 
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

//�����������,�ڵ�����
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

//�������������������
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


//�ݹ�ʵ�������ĳһ���ֿ�ʼ����
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

//�ݹ�ɾ���ظ��ڵ�
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

//�ݹ��ͷ�����ڵ�
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
	}else printf("����Ϊ�գ�\n");
}

int main(){
	node*head=NULL,*p;int n,i,denum;
	head=creat(head);
	printf("˳������ڵ���Ϣ:\n");print(head);

	printf("�ڵ����:%d\n",CountNode(head));
	printf("�ڵ�Ԫ�غ�=%d\n",SumNode(head));

	printf("��������ڵ���Ϣ:\n");re_print(head,head);
	printf("�����Ľڵ���Ϣ:\n");head=reverse(head);print(head);
	printf("������Ҫ���ҵĽڵ���Ϣ:");
	scanf_s("%d",&n);
	search(head,n,1);

	//��������
	printf("������Ҫ����Ľڵ���Ϣ��");scanf_s("%d",&i);
	p=(node*)malloc(sizeof(node));p->n=i;
	head=insert_up(head,p,head,head);
	print(head);

	//�ݼ�����
	printf("������Ҫ����Ľڵ���Ϣ��");scanf_s("%d",&i);
	p=(node*)malloc(sizeof(node));p->n=i;
	head=insert_down(head,p,head,head);
	print(head);

	//ɾ������ڵ�
	printf("������Ҫɾ���Ľڵ���Ϣ;");scanf_s("%d",&denum);
	head=del(head,denum,head,head);
	printf("ɾ���ض��ڵ�������\n");
	print(head);
	
	//��ĳһ�ڵ㿪ʼ����
	printf("�����뵹��ʼ�Ľڵ���Ϣ:");
	scanf_s("%d",&n);
	head=SubSort(head,head,head,n,0);
	printf("��ָ���ڵ�֮���������:\n");
	print(head);
	
	//ɾ�������ظ��ڵ�
	DelRepeat(head,head);
	printf("ɾ�������ظ��ڵ�������:\n");
	print(head);

	//�ݹ�ɾ��ָ��ȫ���ڵ�
	printf("������Ҫȫ��ɾ���Ľڵ�����:");
	scanf_s("%d",&n);
	DelAll(head,n,head,&head,0);
	printf("ɾ��ȫ�������ڵ�֮�������:\n");
	print(head);

	head=SortNode(head);//�Խڵ�����
	print(head);

	head=SortValue(head);//����������
	print(head);

	FreeNode(head);
 	return 0;
}
