
#ifndef _BINNODE_H_
#define _BINNODE_H_

#include "util.h"

//���������
struct BinNode{
	int weight;//��Ȩֵ
	int height;//�߶�
	BinNode* parent;
	BinNode* leftChild;
	BinNode* rightChild;
	int color;

	BinNode():height(0), parent(NULL), leftChild(NULL), rightChild(NULL), color(RED){}
	BinNode(int w):weight(w), height(0), parent(NULL), leftChild(NULL), rightChild(NULL), color(RED){}
	BinNode* insertAsLeft(BinNode* child){
		leftChild = child;
		if(leftChild)leftChild->parent = this;
		height = 1 + max(leftHeight(), rightHeight());
		return leftChild;
	}
	BinNode* insertAsRight(BinNode* child){
		rightChild = child;
		if(rightChild)rightChild->parent = this;
		height = 1 + max(leftHeight(), rightHeight());
		return rightChild;
	}
	bool hasLChild()const{
		return leftChild != NULL;
	}
	bool hasRChild()const{
		return rightChild != NULL;
	}
	bool isLChild()const{
		if(parent && parent->leftChild == this)return true;
		return false;
	}
	bool isRChild()const{
		if(parent && parent->rightChild == this)return true;
		return false;
	}
	int leftHeight()const{
		return leftChild ? leftChild->height : -1;
	}
	int rightHeight()const{
		return rightChild ? rightChild->height : -1;
	}
	void updateHeight(){//ֻ���ºڸ߶�
		height = max(leftHeight(), rightHeight());//����һ��ڸ߶���ȣ����ǳ���˫��
		if(isBlack())height++;//����ǰ�ڵ�Ϊ�ڣ����������
	}//��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�
	bool blackHeightUpdated(){
		return leftHeight() == rightHeight() && height == (isBlack() ? (leftHeight() + 1) : leftHeight());
	}
	bool isBlack()const{ return color == BLACK; }
	bool isRed()const{ return color == RED; }
	//�ݹ�õ�size,O(size)
	int size()const{
		int s = 1;
		if(leftChild)s += leftChild->size();
		if(rightChild)s += rightChild->size();
		return s;
	}
	bool avlBalanced(){//AVL�Ƿ�ƽ��
		return -2 < balanceFactor() && balanceFactor() < 2;
	}
	//ƽ������
	int balanceFactor(){
		return leftHeight() - rightHeight();
	}
	BinNode* tallerChild(){//���ؽϸߵĺ��ӣ�����߶���ȣ������븸��(������)ͬ����
		int fac = balanceFactor();
		return fac > 0 ? leftChild : (fac < 0 ? rightChild : (isLChild() ? leftChild : rightChild));
	}
	//��ǰ�ڵ��ֱ�Ӻ��,��������ʵ�ֵ��������O(logn)������˳��ִ�У���̯O(1)
	BinNode* succ(){
		BinNode* s = this;
		if(rightChild){//�����Һ��ӣ���ֱ�Ӻ�̱�����������
			s = rightChild;
			while(s->hasLChild())s = s->leftChild;
		}else{//����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�
			while(s->isRChild())s = s->parent;
			s = s->parent;//����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
		}
		return s;
	}
	//��ʱ����ת
	BinNode* zag(){
		BinNode* rc = rightChild;
		//�ı�ṹ
		rc->parent = this->parent;
		if(rc->parent)
			(this == rc->parent->leftChild ? rc->parent->leftChild : rc->parent->rightChild) = rc;
		rightChild = rc->leftChild;
		if(rightChild)rightChild->parent = this;
		rc->leftChild = this;
		this->parent = rc;
		//���¾ֲ��߶�
		height = 1 + max(leftHeight(), rightHeight());
		rc->height = 1 + max(rc->leftHeight(), rc->rightHeight());
		//�������ȸ߶�
		for(BinNode* x = rc->parent; x; x = x->parent){
			if(x->height == 1 + max(x->rightHeight(), x->leftHeight()))break;
			x->height = 1 + max(x->rightHeight(), x->leftHeight());
		}
		return rc;//������ת�����ߵ�
	}
	//˳ʱ����ת
	BinNode* zig(){//˳ʱ��
		BinNode* lc = leftChild;
		//�ı�ṹ
		lc->parent = this->parent;
		if(lc->parent)
			(this == lc->parent->rightChild? lc->parent->rightChild : lc->parent->leftChild) = rightChild;
		leftChild = lc->rightChild;
		if(leftChild)leftChild->parent = this;
		lc->rightChild = this;
		this->parent = lc;
		//���¾ֲ��߶�
		height = 1 + max(leftHeight(), rightHeight());
		lc->height = 1 + max(lc->leftHeight(), lc->rightHeight());
		//�������ȸ߶�
		for(BinNode* x = lc->parent; x; x = x->parent){
			if(x->height == 1 + max(x->rightHeight(), x->leftHeight()))break;
			x->height = 1 + max(x->rightHeight(), x->leftHeight());
		}
		return lc;//������ת�����ߵ�
	}
	//�Ƚ���
	bool operator<(BinNode* bn){
		return weight < bn->weight;
	}

};

#endif