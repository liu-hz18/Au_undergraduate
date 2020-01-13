//矩阵按行(循环)链表进行存储
#include<stdio.h>
#include<malloc.h>
struct node{
	int aij;
	node*next;
};
//不调用任何库函数？？？
//如何使用数组指针对a的行列值进行修改??
void input(int***a,int*m,int*n){
	int i,j;
	printf("please input m n of matrix A:");
	scanf_s("%d%d",m,n);
	*a=(int**)malloc(*m*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc(*n*sizeof(int));
	}
	for(i=0;i<*m;i++){
		printf("请输入矩阵第%d行的值:\n",i);
		for(j=0;j<*n;j++){
			scanf_s("%d",&(*a)[i][j]);
		}
	}
	getchar();
}
node*RowInsert(int*a,int n){
	int j;node*head,*p1,*p2;
	head=p1=(node*)malloc(sizeof(node));
	for(j=0;j<n;j++){
		p1->aij=a[j];
		p2=(node*)malloc(sizeof(node));
		if(j<n-1){
			p1->next=p2;
			p1=p2;
		}else if(j==n-1){
			p1->next=head;
		}
	}
	return head;
}

//如何使用数组指针对node指针进行指代？？
node**Link_Layer(int**a,int m,int n){
	node**head;int i;
	head=(node**)malloc(m*sizeof(node*));
	for(i=0;i<m;i++){
		*(head+i)=(node*)malloc(sizeof(node));
	}
	for(i=0;i<m;i++){
		head[i]=RowInsert(a[i],n);
	}
	return head;
}

void List(node**head,int m,int n){
	int i;node*p1,*p2;
	printf("矩阵a的链式存储:\n");
	for(i=0;i<m;i++){
		p1=head[i];p2=head[i];
		while(p1->next!=p2){
			printf("%d->",p1->aij);
			p1=p1->next;
		};
		printf("%d\n",p1->aij);
	}
	return ;
}

void freeMatrix(int***a,int m){
	int i;
	for(i=0;i<m;i++){
		free(*(*a+i));
	}
	free(*a);
}

void freeNode(node***head,int m){
	int i;
	for(i=0;i<m;i++){
		free(*((*head)+i));
	}
	free(*head);
}

int main(){
	int **a,m,n;node**head;char ch;
	while((ch=getchar())!='@'){
		input(&a,&m,&n);
		head=Link_Layer(a,m,n);
		List(head,m,n);
		freeMatrix(&a,m);
		freeNode(&head,m);
		printf("按任意键继续，按@结束程序\n");
	}
	return 0;
}
