
#include "rbtree.h"

BinNode* RedBlackTree::insert(int data){
	if(!_size){//空树，则插入为树根
		_size++;
		root = new BinNode(data);
		root->color = BLACK;
		return root;
	}
	BinNode* hot = searchIn(data);
	if(hot->weight == data)return hot;//保证树中没有此值
	BinNode* x = new BinNode(data);
	x->parent = hot; x->height = -1; _size++;
	if(data < hot->weight)hot->leftChild = x;
	else hot->rightChild = x;
	BinNode* xOld = x;
	solveDoubleRed(x);
	return xOld;
}
