#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct node{
	char serial_num[20];
	node*next;
};
void PrintList(node*head,int n)//输出链表内容
{
	node*p1=head;//为了简便，这里用head代表线性链表的head和循环链表的rear
	printf("当前链表内容:\n");
	switch(n){//用1代表线性链表，用2代表循环链表
		case 1:
			while(p1!=NULL){
				printf("%s -> ",p1->serial_num);
				p1=p1->next;
			}
			break;
		case 2:
			while(p1->next!=head){
				p1=p1->next;
				printf("%s -> ",p1->serial_num);				
			}
			printf("%s -> ",p1->next->serial_num);
			break;
	}
	putchar(10);
}
node*LineInsert(node*head,node*p0)//线性链表插入
{
	node*p1,*p2;
	p1=p2=head;
	if(head==NULL){head=p0;p0->next=NULL;}
	else{
		//关键字递增有序，所以应该先比较高位数字，因此采用strcmp比较大小，注意：10<2
		while(strcmp(p0->serial_num,p1->serial_num)>0&&p1->next!=NULL){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->serial_num,p1->serial_num)<=0){
			if(p1==head){
				head=p0;
				p0->next=p1;
			}else{
				p2->next=p0;
				p0->next=p1;
			}
		}else{
			p1->next=p0;
			p0->next=NULL;
		}
	}
	return head;
}
//用尾指针创建链表是简便易行的，因为尾指针的下一个就是头节点，
//但是在循环输出链表数据的时候需要注意不是从尾指针进行输出，而是rear->next开始输出！！！
node*CircleInsert(node*rear,node*p0)//循环链表插入,返回尾指针
{
	node*p1,*p2;
	if(rear==NULL){rear=p0;p0->next=rear;}
	p1=p2=rear->next;
	if(rear!=NULL){
		while(strcmp(p0->serial_num,p1->serial_num)>0&&p1!=rear){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->serial_num,p1->serial_num)<=0){
			if(p1==rear->next){
				rear->next=p0;
				p0->next=p1;
			}else{
				p2->next=p0;
				p0->next=p1;
			}
		}else{
			p0->next=rear->next;
			p1->next=p0;
			rear=p0;
		}
	}
	return rear;
}
void create(node**rear,node**head2)
{
	node*p1,*p2;
	int n1,n2,i;
	p1=*rear;p2=*head2;
	printf("please input number of elements of aList:");
	scanf_s("%d",&n1);
	printf("please input the elements of aList:\n");
	for(i=0;i<n1;i++){//创建环形链表
		p1=(node*)malloc(sizeof(node));
		scanf_s("%s",p1->serial_num,20);
		*rear=CircleInsert(*rear,p1);
		PrintList(*rear,2);
		fflush(stdin);
	}
	printf("\nplease input number of elements of bList:");
	scanf_s("%d",&n2);
	printf("please input the elements of sList:\n");
	for(i=0;i<n2;i++){//创建线性链表
		p2=(node*)malloc(sizeof(node));
		scanf_s("%s",p2->serial_num,20);
		*head2=LineInsert(*head2,p2);
		PrintList(*head2,1);
		fflush(stdin);
	}
}
node*combin(node*rear,node*head2)
{
	node*head;
	head=rear->next;
	rear->next=head2;
	return head;
}
void SaveList(node*head,int n,char**fname1)//将链表的数据输入到硬盘文件
{
	FILE*fp1;
	node*p1;
	p1=head;//同样为了简便，这里用head既代表顺序链表的head又用rear代表循环链表的rear
	printf("\n请输入新建.txt文件名：");
	scanf_s("%s",*fname1,20);
	if((fp1=fopen(*fname1,"w+"))==NULL){
		printf("cannot open file %s\n",*fname1);
		return;
	}
	switch(n){
		case 2:
			do{
				p1=p1->next;
				if((fwrite(p1,20*sizeof(char),1,fp1)!=1))//仅仅存入数据，不存入指针
					printf("file1 write error!\n");
			}while(p1!=head);
			break;
		case 1:
			do{
				if((fwrite(p1,20*sizeof(char),1,fp1))!=1)
					printf("file2 write error!\n");
				p1=p1->next;
			}while(p1!=NULL);
			break;
	}
	fclose(fp1);
}
void LoadList(char**fname_p)//从硬盘文件读入链表
{
	int n,i;node tmp[20];
	char fname[20];FILE*fp;
	printf("\n请输入要打开的.txt文件名:\n");
	scanf_s("%s",fname,20);
	if(strcmp(fname,*fname_p)==0||strcmp(fname,*(fname_p+2))==0)n=2;
	else if(strcmp(fname,*(fname_p+1))==0)n=1;
	else {printf("error!\n");return ;}
	if((fp=fopen(fname,"r"))==NULL){
		printf("cannot open file!\n");
		return ;
	}
	//指针在写入文件之后，在程序结束之后，硬盘文件依然保存了指针的信息，但是在文件结束之后，内存中的指针指向的数据会消失
	//因此在新打开程序之后，所有内存信息是新开辟的，这时再读入硬盘里的指针，就会使得指针指向区域没有数据信息
	//因此，尽量避免向文件中输入指针或者从文件中读入指针信息
	printf("当前链表内容:\n");
	switch(n){
	case 1:
		i=0;
		rewind(fp);
		while(!feof(fp)){
			fread(&tmp[i].serial_num,20*sizeof(char),1,fp);//这里仅仅读取了结构体成员中的数组，如何读取指针信息并存入一条链表呢？
			if(feof(fp))break;
			printf("%s -> ",tmp[i].serial_num);
			i++;
		};
		break;
	case 2:
		i=0;
		rewind(fp);
		while(!feof(fp)){
			fread(&tmp[i].serial_num,20*sizeof(char),1,fp);
			if(feof(fp))break;
			printf("%s -> ",tmp[i].serial_num);
			i++;
		};
		break;
	}
	fclose(fp);
	return;
}
int main()
{
	node*head1,*head2;
	char fname[3][20];
	char*fname_p[3]={fname[0],fname[1],fname[2]};
	head1=NULL;head2=NULL;
	create(&head1,&head2);
	//create函数返回之后形参消失了，所以当子函数可能对头结点进行修改的时候，应该传头结点的地址
	SaveList(head1,2,&fname_p[0]);
	SaveList(head2,1,&fname_p[1]);
	LoadList(fname_p);
	LoadList(fname_p);//读入内存并输出到屏幕
	head1=combin(head1,head2);
	SaveList(head1,1,&fname_p[2]);
	printf("合并后的新链表:\n");
	PrintList(head1,1);
	return 0;
}
