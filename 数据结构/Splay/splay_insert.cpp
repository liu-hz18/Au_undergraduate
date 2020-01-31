
#include "SplayTree.h"

BinNode* SplayTree::insert(int data){//����
	if(!root){
		_size++;
		return root = new BinNode(data);
	}
	if(data == search(data)->weight)return root;//ȷ��Ŀ��ڵ㲻����
	_size++;
	BinNode* t = root;
	if(root->weight < data){//�����¸�����t��t->rcΪ���Һ���
		t->parent = root = new BinNode(data);
		root->leftChild = t;
		root->rightChild = t->rightChild;
		if(t->hasRChild()){
			t->rightChild->parent = root;
			t->rightChild = NULL;
		}
	}else{//�����¸�����t->lc��tΪ���Һ���
		t->parent = root = new BinNode(data);
		root->leftChild = t->leftChild;
		root->rightChild = t;
		if(t->hasLChild()){
			t->leftChild->parent = root;
			t->leftChild = NULL;
		}
	}
	//���¸��ڵ��ԭ�����ڵ�ĸ߶�
	updateHeightAbove(t);
	return root;
}
