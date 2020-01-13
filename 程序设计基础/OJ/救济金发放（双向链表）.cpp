//救济金发放，双向链表
#include<stdio.h> 
#include<malloc.h>
typedef struct node {
    int id;
    struct node *pre,*next;
}pesNode;
void Insert(pesNode *first, pesNode *s)
{
    pesNode *p = first;
    while(p->next != first) p = p->next;
    s->next = p->next;
    p->next->pre = s;
    p->next = s;
    s->pre = p;
}
void Delete(pesNode *p)
{
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete p;
}
int main()
{
    int n,k,m;
    while(scanf_s("%d%d%d", &n, &k, &m) && n!=0&&k!=0&&m!=0) {//输入到0为止
        pesNode *first = (pesNode*)malloc(sizeof(pesNode));
        first->id = 0;
        first->next = first; first->pre = first;
        for(int i=1; i<=n; i++){
			pesNode *s = (pesNode*)malloc(sizeof(pesNode));
            s->id = i;
            Insert(first, s);
        }
        pesNode *p,*q;
        p = first; q = first;
        int tot = n;
        while(tot) {
            int i=0;
            while(i!=k) {if(p->next != first){p=p->next;i++;}else p=p->next;}
            int j=0;
            while(j != m) {if(q->pre != first){q=q->pre;j++;}else q=q->pre;}
            pesNode *tempP = p;
            pesNode *tempQ = q;
            if(p->pre==q){p=p->pre->pre;q = q->next->next;}
            else{p=p->pre;q = q->next;}
            if(tempP->id == tempQ->id) {
                if(tempP->next == first&&tempP->pre == first) { printf("%d\n", tempP->id);break; }
                else printf("%d,",tempP->id);
                tot--;
            }
            else {
                if(tempP->pre==first && tempQ->next == first && tempP->next == tempQ|| 
                    tempP->next==first && tempQ->pre==first && tempQ->next == tempP)
                    {printf("%d %d\n", tempP->id, tempQ->id); break; }
                else printf("%d %d,", tempP->id, tempQ->id);
                tot -= 2;
            }
            if(tempP!=tempQ) {Delete(tempP);Delete(tempQ);}
            else Delete(tempP);
        }
    }
}
