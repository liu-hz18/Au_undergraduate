#include <stdio.h>
#include<time.h>
#include <stdlib.h>
typedef struct node{
    int value;
    struct node *next;
}LinkNode,*Linklist;

/// ��������(�����ȣ����ڵ���ʼλ��)
struct node *create()
{
	int n = 0;
	struct node *p1, *p2, *head;
	int i;
	int randomIndex ;
    head=NULL;
	p1=NULL;
	p2=NULL;
	srand((unsigned)time(NULL));
	while(n==0)//�����ĳ������
		n=((int)rand())%50;
	for(i=0;i<n;i++)
	{
		p1=(struct node*)malloc(sizeof(struct node));
		p1->next = NULL;
		p1->value = ((int)rand());//ÿ�ڵ��������
		if(i == 0)
			head = p1;
		else
			p2->next = p1;
		p2=p1;
	}
	//��ʱp1������β�ڵ����Ϣ
    if (head!=NULL)//������Ϊ��ʱ������ɻ�
	{
		randomIndex =((int)rand())%n; //����ɻ��Ľڵ�
		p2=head;
		for(i=0; i<randomIndex; i++)
			p2 = p2->next;//�ҵ��ɻ��Ľڵ�
		p1->next = p2;
	}
	return head;
}

///�ж������Ƿ��л�
LinkNode* judgeRing(Linklist list){
    LinkNode *fast = list;
    LinkNode *slow = list;

    if(list == NULL)
        return NULL;

    while(true){
        if(slow->next != NULL && fast->next != NULL && fast->next->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        else
            return NULL;

        if(fast == slow)
            return fast;
    }
}

///��ȡ������
int getRingLength(LinkNode *ringMeetNode){
    int RingLength=0;
    LinkNode *fast = ringMeetNode;
    LinkNode *slow = ringMeetNode;
    for(;;){
        fast = fast->next->next;
        slow = slow->next;
        RingLength++;
        if(fast == slow)
            break;
    }
    return RingLength;
}

///��ȡ����ͷ�������ӵ�ĳ���
int getLenA(Linklist list,LinkNode *ringMeetNode){
    int lenA=0;
    LinkNode *fast = list;
    LinkNode *slow = ringMeetNode;
    for(;;){
        fast = fast->next;
        slow = slow->next;
        lenA++;
        if(fast == slow)
            break;
    }
    return lenA;
}

///����ʼ��
///����л�, �ͷſտռ�ʱ��Ҫע��. 
LinkNode* RingStart(Linklist list, int lenA){
    if (!list || lenA <= 0){
        return NULL;
    }

    int i = 0;
    LinkNode* tmp = list;
    for ( ; i < lenA; ++i){
        if (tmp != NULL){
            tmp = tmp->next;
        }
    }

    return (i == lenA)? tmp : NULL;
}

///�ͷſռ�
int freeMalloc(Linklist list, LinkNode* ringstart){
    bool is_ringstart_free = false; //����ʼ��ֻ�ܱ��ͷſռ�һ��
    LinkNode *nextnode = NULL;

    while(list != NULL){
        nextnode = list->next;
        if (list == ringstart){ //����ǻ���ʼ��
            if (is_ringstart_free)
                break;  //����ڶ�����������ʼ��addr, ��ʾ�Ѿ��ͷ����
            else
                is_ringstart_free = true;   //��¼�Ѿ��ͷ�һ��
        }
        free(list);
        list = nextnode;
    }

    return 0;
}

int main(){
    Linklist list = NULL;
    LinkNode *ringMeetNode  = NULL;
    LinkNode *ringStartNode = NULL;

    int LenA       = 0;
    int RingLength = 0;

    list = create();
    ringMeetNode = judgeRing(list); //����ָ��������

    if(ringMeetNode == NULL)
        printf("No Ring\n");
    else{
        printf("Have Ring\n");
        RingLength = getRingLength(ringMeetNode);   //����
        LenA = getLenA(list,ringMeetNode);

        printf("RingLength:%d\n", RingLength);
        printf("LenA:%d\n", LenA);
        printf("listLength=%d\n", RingLength+LenA);
    }

    ringStartNode = RingStart(list, LenA);  //��ȡ����ʼ��
    freeMalloc(list, ringStartNode);    //�ͷŻ��ڵ�, �л�ʱ��Ҫע��
    return 0;
}
