
#include "AVL.h"

/******************************************************************************************
* BST�ڵ���ת�任ͳһ�㷨��3�ڵ� + 4�����������ص���֮��ֲ��������ڵ��λ��
* ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ�������������������ϲ㺯�����
******************************************************************************************/
BinNode* AVLTree::rotateAt(BinNode* v){
	BinNode* p = v->parent;
	BinNode* g = p->parent;
	if(p->isLChild()){//zig
			if(v->isLChild()){//zig-zig
			p->parent = g->parent;//��������
			return connect34(v, p, g, v->leftChild, v->rightChild, p->rightChild, g->rightChild);
		}else{//zig-zag
			v->parent = g->parent;//��������
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
