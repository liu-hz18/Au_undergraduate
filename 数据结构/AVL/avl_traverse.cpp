
#include "AVL.h"

void AVLTree::traverseIn(BinNode* r){//�������
	if(!r)return ;
	if(r->leftChild)traverseIn(r->leftChild);
	printf(" %d(%d) ", r->weight, r->height);
	if(r->rightChild)traverseIn(r->rightChild);
}