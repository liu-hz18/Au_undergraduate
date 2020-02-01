
#include "rbtree.h"

//双黑修正
/******************************************************************************************
* RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
* 分为三大类共四种情况：
*    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
*    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
*    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
******************************************************************************************/
void RedBlackTree::solveDoubleBlack(BinNode* r, BinNode* hot){
	BinNode* p = r ? r->parent : hot;//r的父亲
	if(!p)return;
	BinNode* s = (r == p->leftChild) ? p->rightChild : p->leftChild;//r的兄弟
	if(!s)return;
	if(s->isBlack()){//兄弟s为黑
		BinNode* t = NULL;//s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
		if(s->rightChild && s->rightChild->isRed())t = s->rightChild;//右子
		if(s->leftChild && s->leftChild->isRed())t = s->leftChild;//左子
		if(t){//黑s有红孩子：BB-1
			int oldColor = p->color;//备份原子树根节点p颜色，并对t及其父亲、祖父
			BinNode*& temp = fromParentTo(p);// 以下，通过旋转重平衡，并将新子树的左、右孩子染黑
			BinNode* b = temp = rotateAt(t);//旋转
			if(b->hasLChild()){//左子
				b->leftChild->color = BLACK;
				b->leftChild->updateHeight();
			}
			if(b->hasRChild()){//右子
				b->rightChild->color = BLACK;
				b->rightChild->updateHeight();
			}
			b->color = oldColor;
			b->updateHeight(); //新子树根节点继承原根节点的颜色
		}else{//黑s无红孩子
			s->color = RED;//s转红
			s->height--;
			if(p->isRed())p->color = BLACK;//BB-2R p转黑，但黑高度不变
			else{//BB-2B
				p->height--;//p保持黑，但黑高度下降
				solveDoubleBlack(p, hot);//递归上溯
			}
		}
	}else{//兄弟s为红：BB-3
		s->color = BLACK;//s转黑，p转红
		p->color = RED;
		BinNode* t = s->isLChild() ? s->leftChild : s->rightChild;//取t与其父s同侧
		hot = p;
		BinNode*& temp = fromParentTo(p);
		temp = rotateAt(t);//对t及其父亲、祖父做平衡调整
		solveDoubleBlack(r, hot);//继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
	}
}
