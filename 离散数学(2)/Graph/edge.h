
#pragma once
#include "macro.h"

//����
struct Edge{
	int data;//������Ҳ���Լǳ�from
	int to;//����ͼ��ָ��Ľڵ���
	int weight;//Ȩ��
	char edgeType;
	Edge():edgeType(UNETERMINED){}
	Edge(int t, int w = 1):weight(w), to(t), edgeType(UNETERMINED){}
	//Edge(int f, int t, int w = 1):data(f), to(t), weight(w){}
	void reset(){
		edgeType = UNETERMINED;
	}
	//Ȩ�رȽ���
	bool operator<(Edge const& e){
		return weight < e.weight;
	}
	bool operator==(Edge const& e){
		return weight < e.weight;
	}
};
