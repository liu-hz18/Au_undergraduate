
#pragma once
#include "util.h"

//���鼯
class unionSet{
	int n;
	int* parent;
	int* size;
	bool* singled;

public:
	unionSet(int _n):n(_n), parent(new int[n]), size(new int[n]), singled(new bool[n]){
	    for(int i = 0; i < n; i++)parent[i] = i;//i��������Լ��ļ�����
		memset(size, 1, n * sizeof(int));
		memset(singled, 1, n * sizeof(bool));
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
	//�ϲ���������
	void Union(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y)return;
		if(size[x] > size[y])swap(x, y);
		parent[x] = y;
		size[y] += size[x];
		singled[x] = singled[y] = false;
	}
	void isolate(int x){//ʹĳ��Ӽ����й�������O(n)
		if(singled[x])return;
		int i = 0;
		for(; i < n; i++){//�ҵ�x��һ������
			if(parent[i] == x && i != x)break;
		}
		if(i == n || x == i)return;
		parent[i] = (parent[x] == x) ? i : parent[x];
		for(int j = i+1; j < n; j++){//������
			if(parent[j] == x)parent[j] = i;
		}
		parent[x] = x;//����
	}
};
