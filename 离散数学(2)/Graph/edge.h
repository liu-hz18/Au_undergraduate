
#ifndef _EDGE_H_
#define _EDGE_H_

#include "macro.h"

//边类
struct Edge{
	int data;//数据域，也可以记成from
	int to;//有向图中指向的节点编号
	int weight;//权重
	char edgeType;
	Edge():edgeType(UNETERMINED){}
	Edge(int t, int w = 1):weight(w), to(t), edgeType(UNETERMINED){}
	//Edge(int f, int t, int w = 1):data(f), to(t), weight(w){}
	void reset(){
		edgeType = UNETERMINED;
	}
	//权重比较器
	bool operator<(Edge const& e){
		return weight < e.weight;
	}
	bool operator==(Edge const& e){
		return weight < e.weight;
	}
};

#endif
