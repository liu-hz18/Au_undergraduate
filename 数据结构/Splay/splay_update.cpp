
#include "SplayTree.h"
#include "util.h"

void SplayTree::updateHeightAbove(BinNode* v){
	while(v){
		if(v->height == 1 + max(v->leftHeight(), v->rightHeight()))break;
		v->height = 1 + max(v->leftHeight(), v->rightHeight());
		v = v->parent;
	}
}
