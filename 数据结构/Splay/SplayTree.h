
#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

#include "BinNode.h"

//��չ��
class SplayTree{
	BinNode* root;
	int _size;//�ڵ����
	//����tarjian˫����չ����
	BinNode* splay(BinNode* v);
	//���ı�ṹ������λ��
	BinNode* searchIn(int data);
	//��·���ϸ������ȸ߶�
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
	BinNode* search(int data);//����
	BinNode* insert(int data);//����
	bool remove(int data);//ɾ��
	
};

#endif
