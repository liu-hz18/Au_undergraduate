
#include "rbtree.h"

/******************************************************************************************
* 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
* 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
* 可用于AVL和RedBlack的局部平衡调整
******************************************************************************************/
BinNode* RedBlackTree::connect34(BinNode* a, BinNode* b, BinNode* c, \
						  BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3){
	a->leftChild = T0; if(T0)T0->parent = a;
	a->rightChild = T1; if(T1)T1->parent = a;
	a->updateHeight();
	c->leftChild = T2; if(T2)T2->parent = c;
	c->rightChild = T3; if(T3)T3->parent = c;
	c->updateHeight();
	b->leftChild = a; a->parent = b;
	b->rightChild = c; c->parent = b;
	b->updateHeight();
	return b;
}