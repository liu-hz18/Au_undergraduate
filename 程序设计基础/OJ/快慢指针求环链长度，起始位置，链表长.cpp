#include <stdio.h>
#include<time.h>
#include <stdlib.h>
typedef struct node{
    int value;
    struct node *next;
}LinkNode,*Linklist;

/// 创建链表(链表长度，环节点起始位置)
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
	while(n==0)//环链的长度随机
		n=((int)rand())%50;
	for(i=0;i<n;i++)
	{
		p1=(struct node*)malloc(sizeof(struct node));
		p1->next = NULL;
		p1->value = ((int)rand());//每节点内容随机
		if(i == 0)
			head = p1;
		else
			p2->next = p1;
		p2=p1;
	}
	//此时p1保留了尾节点的信息
    if (head!=NULL)//当链表不为空时，随机成环
	{
		randomIndex =((int)rand())%n; //随机成环的节点
		p2=head;
		for(i=0; i<randomIndex; i++)
			p2 = p2->next;//找到成环的节点
		p1->next = p2;
	}
	return head;
}

///判断链表是否有环
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

///获取链表环长
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

///获取链表头到环连接点的长度
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

///环起始点
///如果有环, 释放空空间时需要注意. 
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

///释放空间
int freeMalloc(Linklist list, LinkNode* ringstart){
    bool is_ringstart_free = false; //环起始点只能被释放空间一次
    LinkNode *nextnode = NULL;

    while(list != NULL){
        nextnode = list->next;
        if (list == ringstart){ //如果是环起始点
            if (is_ringstart_free)
                break;  //如果第二次遇到环起始点addr, 表示已经释放完成
            else
                is_ringstart_free = true;   //记录已经释放一次
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
    ringMeetNode = judgeRing(list); //快慢指针相遇点

    if(ringMeetNode == NULL)
        printf("No Ring\n");
    else{
        printf("Have Ring\n");
        RingLength = getRingLength(ringMeetNode);   //环长
        LenA = getLenA(list,ringMeetNode);

        printf("RingLength:%d\n", RingLength);
        printf("LenA:%d\n", LenA);
        printf("listLength=%d\n", RingLength+LenA);
    }

    ringStartNode = RingStart(list, LenA);  //获取环起始点
    freeMalloc(list, ringStartNode);    //释放环节点, 有环时需要注意
    return 0;
}
