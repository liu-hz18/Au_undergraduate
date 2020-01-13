#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct tree{
	char val;
	int pre;
	tree *fa;
	tree *le;
	tree *ri;
};
tree *init();
tree *insert(tree *,char *);
double calc(tree *,double);
int main(){
	char poly[105];
	double x;
	scanf("%s",poly);
	int end=strlen(poly);
	tree *head=init();
	head=insert(head,poly);
	scanf("%lf",&x);
	double value=calc(head,x);
	double deri=(calc(head,(x+0.000001))-calc(head,x))/0.000001;
	printf("%lf %lf",value,deri);
	return 0;
}
double calc(tree *h,double x){
	if(h->val=='x')return x;
	if(h->val=='0')return 0;
	double le=calc(h->le,x);
	double ri=calc(h->ri,x);
	switch(h->val){
		case '+':return le+ri;
		case '-':return le-ri;
		case '*':return le*ri;
		case '/':return le/ri;
	}
	return 0;
}
tree *insert(tree *h,char *s){
	int ket=0;
	int end=strlen(s);
	tree *now=init();
	h->ri=now;now->fa=h;
	for(int i=0;i<end;i++){
		if(*(s+i)=='x'){
			now->val='x';now->pre=999999;
		}
		if(*(s+i)=='+'||*(s+i)=='-'||*(s+i)=='*'||*(s+i)=='/'){
			if(now->val!='x'){now->val='0';now->pre=999999;}
			tree *tmp=init();
			tmp->val=*(s+i);
			if(*(s+i)=='+'||*(s+i)=='-')tmp->pre=ket+1;
			else tmp->pre=ket+2;
			while(tmp->pre<=now->pre)now=now->fa;
			tmp->le=now->ri;
			tmp->fa=now;
			now->ri=tmp;
			tree *right=init();
			tmp->ri=right;right->fa=tmp;
			now=right;
		}
		if(*(s+i)=='(')ket+=2;
		if(*(s+i)==')')ket-=2;
	}
	return h->ri;
}
tree *init(){
	tree *p;
	p=(tree *)malloc(sizeof(tree));
	if(!p){printf("ERROR");exit(-1);}
	p->fa=NULL;p->le=NULL;p->ri=NULL;p->pre=0;
	return p;
}