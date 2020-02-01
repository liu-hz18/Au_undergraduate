
#include <stdio.h>
#include "rbtree.h"

void RedBlackTree::traverseIn(BinNode* r){//ÖÐÐò±éÀú
	if(!r)return ;
	if(r->leftChild)traverseIn(r->leftChild);
	printf(" %d(H:%d C:%d) ", r->weight, r->height, r->color);
	if(r->rightChild)traverseIn(r->rightChild);
}