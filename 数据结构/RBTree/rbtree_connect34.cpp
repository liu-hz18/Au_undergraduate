
#include "rbtree.h"

/******************************************************************************************
* ���ա�3 + 4���ṹ����3���ڵ㼰���Ŀ���������������֮��ľֲ��������ڵ�λ�ã���b��
* �������ڵ����ϲ�ڵ�֮���˫�����ӣ��������ϲ���������
* ������AVL��RedBlack�ľֲ�ƽ�����
******************************************************************************************/
BinNode* RedBlackTree::connect34(BinNode* a, BinNode* b, BinNode* c, \
						  BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3){
	a->leftChild = T0; if(T0)T0->parent = a;
	a->rightChild = T1; if(T1)T1->parent = a;
	a->updateHeight();
	c->leftChild = T2; if(T2)T2->parent = c;
	c->rightChild = T3; if(T3)T3->parent = c;
	c->updateHeight();
	b->leftChild = a; a->parent = b;
	b->rightChild = c; c->parent = b;
	b->updateHeight();
	return b;
}