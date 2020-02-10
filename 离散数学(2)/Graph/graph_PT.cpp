
#include "vertex_PT.h"
#include "Graph.h"

//用于qsort的compare
int compareNode(const void* x, const void* y){
	return (*(vertexPT*)x).rank - (*(vertexPT*)y).rank;
}

//求每个顶点(工序)的最早启动时间(同时也是v1 - vi的最长路径，即应等待其之前的所有工序都完成才能开始本工序)
void Graph::earlistStartTime(){
	vertexpt = new vertexPT[n];
	topoSortDFS(0, true);//获得拓扑序
	for(int i = 0; i < n; i++)vertexpt[i].set(i, vertex[i].topoIndex, -1, -1);
	qsort(vertexpt, n, sizeof(vertexPT), compareNode);//对顶点按拓扑序排序
	//重建入度邻接表， 入度表中to是from
	list<Edge>* indeg = new list<Edge>[n];
	for(int i = 0; i < n; i++){
		for(auto& it : edgeList[i]){
			indeg[it.to].push_back(Edge(i, it.weight));
		}
	}
	int* rank = new int[n];
	for(int i = 0; i < n; i++)rank[vertexpt[i].index] = i;
	//跑最长路径算法
	vertexpt[0].earStartTime = 0;
	for(int i = 1; i < n; i++){
		int max = -1;
		for(auto& it : indeg[vertexpt[i].index]){
			if(max < vertexpt[rank[it.to]].earStartTime + it.weight)max = vertexpt[rank[it.to]].earStartTime + it.weight;
		}
		vertexpt[i].earStartTime = max;
	}
	for(int i = 0; i < n; i++){
		vertex[vertexpt[i].index].earStartTime = vertexpt[i].earStartTime;
	}
	delete[] indeg;
	delete[] rank;
}

//必须先得到最早启动时间才能调用本函数！！！
//求每个顶点(工序)的最晚启动时间(同时也是vi - vn的最长路径，即不能再晚，否则最后一道工序会延误)
void Graph::latestStartTime(){
	int* rank = new int[n];
	for(int i = 0; i < n; i++)rank[vertexpt[i].index] = i;//建立倒映射
	vertexpt[n-1].latStartTime = vertexpt[n-1].earStartTime;
	for(int i = n-2; i >= 0; i--){
		int min = INT_MAX;
		for(auto& it : edgeList[vertexpt[i].index]){
			if(min > vertexpt[rank[it.to]].latStartTime - it.weight)min = vertexpt[rank[it.to]].latStartTime - it.weight;
		}
		vertexpt[i].latStartTime = min;
	}
	for(int i = 0; i < n; i++){
		vertex[vertexpt[i].index].latStartTime = vertexpt[i].latStartTime;
	}
	delete[] rank;
}
