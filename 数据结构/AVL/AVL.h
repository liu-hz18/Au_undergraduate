
#ifndef _AVL_H_
#define _AVL_H_

#include "BinNode.h"

class AVLTree{
	BinNode* root;
	int _size;

protected:
	BinNode*& fromParentTo(BinNode* x){//返回引用，保证指针是可修改的
		return (x == root) ? root : (x->isLChild() ? x->parent->leftChild : x->parent->rightChild);
	}
	BinNode* searchIn(int data);//不改变结构，查找位置
	BinNode* connect34(BinNode* a, BinNode* b, BinNode* c, BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3);
	BinNode* rotateAt(BinNode* v);
	BinNode* removeAt(BinNode* x);//删除x，同时用x的直接后继替代

public:
	AVLTree():_size(0), root(NULL){}
	AVLTree(BinNode* r):_size(1), root(r){
		root->leftChild = root->rightChild = NULL;
		root->parent = NULL;
	}
	BinNode* getroot()const{
		return root;
	}
	int size()const{
		return _size;
	}
	void traverseIn(BinNode* r);
	BinNode* search(int data);
	BinNode* insert(int data);
	bool remove(int data);
	
};

#endif
