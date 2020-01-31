
#include "AVL.h"

//���ı�ṹ������λ��
BinNode* AVLTree::searchIn(int data){
	BinNode* v = root, *hot;
	if(!root || v->weight == data)return v;
	hot = v;
	while(true){
		BinNode* c = (data < hot->weight) ? hot->leftChild : hot->rightChild;
		if(!c)return hot;//ȷ������ֵ��Ϊ��
		else if(c->weight == data)return c;
		hot = c;
	}//hotʼ��ָ�����һ��ʧ�ܽڵ�
	return hot;
}

BinNode* AVLTree::search(int data){
	return searchIn(data);
}