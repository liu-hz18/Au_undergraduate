
#include "rbtree.h"

//˫������
/******************************************************************************************
* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
*    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
******************************************************************************************/
void RedBlackTree::solveDoubleRed(BinNode* x){
	if(x == root){//���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
		root->color = BLACK;
		root->height++;
		return;
	}
	BinNode* p = x->parent;//����x�ĸ���p�ش���
	if(p->isBlack())return;//��pΪ�ڣ������ֹ����������
	BinNode* g = p->parent;//��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
	BinNode* u = (p == g->leftChild) ? g->rightChild : g->leftChild;//uncle(x)��x�常u����ɫ�ֱ���
	if(!u)return;
	if(u->isBlack()){
		if(x->isLChild() == p->isLChild())p->color = BLACK;//��x��pͬ�ࣨ��zIg-zIg��zAg-zAg),p�ɺ�ת�ڣ�x���ֺ�
		else x->color = BLACK;//��x��p��ࣨ��zIg-zAg��zAg-zIg��,x�ɺ�ת�ڣ�p���ֺ�
		g->color = RED;//g�ض��ɺ�ת��
		//�����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ,����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ���	
		BinNode* gg = g->parent;//���游
		BinNode*& temp = fromParentTo(g);//��������������ڵ�
		BinNode* r = temp = rotateAt(x);//��ԭ���游����
		r->parent = gg;
	}else{//��uΪ��ɫ
		p->color = BLACK;//p�ɺ�ת��
		p->height++;
		u->color = BLACK;//u�ɺ�ת��
		u->height++;
		if(g != root)g->color = RED;//u�ɺ�ת��
		solveDoubleRed(g);//��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
	}
}
