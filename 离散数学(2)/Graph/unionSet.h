
#ifndef _UNIONSET_H_
#define _UNIONSET_H_

#include "util.h"

//���鼯
class unionSet{
	int n;
	int* parent;
	int* size;

public:
	unionSet(int _n):n(_n), parent(new int[n]), size(new int[n]){
	    for(int i = 0; i < n; i++)parent[i] = i;//i��������Լ��ļ�����
		memset(size, 1, n * sizeof(int));
	}
	~unionSet(){
		delete[] parent;
		delete[] size;
	}
	void reset(){
		for(int i = 0; i < n; i++)parent[i] = i;
	}
	//���ң�·��ѹ��
	int find(int x){
		if(x != parent[x])parent[x] = find(parent[x]);
		return parent[x];
	}
	void Union(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y)return;
		if(size[x] > size[y])swap(x, y);
		parent[x] = y;
		size[y] += size[x];
	}
};

#endif
