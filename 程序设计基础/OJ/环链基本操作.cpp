void CreatCLLinkList(CLLinkList CL) 
{
    Node *rear,*s;
    rear=CL;//rear指针动态指向当前表尾，其初始值指向头结点 
    int flag=1;
    int x;
    printf("Please input data and enter 0 end:\n");
    while(flag)
    {
        scanf("%d",&x);
        if(x!=0)
        {
            s=(Node *)malloc(len);
            s->data=x;
            rear->next=s;
            rear=s;
        }
        else
        {
            flag=0;
            rear->next=CL;//最后一个节点的next域指向头结点 
        }
    }
}
//插入节点
void InCLLinkList(CLLinkList CL,int i,int x)
{
    Node *p,*s;
    int k=0;
    p=CL;
    if(i<=0)
    {
        printf("You enter location illegal:\n");
        return;
    }
    while(p->next!=CL&&k<i-1)
    {
        k++;
        p=p->next;
    }
    if(p==CL)
    {
        printf("The insert position is not reasonable:\n");
        return;
    }
    s=(Node *)malloc(len);
    s->data=x;
    s->next=p->next;
    p->next=s;
    printf("Insert successfully\n");
}
void DeleCLLinkList(LinkList CL,int i)
{
    Node *p,*r;
    p=CL;
    int k=0;
    if(i<0)
    {
        printf("You enput i illegal!\n");
        return;
    }
    while(p->next!=CL&&k<i-1)
    {
        p=p->next;
        k++;
    }
    if(p->next==CL)
    {
        printf("Delete Node i illegal!\n");
        return;
    }
    r=p->next;
    p->next=r->next;
    free(r);
}
//头指针法
CLLinkList MergeCLLinkList(CLLinkList CL_a,CLLinkList CL_b)
{
    Node *p,*q;
    p=CL_a;
    q=CL_b;
    while(p->next!=CL_a)//找到LA的表尾，用p指向它 
        p=p->next;
    while(q->next!=CL_b)//找到LB的表尾，用q指向它
        q=q->next;
    q->next=CL_a;//修改LB的表尾指针，使之指向表LA的头结点 
    p->next=CL_b->next;    //修改LA的表尾指针，CL_b->next的意思是跳过CL_b头结点
    free(CL_b);
    return CL_a;
}
//尾指针法
CLLinkList MergeCLLinkList(CLLinkList RA,CLLinkList RB)
{
    Node *p=RA->next;//保存RA的头结点地址 
    RA->next=RB->next->next;//RB的头结点练到RA的终端结点之后
    RB->next=p;//将RA的头结点链到RB的终端结点之后
    free(RB->next);//释放RB的头结点 
    return RB;//返回新的链表的尾指针 
}
//求长度
int LengthCLLinkList(LinkList CL)
{
    int i=0;
    Node *p;
    p=CL->next;
    while(p!=CL)
    {
        i++;
        p=p->next;
    }
    return i;
}