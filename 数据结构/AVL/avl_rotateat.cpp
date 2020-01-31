
#include "AVL.h"

/******************************************************************************************
* BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
* 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
******************************************************************************************/
BinNode* AVLTree::rotateAt(BinNode* v){
	BinNode* p = v->parent;
	BinNode* g = p->parent;
	if(p->isLChild()){//zig
			if(v->isLChild()){//zig-zig
			p->parent = g->parent;//向上联接
			return connect34(v, p, g, v->leftChild, v->rightChild, p->rightChild, g->rightChild);
		}else{//zig-zag
			v->parent = g->parent;//向上联接
			return connect34(p, v, g, p->leftChild, v->leftChild, v->rightChild, g->rightChild);
		}
	}else{//zag
		if(v->isRChild()){//zag-zag
			p->parent = g->parent;
			return connect34(g, p, v, g->leftChild, p->leftChild, v->leftChild, v->rightChild);
		}else{//zag-zig
			v->parent = g->parent;
			return connect34(g, v, p, g->leftChild, v->leftChild, v->rightChild, p->rightChild);
		}
	}
}
