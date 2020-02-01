
#include "rbtree.h"

//双红修正
/******************************************************************************************
* RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
*    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
******************************************************************************************/
void RedBlackTree::solveDoubleRed(BinNode* x){
	if(x == root){//若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
		root->color = BLACK;
		root->height++;
		return;
	}
	BinNode* p = x->parent;//否则，x的父亲p必存在
	if(p->isBlack())return;//若p为黑，则可终止调整。否则
	BinNode* g = p->parent;//既然p为红，则x的祖父必存在，且必为黑色
	BinNode* u = (p == g->leftChild) ? g->rightChild : g->leftChild;//uncle(x)视x叔父u的颜色分别处理
	if(!u)return;
	if(u->isBlack()){
		if(x->isLChild() == p->isLChild())p->color = BLACK;//若x与p同侧（即zIg-zIg或zAg-zAg),p由红转黑，x保持红
		else x->color = BLACK;//若x与p异侧（即zIg-zAg或zAg-zIg）,x由红转黑，p保持红
		g->color = RED;//g必定由黑转红
		//以上虽保证总共两次染色，但因增加了判断而得不偿失,在旋转后将根置黑、孩子置红，虽需三次染色但效率更高	
		BinNode* gg = g->parent;//曾祖父
		BinNode*& temp = fromParentTo(g);//调整后的子树根节点
		BinNode* r = temp = rotateAt(x);//与原曾祖父联接
		r->parent = gg;
	}else{//若u为红色
		p->color = BLACK;//p由红转黑
		p->height++;
		u->color = BLACK;//u由红转黑
		u->height++;
		if(g != root)g->color = RED;//u由红转黑
		solveDoubleRed(g);//继续调整g（类似于尾递归，可优化为迭代形式）
	}
}
