
#include "rbtree.h"

//ɾ��x��ͬʱ��x��ֱ�Ӻ�����
BinNode* RedBlackTree::removeAt(BinNode* x, BinNode*& hot){
	BinNode* w = x;//�����ϱ�ɾ���Ľڵ�
	BinNode* succ = NULL;
	if(!x->hasLChild()){
		succ = x->rightChild;
		if(x->isLChild())x->parent->leftChild = succ;//����
		else if(x->isRChild())x->parent->rightChild = succ;//�Һ���
		else root = succ;//x�Ǹ�
	}else if(!x->hasRChild()){
		succ = x->leftChild;
		if(x->isLChild())x->parent->leftChild = succ;
		else if(x->isRChild())x->parent->rightChild = succ;
		else root = succ;
	}else{//���Һ��Ӷ���
		w = w->succ();
		swap(x->weight, w->weight);
		BinNode* u = w->parent;//u�����ӻ��Һ��ӻ�ı�
		(u == x ? u->rightChild : u->leftChild) = succ = w->rightChild;//����ڵ�w
	}
	BinNode* wparent = w->parent;//��¼�������㷵��
	if(succ)succ->parent = w->parent;
	hot = wparent;
	delete w;
	return succ;//���ؽ�����
}

bool RedBlackTree::remove(int data){
	BinNode* x = searchIn(data), *hot;
	if(!x || x->weight != data)return false;
	BinNode* r = removeAt(x, hot);
	if(!(--_size))return true;
	//hotĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ����
	if(!hot){
		root->color = BLACK;
		root->updateHeight();
		return true;
	}
	//���£�ԭx����r���طǸ���_hot�طǿ�
	if(hot->blackHeightUpdated())return true;//���������ȵĺ������Ȼƽ�⣬���������
	if(r && r->isRed()){//������rΪ�죬��ֻ������ת��
		r->color = BLACK; r->height ++; return true;
	}//���£�ԭx����r����Ϊ��ɫ
	solveDoubleBlack(r, hot);//��˫�ڵ����󷵻�
	return true;
}
