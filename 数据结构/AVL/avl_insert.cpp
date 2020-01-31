
#include "AVL.h"

BinNode* AVLTree::insert(int data){
	if(!_size){//空树，则插入为树根
		_size++;
		return root = new BinNode(data);
	}
	BinNode* hot = searchIn(data);
	if(hot->weight == data)return hot;//保证树中没有此值
	BinNode* newx = new BinNode(data);
	newx->parent = hot;//插入成为树的叶子
	if(data < hot->weight)hot->leftChild = newx;
	else hot->rightChild = newx;
	_size++;
	for(BinNode* g = hot; g; g = g->parent){//调整树高
		if(!g->avlBalanced()){//一旦发现g失衡，则（采用“3 + 4”算法）使之复衡
			BinNode*& gg = fromParentTo(g);
			gg = rotateAt(g->tallerChild()->tallerChild());//子树重新接入原树
			break;
		}//g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束;否则（g依然平衡），只需简单地更新其高度
		else g->updateHeight();
	}//可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
	return newx;
}
