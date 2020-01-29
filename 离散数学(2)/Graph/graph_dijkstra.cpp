
#include "minHeap.h"
#include "Graph.h"

//朴素dijkstra(BFS),正权矩阵, 单源点s最短路,O(n^2+e)
void Graph::dijkstraBrute(int s){
	assert(0 <= s && s < n);
	reset();
	vertex[s].priority = 0;//priority存放其他所有节点到源点的最短距离
	int source = s;
	//引入n个顶点和n-1条边
	for(int i = 0;i < n;i ++){
		vertex[s].state = VISITED;
		for(list<Edge>::iterator iter = edgeList[s].begin(); iter != edgeList[s].end(); iter++){
			int j = iter->to;
			//松弛操作
			if(vertex[j].state == UNDISCOVERED && vertex[j].priority > add(vertex[s].priority, iter->weight)){
				vertex[j].priority = vertex[s].priority + iter->weight;
				vertex[j].parent = s;
			}
		}
		//选出下一个最临近节点
		for(int shortest = INT_MAX, j = 0; j < n; j++){
			if(vertex[j].state == UNDISCOVERED && shortest > vertex[j].priority){
				shortest = vertex[j].priority;
				s = j;
			}
		}
	}
	//得到源点s的紧密中心度
	for(int i = 0; i < n; i++){
		if(vertex[i].priority < INT_MAX)
			vertex[source].closeCentrality += vertex[i].priority;
	}
}
//dijkstra堆优化(BFS),O((n+e)logn),选择优先级最低的点加入堆
void Graph::dijkstraHeap(int s){
	assert(0 <= s && s < n);
	reset();
	MinHeap<Vertex> H(n);
	int source = s;
	vertex[s].priority = 0;//priority存放其他所有节点到源点的最短距离
	H.push(vertex[s]);
	while(!H.empty()){
		int u = H.pop().data;
		if(vertex[u].state == VISITED)continue;//注意此处，不是u->next被访问，而是u被访问
		vertex[u].state = VISITED;
		for(list<Edge>::iterator iter = edgeList[u].begin(); iter != edgeList[u].end(); iter++){
			int j = iter->to;
			if(vertex[j].priority > add(vertex[u].priority, iter->weight)){//松弛
				vertex[j].priority = vertex[u].priority + iter->weight;
				vertex[j].parent = u;
				H.push(vertex[j]);
			}
		}
	}
	//得到源点s的紧密中心度
	for(int i = 0; i < n; i++){
		if(vertex[i].priority < INT_MAX)
			vertex[source].closeCentrality += vertex[i].priority;
	}
}
