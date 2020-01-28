
#ifndef _BINNODE_H_
#define _BINNODE_H_

#include "util.h"

//ģ����������Ͷ���������ͬһ���ļ���
//��ͨ�������.h�ļ�����������.cpp�ļ��ж��壬����.cpp�ļ���include "xxx.h"
template<typename T>
struct BinNode{
	T data;
	BinNode* lc;
	BinNode* rc;
	int height;
	
	BinNode(T d, BinNode* l = NULL, BinNode* r = NULL, int h = 0):data(d), lc(l), rc(r), height(h){}
	
	BinNode<T>* insertAsLC(T d){
		lc = new BinNode(d);
		height = rc ? (1 + rc->height) : 1;
		return lc;
	}
	BinNode<T>* insertAsRC(T d){
		rc = new BinNode(d);
		height = lc ? (1 + c->height) : 1;
		return rc;
	}
	BinNode<T>* insertAsLC(BinNode* bn){
		lc = bn;
		height = rc ? max(rc->height, lc->height) : (1 + lc->height);
		return lc;
	}
	BinNode<T>* insertAsRC(BinNode* bn){
		rc = bn;
		height = lc ? max(lc->height, rc->height) ; (1 + rc->height);
		return rc;
	}
	BinNode<T>* removeLC(){
		BinNode* temp = lc;
		lc = NULL;
		return temp;
	}
	BinNode<T>* removeRC(){
		BinNode* temp = rc;
		rc = NULL;
		return temp;
	}
	//T����Ӧ����<�����
	bool operator<(BinNode const& bn){
		return data < bn.data;
	}
	//T����Ӧ����==�����
	bool operator==(BinNode const& bn){
		return data == bn.data;
	}
	bool isleaf()const{
		return height == 0;
	}
};

#endif
