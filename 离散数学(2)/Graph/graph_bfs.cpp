
#include "Graph.h"

//单连通域BFS
void Graph::BFS(int v, int& clock){
	queue<int> Q;//辅助队列
	vertex[v].state = DISCOVERED;
	Q.push(v);
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		vertex[v].dTime = ++clock;
		//遍历所有出边
		for(list<Edge>::iterator iter = edgeList[v].begin(); iter != edgeList[v].end(); iter++){
			int u = iter->to;
			if(vertex[u].state == UNDISCOVERED){
				vertex[u].state = DISCOVERED;
				Q.push(u);
				vertex[u].parent = v;
				iter->edgeType = TREE;
			}else{
				iter->edgeType = CROSS;
			}
		}
		vertex[v].state = VISITED;
	}
}

//对于固定图的算法接口
//全图bfs
void Graph::bfs(int s){//从源点s开始进行bfs
	assert(0 <= s && s < n);
	reset();
	int clock = 0, v = s;
	do{
		if(vertex[v].state == UNDISCOVERED){
			BFS(v, clock);
		}
		v = (v + 1) % n;
	}while(v != s);
}
