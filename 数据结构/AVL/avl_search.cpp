
#include "AVL.h"

//不改变结构，查找位置
BinNode* AVLTree::searchIn(int data){
	BinNode* v = root, *hot;
	if(!root || v->weight == data)return v;
	hot = v;
	while(true){
		BinNode* c = (data < hot->weight) ? hot->leftChild : hot->rightChild;
		if(!c)return hot;//确保返回值不为空
		else if(c->weight == data)return c;
		hot = c;
	}//hot始终指向最后一个失败节点
	return hot;
}

BinNode* AVLTree::search(int data){
	return searchIn(data);
}