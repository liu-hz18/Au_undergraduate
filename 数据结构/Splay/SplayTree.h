
#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

#include "BinNode.h"

//伸展树
class SplayTree{
	BinNode* root;
	int _size;//节点个数
	//采用tarjian双层伸展策略
	BinNode* splay(BinNode* v);
	//不改变结构，查找位置
	BinNode* searchIn(int data);
	//沿路向上更新祖先高度
	void updateHeightAbove(BinNode* v);

public:
	SplayTree():_size(0), root(NULL){}
	SplayTree(BinNode* r):_size(1), root(r){
		root->leftChild = root->rightChild = NULL;
		root->parent = NULL;
	}
	~SplayTree(){
		if(root)release(root);
	}
	void release(BinNode* r){
		if(r->rightChild)release(r->rightChild);
		if(r->leftChild)release(r->leftChild);
		delete r;
	}
	int size()const{ return _size; }
	BinNode* getroot()const{ return root; }
	BinNode* search(int data);//查找
	BinNode* insert(int data);//插入
	bool remove(int data);//删除
	
};

#endif
