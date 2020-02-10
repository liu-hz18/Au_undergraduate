
#include "Graph.h"

//����ͨ��DFS
void Graph::DFS(int v, int& clock){
	vertex[v].dTime = ++clock;
	vertex[v].state = DISCOVERED;
	//�������г���
	for(auto& iter : edgeList[v]){
		int u = iter.to;
		switch(vertex[u].state){
			case UNDISCOVERED:
				iter.edgeType = TREE;
				vertex[u].parent = v;
				DFS(u, clock);
				break;
			case DISCOVERED:
				iter.edgeType = BACKWARD;
				break;
			default:
				iter.edgeType = (vertex[v].dTime < vertex[u].dTime) ? FORWARD : CROSS;
				break;
		}
	}
	vertex[v].state = VISITED;
	vertex[v].fTime = ++clock;
}

//ȫͼdfs
void Graph::dfs(int s){
	assert(0 <= s && s < n);
	reset();
	int clock = 0, v = s;
	do{
		if(vertex[v].state == UNDISCOVERED){
			DFS(v, clock);
		}
		v = (v + 1) % n;
	}while(v != s);
}
