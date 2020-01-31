
#include "AVL.h"

//ɾ��x��ͬʱ��x��ֱ�Ӻ�����
BinNode* AVLTree::removeAt(BinNode* x){
	BinNode* w = x;//�����ϱ�ɾ���Ľڵ�
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
		BinNode* u = w->parent;//u�����ӻ��Һ��ӻ�ı�
		(u == x ? u->rightChild : u->leftChild) = succ = w->rightChild;//����ڵ�w
	}
	BinNode* wparent = w->parent;//��¼�������㷵��
	if(succ)succ->parent = w->parent;
	delete w;
	return wparent;//����hot�ڵ�
}

bool AVLTree::remove(int data){
	BinNode* x = searchIn(data);
	if(!x || x->weight != data)return false;
	BinNode* hot = removeAt(x);//���������ϱ�ɾ���ĵ�ĸ���
	_size --;
	for(BinNode* g = hot; g; g = g->parent){
		if(!g->avlBalanced()){
			BinNode*& gg = fromParentTo(g);
			g = gg = rotateAt(g->tallerChild()->tallerChild());
		}
		g->updateHeight();
	}//��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
	return true;
}//��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false