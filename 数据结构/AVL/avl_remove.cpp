
#include "AVL.h"

//删除x，同时用x的直接后继替代
BinNode* AVLTree::removeAt(BinNode* x){
	BinNode* w = x;//物理上被删除的节点
	BinNode* succ = NULL;
	if(!x->hasLChild()){
		succ = x->rightChild;
		if(x->isLChild())x->parent->leftChild = succ;
		else if(x->isRChild())x->parent->rightChild = succ;
	}else if(!x->hasRChild()){
		succ = x->leftChild;
		if(x->isLChild())x->parent->leftChild = succ;
		else if(x->isRChild())x->parent->rightChild = succ;
	}else{
		w = w->succ();
		swap(x->weight, w->weight);
		BinNode* u = w->parent;//u的左孩子或右孩子会改变
		(u == x ? u->rightChild : u->leftChild) = succ = w->rightChild;//隔离节点w
	}
	BinNode* wparent = w->parent;//记录副本方便返回
	if(succ)succ->parent = w->parent;
	delete w;
	return wparent;//返回hot节点
}

bool AVLTree::remove(int data){
	BinNode* x = searchIn(data);
	if(!x || x->weight != data)return false;
	BinNode* hot = removeAt(x);//返回物理上被删除的点的父亲
	_size --;
	for(BinNode* g = hot; g; g = g->parent){
		if(!g->avlBalanced()){
			BinNode*& gg = fromParentTo(g);
			g = gg = rotateAt(g->tallerChild()->tallerChild());
		}
		g->updateHeight();
	}//可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
	return true;
}//若目标节点存在且被删除，返回true；否则返回false