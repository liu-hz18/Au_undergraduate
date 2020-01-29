
#include "unionSet.h"
#include "Graph.h"

//用于qsort的compare
int compare(const void* x, const void* y){
	return (*(Edge*)x).weight - (*(Edge*)y).weight;
}

//最小支撑树，并查集版本 kruskal, O(eloge),返回最小支撑树的边集
int Graph::kruskal(list<Edge>* result){
	reset();
	//构建边表
	Edge* edge = new Edge[e];
	unionSet set(n);
	int count = 0, sum = 0;
	//有向图遍历方式，无向图在邻接表中边数为2e，所以只需要存一半
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator iter = edgeList[i].begin(); iter != edgeList[i].end(); iter++){
			if(!isDirected && iter->to <= i)continue;//保证无向图每个边只存一次
			edge[count].data = i;
			edge[count].to = iter->to;
			edge[count].weight = iter->weight;
			count++;
		}
	}
	//从小到大 排序
	qsort(edge, e, sizeof(Edge), compare);
	//kruskal
	for(int i = 0; i < e; i++){
		int u = edge[i].data;
		int v = edge[i].to;
		if(set.find(u) != set.find(v)){
			set.Union(u, v); //O(1)
			vertex[v].parent = u;
			result->push_back(edge[i]);
			sum += edge[i].weight;
		}
	}
	delete[] edge;
	return sum;
}
