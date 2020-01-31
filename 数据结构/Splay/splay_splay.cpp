
#include "SplayTree.h"
#include "util.h"

//����tarjian˫����չ����
BinNode* SplayTree::splay(BinNode* v){//���ڵ�v��չ����
	if(!v)return NULL;
	BinNode *p, *g;//���׺��游
	while((p = v->parent) && (g = p->parent)){//���¶��ϣ�������*v��˫����չ
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
		if(!gg)v->parent = NULL;//��vԭ�ȵ����游gg�����ڣ���v����ӦΪ����
		else (g == gg->leftChild) ? gg->insertAsLeft(v) : gg->insertAsRight(v);
		g->height = 1 + max(g->leftHeight(), g->rightHeight());
		p->height = 1 + max(p->leftHeight(), p->rightHeight());
		v->height = 1 + max(v->leftHeight(), v->rightHeight());
	}//˫����չ����ʱ������g == NULL����p���ܷǿ�
	if(p = v->parent){//��p����ǿգ����������һ�ε���
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
}//����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯����������
