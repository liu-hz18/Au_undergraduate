
#ifndef _BINNODE_H_
#define _BINNODE_H_

#include "util.h"

//二叉树结点
struct BinNode{
	int weight;//点权值
	int height;//高度
	BinNode* parent;
	BinNode* leftChild;
	BinNode* rightChild;
	int color;

	BinNode():height(0), parent(NULL), leftChild(NULL), rightChild(NULL), color(RED){}
	BinNode(int w):weight(w), height(0), parent(NULL), leftChild(NULL), rightChild(NULL), color(RED){}
	BinNode* insertAsLeft(BinNode* child){
		leftChild = child;
		if(leftChild)leftChild->parent = this;
		height = 1 + max(leftHeight(), rightHeight());
		return leftChild;
	}
	BinNode* insertAsRight(BinNode* child){
		rightChild = child;
		if(rightChild)rightChild->parent = this;
		height = 1 + max(leftHeight(), rightHeight());
		return rightChild;
	}
	bool hasLChild()const{
		return leftChild != NULL;
	}
	bool hasRChild()const{
		return rightChild != NULL;
	}
	bool isLChild()const{
		if(parent && parent->leftChild == this)return true;
		return false;
	}
	bool isRChild()const{
		if(parent && parent->rightChild == this)return true;
		return false;
	}
	int leftHeight()const{
		return leftChild ? leftChild->height : -1;
	}
	int rightHeight()const{
		return rightChild ? rightChild->height : -1;
	}
	void updateHeight(){//只更新黑高度
		height = max(leftHeight(), rightHeight());//孩子一般黑高度相等，除非出现双黑
		if(isBlack())height++;//若当前节点为黑，则计入黑深度
	}//因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断
	bool blackHeightUpdated(){
		return leftHeight() == rightHeight() && height == (isBlack() ? (leftHeight() + 1) : leftHeight());
	}
	bool isBlack()const{ return color == BLACK; }
	bool isRed()const{ return color == RED; }
	//递归得到size,O(size)
	int size()const{
		int s = 1;
		if(leftChild)s += leftChild->size();
		if(rightChild)s += rightChild->size();
		return s;
	}
	bool avlBalanced(){//AVL是否平衡
		return -2 < balanceFactor() && balanceFactor() < 2;
	}
	//平衡因子
	int balanceFactor(){
		return leftHeight() - rightHeight();
	}
	BinNode* tallerChild(){//返回较高的孩子，如果高度相等，返回与父亲(的左右)同侧者
		int fac = balanceFactor();
		return fac > 0 ? leftChild : (fac < 0 ? rightChild : (isLChild() ? leftChild : rightChild));
	}
	//当前节点的直接后继,可以用于实现迭代器，最坏O(logn)，但若顺序执行，均摊O(1)
	BinNode* succ(){
		BinNode* s = this;
		if(rightChild){//若有右孩子，则直接后继必在右子树中
			s = rightChild;
			while(s->hasLChild())s = s->leftChild;
		}else{//否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”
			while(s->isRChild())s = s->parent;
			s = s->parent;//最后再朝右上方移动一步，即抵达直接后继（如果存在）
		}
		return s;
	}
	//逆时针旋转
	BinNode* zag(){
		BinNode* rc = rightChild;
		//改变结构
		rc->parent = this->parent;
		if(rc->parent)
			(this == rc->parent->leftChild ? rc->parent->leftChild : rc->parent->rightChild) = rc;
		rightChild = rc->leftChild;
		if(rightChild)rightChild->parent = this;
		rc->leftChild = this;
		this->parent = rc;
		//更新局部高度
		height = 1 + max(leftHeight(), rightHeight());
		rc->height = 1 + max(rc->leftHeight(), rc->rightHeight());
		//更新祖先高度
		for(BinNode* x = rc->parent; x; x = x->parent){
			if(x->height == 1 + max(x->rightHeight(), x->leftHeight()))break;
			x->height = 1 + max(x->rightHeight(), x->leftHeight());
		}
		return rc;//返回旋转后的最高点
	}
	//顺时针旋转
	BinNode* zig(){//顺时针
		BinNode* lc = leftChild;
		//改变结构
		lc->parent = this->parent;
		if(lc->parent)
			(this == lc->parent->rightChild? lc->parent->rightChild : lc->parent->leftChild) = rightChild;
		leftChild = lc->rightChild;
		if(leftChild)leftChild->parent = this;
		lc->rightChild = this;
		this->parent = lc;
		//更新局部高度
		height = 1 + max(leftHeight(), rightHeight());
		lc->height = 1 + max(lc->leftHeight(), lc->rightHeight());
		//更新祖先高度
		for(BinNode* x = lc->parent; x; x = x->parent){
			if(x->height == 1 + max(x->rightHeight(), x->leftHeight()))break;
			x->height = 1 + max(x->rightHeight(), x->leftHeight());
		}
		return lc;//返回旋转后的最高点
	}
	//比较器
	bool operator<(BinNode* bn){
		return weight < bn->weight;
	}

};

#endif