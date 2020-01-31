
#include "AVL.h"

BinNode* AVLTree::insert(int data){
	if(!_size){//�����������Ϊ����
		_size++;
		return root = new BinNode(data);
	}
	BinNode* hot = searchIn(data);
	if(hot->weight == data)return hot;//��֤����û�д�ֵ
	BinNode* newx = new BinNode(data);
	newx->parent = hot;//�����Ϊ����Ҷ��
	if(data < hot->weight)hot->leftChild = newx;
	else hot->rightChild = newx;
	_size++;
	for(BinNode* g = hot; g; g = g->parent){//��������
		if(!g->avlBalanced()){//һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮����
			BinNode*& gg = fromParentTo(g);
			gg = rotateAt(g->tallerChild()->tallerChild());//�������½���ԭ��
			break;
		}//g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����;����g��Ȼƽ�⣩��ֻ��򵥵ظ�����߶�
		else g->updateHeight();
	}//��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
	return newx;
}
