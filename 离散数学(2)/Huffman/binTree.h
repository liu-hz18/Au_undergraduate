
#ifndef _BINTREE_H_
#define _BINTREE_H_

#include "util.h"
#include "binNode.h"

//二叉树，同时维护高度信息
template<typename T>
class BinTree{
protected:
	int _size;
	BinNode<T>* _root;

public:
	BinTree(T d):_size(0), _root(new BinNode<T>(d)){}
	~BinTree(){
		if(_root)release(_root);
	}
	void release(BinNode<T>* bn){
		if(bn->lc)release(bn->lc);
		if(bn->rc)release(bn->rc);
		delete bn;
	}
	bool empty()const{return !_root;}
	int size()const{return _size;}
	//子树连接
	void attachAsLT(BinTree<T>* bt){
		assert(_root->lc == NULL);
		_root->lc = bt->_root;
		_size += bt->_size;
		_root->height = 1 + (_root->rc ? max(_root->lc->height, _root->rc->height) : _root->lc->height);
	}
	void attachAsRT(BinTree<T>* bt){
		assert(_root->rc == NULL);
		_root->rc = bt->_root;
		_size += bt->_size;
		_root->height = 1 + (_root->lc ? max(_root->rc->height, _root->lc->height) : _root->rc->height);
	}
	bool operator<(BinTree<T> const& bt){
		return *(_root) < *(bt._root);
	}
	bool operator==(BinTree<T> const& bt){
		return *(_root) == *(bt._root);
	}
	BinNode<T>* root()const{
		return _root;
	}
};


#endif
