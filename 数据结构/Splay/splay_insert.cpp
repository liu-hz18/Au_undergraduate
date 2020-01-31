
#include "SplayTree.h"

BinNode* SplayTree::insert(int data){//插入
	if(!root){
		_size++;
		return root = new BinNode(data);
	}
	if(data == search(data)->weight)return root;//确认目标节点不存在
	_size++;
	BinNode* t = root;
	if(root->weight < data){//插入新根，以t和t->rc为左、右孩子
		t->parent = root = new BinNode(data);
		root->leftChild = t;
		root->rightChild = t->rightChild;
		if(t->hasRChild()){
			t->rightChild->parent = root;
			t->rightChild = NULL;
		}
	}else{//插入新根，以t->lc和t为左、右孩子
		t->parent = root = new BinNode(data);
		root->leftChild = t->leftChild;
		root->rightChild = t;
		if(t->hasLChild()){
			t->leftChild->parent = root;
			t->leftChild = NULL;
		}
	}
	//更新根节点和原来根节点的高度
	updateHeightAbove(t);
	return root;
}
