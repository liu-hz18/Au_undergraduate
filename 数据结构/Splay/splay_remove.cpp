
#include "SplayTree.h"
#include "util.h"

bool SplayTree::remove(int data){//删除
	if(!root || data != search(data)->weight)return false;
	BinNode* w = root;//经search()后节点e已被伸展至树根
	//对根节点进行操作
	if(!root->hasLChild()){//若无左子树，则直接删除
		root = root->rightChild;
		if(root)root->parent = NULL;
	}else if(!root->hasRChild()){//若无右子树，也直接删除
		root = root->leftChild;
		if(root)root->parent = NULL;
	}else{//若左右子树同时存在
		BinNode* lTree = root->leftChild;
		lTree->parent = NULL;
		root->leftChild = NULL;//暂时将左子树切除
		root = root->rightChild;
		root->parent = NULL;//只保留右子树
		search(w->weight);//!以原树根为目标，做一次（必定失败的）查找,右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空
		root->leftChild =  lTree;
		lTree->parent = root;//只需将原左子树接回原位即可
	}
	_size--;
	delete w;//释放节点
	if(root)root->height = 1 + max(root->leftHeight(), root->rightHeight());
	return true;
}
