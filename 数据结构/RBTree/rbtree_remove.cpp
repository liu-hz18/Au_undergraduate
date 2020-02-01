
#include "rbtree.h"

//删除x，同时用x的直接后继替代
BinNode* RedBlackTree::removeAt(BinNode* x, BinNode*& hot){
	BinNode* w = x;//物理上被删除的节点
	BinNode* succ = NULL;
	if(!x->hasLChild()){
		succ = x->rightChild;
		if(x->isLChild())x->parent->leftChild = succ;//左孩子
		else if(x->isRChild())x->parent->rightChild = succ;//右孩子
		else root = succ;//x是根
	}else if(!x->hasRChild()){
		succ = x->leftChild;
		if(x->isLChild())x->parent->leftChild = succ;
		else if(x->isRChild())x->parent->rightChild = succ;
		else root = succ;
	}else{//左右孩子都有
		w = w->succ();
		swap(x->weight, w->weight);
		BinNode* u = w->parent;//u的左孩子或右孩子会改变
		(u == x ? u->rightChild : u->leftChild) = succ = w->rightChild;//隔离节点w
	}
	BinNode* wparent = w->parent;//记录副本方便返回
	if(succ)succ->parent = w->parent;
	hot = wparent;
	delete w;
	return succ;//返回接替者
}

bool RedBlackTree::remove(int data){
	BinNode* x = searchIn(data), *hot;
	if(!x || x->weight != data)return false;
	BinNode* r = removeAt(x, hot);
	if(!(--_size))return true;
	//hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
	if(!hot){
		root->color = BLACK;
		root->updateHeight();
		return true;
	}
	//以下，原x（现r）必非根，_hot必非空
	if(hot->blackHeightUpdated())return true;//若所有祖先的黑深度依然平衡，则无需调整
	if(r && r->isRed()){//否则，若r为红，则只需令其转黑
		r->color = BLACK; r->height ++; return true;
	}//以下，原x（现r）均为黑色
	solveDoubleBlack(r, hot);//经双黑调整后返回
	return true;
}
