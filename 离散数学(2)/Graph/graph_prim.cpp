
#include "minHeap.h"
#include "Graph.h"

//最小支撑树,朴素prim(BFS),O(n^2+e)
int Graph::primBrute(int s, list<Edge>* result){
	assert(0 <= s && s < n);
	reset();
	int sum = 0;
	vertex[s].priority = 0;
	int u = s, shortest;
	for(int i = 0; i < n; i++){
		vertex[u].state = VISITED;
		if(u != s){
			Edge e = Edge(u, shortest); e.data = vertex[u].parent;//(v, u) 
			result->push_back(e);
			sum += shortest;
		}
		for(list<Edge>::iterator iter = edgeList[u].begin(); iter != edgeList[u].end(); iter++){
			int j = iter->to;
			//松弛操作
			if(vertex[j].state == UNDISCOVERED && vertex[j].priority > iter->weight){
				vertex[j].priority = iter->weight;
				vertex[j].parent = u;//为还原树的结构，必须记录parent
			}
		}
		//选出下一个极短跨边
		shortest = INT_MAX;
		for(int j = 0; j < n; j ++){
			if(vertex[j].state == UNDISCOVERED && shortest > vertex[j].priority){
				shortest = vertex[j].priority;
				u = j;
			}
		}
	}
	return sum;
}

//prim() (BFS)堆优化,O((n+e)logn),选择 最短的边 加入树
int Graph::primHeap(int s, list<Edge>* result){
	assert(0 <= s && s < n);
	reset();
	MinHeap<Vertex> H(n);
	int sum = 0;
	vertex[s].priority = 0;
	H.push(vertex[s]);
	//最小支撑树的边 用树边TREE代表
	while(!H.empty()){
		Vertex ver = H.pop();
		int u = ver.data;
		if(u != s){
			sum += ver.priority;
			Edge e = Edge(u, ver.priority); e.data = vertex[u].parent;//(v, u)
			result->push_back(e);
		}
		if(vertex[u].state == VISITED)continue;
		vertex[u].state = VISITED;
		for(list<Edge>::iterator iter = edgeList[u].begin(); iter != edgeList[u].end(); iter++){
			int j = iter->to;
			if(vertex[j].priority > iter->weight){//松弛
				vertex[j].priority = iter->weight;
				vertex[j].parent = u;//为还原树的结构，必须记录parent
				H.push(vertex[j]);
			}
		}
	}
	return sum;
}
