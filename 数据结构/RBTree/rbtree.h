
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "BinNode.h"

//�����
class RedBlackTree{
	BinNode* root;
	int _size;

protected:
	BinNode*& fromParentTo(BinNode* x){//�������ã���ָ֤���ǿ��޸ĵ�
		return (x == root) ? root : (x->isLChild() ? x->parent->leftChild : x->parent->rightChild);
	}
	BinNode* connect34(BinNode* a, BinNode* b, BinNode* c, BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3);
	BinNode* rotateAt(BinNode* v);
	void solveDoubleRed(BinNode* x);//˫������
	void solveDoubleBlack(BinNode* r, BinNode* hot);//˫������
	BinNode* searchIn(int data);//���ҽڵ�
	BinNode* removeAt(BinNode* x, BinNode*& hot);//ɾ��x��ͬʱ��x��ֱ�Ӻ�����

public:
	RedBlackTree():_size(0), root(NULL){}
	BinNode* getroot()const{ return root; }
	int size()const{ return _size; }
	BinNode* search(int data);//����
	BinNode* insert(int data);//����
	bool remove(int data);//ɾ��
	void traverseIn(BinNode* r);//���������������

};

#endif
