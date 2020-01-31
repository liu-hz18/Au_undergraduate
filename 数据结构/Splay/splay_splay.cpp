
#include "SplayTree.h"
#include "util.h"

//采用tarjian双层伸展策略
BinNode* SplayTree::splay(BinNode* v){//将节点v伸展至根
	if(!v)return NULL;
	BinNode *p, *g;//父亲和祖父
	while((p = v->parent) && (g = p->parent)){//自下而上，反复对*v做双层伸展
		BinNode* gg = g->parent;
		if(v->isLChild()){
			if(p->isLChild()){//zig-zig
				g->insertAsLeft(p->rightChild);
				p->insertAsLeft(v->rightChild);
				p->insertAsRight(g);
				v->insertAsRight(p);
			}else{//zig-zag
				p->insertAsLeft(v->rightChild);
				g->insertAsRight(v->leftChild);
				v->insertAsLeft(g);
				v->insertAsRight(p);
			}
		}else if(p->isRChild()){//zag-zag
			g->insertAsRight(p->leftChild);
			p->insertAsRight(v->leftChild);
			p->insertAsLeft(g);
			v->insertAsLeft(p);
		}else{//zag-zig
			p->insertAsRight(v->leftChild);
			g->insertAsLeft(v->rightChild);
			v->insertAsRight(g);
			v->insertAsLeft(p);
		}
		if(!gg)v->parent = NULL;//若v原先的曾祖父gg不存在，则v现在应为树根
		else (g == gg->leftChild) ? gg->insertAsLeft(v) : gg->insertAsRight(v);
		g->height = 1 + max(g->leftHeight(), g->rightHeight());
		p->height = 1 + max(p->leftHeight(), p->rightHeight());
		v->height = 1 + max(v->leftHeight(), v->rightHeight());
	}//双层伸展结束时，必有g == NULL，但p可能非空
	if(p = v->parent){//若p果真非空，则额外再做一次单旋
		if(v->isLChild()){
			p->insertAsLeft(v->rightChild);
			v->insertAsRight(p);
		}else{
			p->insertAsRight(v->leftChild);
			v->insertAsLeft(p);
		}
		p->height = 1 + max(p->leftHeight(), p->rightHeight());
		v->height = 1 + max(v->leftHeight(), v->rightHeight());
	}
	v->parent = NULL;
	return v;
}//调整之后新树根应为被伸展的节点，故返回该节点的位置以便上层函数更新树根
