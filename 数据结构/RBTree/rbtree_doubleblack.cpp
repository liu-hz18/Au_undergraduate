
#include "rbtree.h"

//˫������
/******************************************************************************************
* RedBlack˫�ڵ����㷨������ڵ�x�뱻������Ľڵ��Ϊ��ɫ������
* ��Ϊ�����๲���������
*    BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�0����ת�����ٵݹ�
*    BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
*    BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�1����ת��תΪBB-1��BB2R
******************************************************************************************/
void RedBlackTree::solveDoubleBlack(BinNode* r, BinNode* hot){
	BinNode* p = r ? r->parent : hot;//r�ĸ���
	if(!p)return;
	BinNode* s = (r == p->leftChild) ? p->rightChild : p->leftChild;//r���ֵ�
	if(!s)return;
	if(s->isBlack()){//�ֵ�sΪ��
		BinNode* t = NULL;//s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL��
		if(s->rightChild && s->rightChild->isRed())t = s->rightChild;//����
		if(s->leftChild && s->leftChild->isRed())t = s->leftChild;//����
		if(t){//��s�к캢�ӣ�BB-1
			int oldColor = p->color;//����ԭ�������ڵ�p��ɫ������t���丸�ס��游
			BinNode*& temp = fromParentTo(p);// ���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
			BinNode* b = temp = rotateAt(t);//��ת
			if(b->hasLChild()){//����
				b->leftChild->color = BLACK;
				b->leftChild->updateHeight();
			}
			if(b->hasRChild()){//����
				b->rightChild->color = BLACK;
				b->rightChild->updateHeight();
			}
			b->color = oldColor;
			b->updateHeight(); //���������ڵ�̳�ԭ���ڵ����ɫ
		}else{//��s�޺캢��
			s->color = RED;//sת��
			s->height--;
			if(p->isRed())p->color = BLACK;//BB-2R pת�ڣ����ڸ߶Ȳ���
			else{//BB-2B
				p->height--;//p���ֺڣ����ڸ߶��½�
				solveDoubleBlack(p, hot);//�ݹ�����
			}
		}
	}else{//�ֵ�sΪ�죺BB-3
		s->color = BLACK;//sת�ڣ�pת��
		p->color = RED;
		BinNode* t = s->isLChild() ? s->leftChild : s->rightChild;//ȡt���丸sͬ��
		hot = p;
		BinNode*& temp = fromParentTo(p);
		temp = rotateAt(t);//��t���丸�ס��游��ƽ�����
		solveDoubleBlack(r, hot);//��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
	}
}
