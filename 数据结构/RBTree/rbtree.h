
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "BinNode.h"

//红黑树
class RedBlackTree{
	BinNode* root;
	int _size;

protected:
	BinNode*& fromParentTo(BinNode* x){//返回引用，保证指针是可修改的
		return (x == root) ? root : (x->isLChild() ? x->parent->leftChild : x->parent->rightChild);
	}
	BinNode* connect34(BinNode* a, BinNode* b, BinNode* c, BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3);
	BinNode* rotateAt(BinNode* v);
	void solveDoubleRed(BinNode* x);//双红修正
	void solveDoubleBlack(BinNode* r, BinNode* hot);//双黑修正
	BinNode* searchIn(int data);//查找节点
	BinNode* removeAt(BinNode* x, BinNode*& hot);//删除x，同时用x的直接后继替代

public:
	RedBlackTree():_size(0), root(NULL){}
	BinNode* getroot()const{ return root; }
	int size()const{ return _size; }
	BinNode* search(int data);//查找
	BinNode* insert(int data);//插入
	bool remove(int data);//删除
	void traverseIn(BinNode* r);//中序遍历，调试用

};

#endif
