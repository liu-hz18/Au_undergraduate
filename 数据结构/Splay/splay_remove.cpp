
#include "SplayTree.h"
#include "util.h"

bool SplayTree::remove(int data){//ɾ��
	if(!root || data != search(data)->weight)return false;
	BinNode* w = root;//��search()��ڵ�e�ѱ���չ������
	//�Ը��ڵ���в���
	if(!root->hasLChild()){//��������������ֱ��ɾ��
		root = root->rightChild;
		if(root)root->parent = NULL;
	}else if(!root->hasRChild()){//������������Ҳֱ��ɾ��
		root = root->leftChild;
		if(root)root->parent = NULL;
	}else{//����������ͬʱ����
		BinNode* lTree = root->leftChild;
		lTree->parent = NULL;
		root->leftChild = NULL;//��ʱ���������г�
		root = root->rightChild;
		root->parent = NULL;//ֻ����������
		search(w->weight);//!��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ�����,����������С�ڵ����չ�������ң�������ͬ�ڵ㣩���������ؿ�
		root->leftChild =  lTree;
		lTree->parent = root;//ֻ�轫ԭ�������ӻ�ԭλ����
	}
	_size--;
	delete w;//�ͷŽڵ�
	if(root)root->height = 1 + max(root->leftHeight(), root->rightHeight());
	return true;
}
