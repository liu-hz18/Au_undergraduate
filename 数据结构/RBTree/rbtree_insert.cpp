
#include "rbtree.h"

BinNode* RedBlackTree::insert(int data){
	if(!_size){//�����������Ϊ����
		_size++;
		root = new BinNode(data);
		root->color = BLACK;
		return root;
	}
	BinNode* hot = searchIn(data);
	if(hot->weight == data)return hot;//��֤����û�д�ֵ
	BinNode* x = new BinNode(data);
	x->parent = hot; x->height = -1; _size++;
	if(data < hot->weight)hot->leftChild = x;
	else hot->rightChild = x;
	BinNode* xOld = x;
	solveDoubleRed(x);
	return xOld;
}
