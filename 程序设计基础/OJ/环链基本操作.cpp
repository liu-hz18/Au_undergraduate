void CreatCLLinkList(CLLinkList CL) 
{
    Node *rear,*s;
    rear=CL;//rearָ�붯ָ̬��ǰ��β�����ʼֵָ��ͷ��� 
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
            rear->next=CL;//���һ���ڵ��next��ָ��ͷ��� 
        }
    }
}
//����ڵ�
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
//ͷָ�뷨
CLLinkList MergeCLLinkList(CLLinkList CL_a,CLLinkList CL_b)
{
    Node *p,*q;
    p=CL_a;
    q=CL_b;
    while(p->next!=CL_a)//�ҵ�LA�ı�β����pָ���� 
        p=p->next;
    while(q->next!=CL_b)//�ҵ�LB�ı�β����qָ����
        q=q->next;
    q->next=CL_a;//�޸�LB�ı�βָ�룬ʹָ֮���LA��ͷ��� 
    p->next=CL_b->next;    //�޸�LA�ı�βָ�룬CL_b->next����˼������CL_bͷ���
    free(CL_b);
    return CL_a;
}
//βָ�뷨
CLLinkList MergeCLLinkList(CLLinkList RA,CLLinkList RB)
{
    Node *p=RA->next;//����RA��ͷ����ַ 
    RA->next=RB->next->next;//RB��ͷ�������RA���ն˽��֮��
    RB->next=p;//��RA��ͷ�������RB���ն˽��֮��
    free(RB->next);//�ͷ�RB��ͷ��� 
    return RB;//�����µ������βָ�� 
}
//�󳤶�
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