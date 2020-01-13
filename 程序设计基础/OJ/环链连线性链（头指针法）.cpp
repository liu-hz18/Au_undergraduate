#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct node{
	char serial_num[20];
	node*next;
};
void PrintList(node*head,int n)//输出链表内容
{
	node*p1=head;
	printf("当前链表内容:\n");
	switch(n){//用1代表线性链表，用2代表循环链表
		case 1:
			while(p1!=NULL){
				printf("%s -> ",p1->serial_num);
				p1=p1->next;
			}
			break;
		case 2:
			printf("%s -> ",p1->serial_num);
			while(p1->next!=head){
				p1=p1->next;
				printf("%s -> ",p1->serial_num);				
			}
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
node*CircleInsert(node*head,node*p0)//环形链表插入
{
	node*p1,*p2,*p3;
	p1=p2=head;
	if(head==NULL){head=p0;p0->next=head;}
	else{
		while(p1->next!=head&&head!=NULL){p1=p1->next;}
		p3=p1;p1=head;
		while(strcmp(p0->serial_num,p1->serial_num)>0&&p1->next!=head){
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p0->serial_num,p1->serial_num)<=0){
			if(p1==head){
				head=p0;
				p0->next=p1;
				p3->next=head;
			}else{
				p2->next=p0;
				p0->next=p1;
			}
		}else{
			p1->next=p0;
			p0->next=head;
		}
	}
	return head;
}
void create(node**head1,node**head2)
{
	node*p1,*p2;
	int n1,n2,i;
	p1=*head1;p2=*head2;
	printf("please input number of elements of aList:");
	scanf_s("%d",&n1);
	printf("please input the elements of aList:\n");
	for(i=0;i<n1;i++){
		p1=(node*)malloc(sizeof(node));
		scanf_s("%s",p1->serial_num,20);
		*head1=CircleInsert(*head1,p1);
		PrintList(*head1,2);
		fflush(stdin);
	}
	printf("\nplease input number of elements of bList:");
	scanf_s("%d",&n2);
	printf("please input the elements of sList:\n");
	for(i=0;i<n2;i++){
		p2=(node*)malloc(sizeof(node));
		scanf_s("%s",p2->serial_num,20);
		*head2=LineInsert(*head2,p2);
		PrintList(*head2,1);
		fflush(stdin);
	}
}
node*combin(node*head1,node*head2)
{
	node*p1;
	p1=head1;
	while(p1->next!=head1){
		p1=p1->next;
	}
	p1->next=head2;
	return head1;
}
void SaveList(node*head,int n,char**fname1)//将链表的数据输入到硬盘文件
{
	FILE*fp1;
	node*p1;
	p1=head;
	printf("\n请输入新建.txt文件名：");
	scanf_s("%s",*fname1,20);
	if((fp1=fopen(*fname1,"w+"))==NULL){
		printf("cannot open file %s\n",*fname1);
		return;
	}
	switch(n){
		case 2:
			do{
				if((fwrite(p1,20*sizeof(char),1,fp1)!=1))//仅仅存入数据，不存入指针
					printf("file1 write error!\n");
				p1=p1->next;
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
