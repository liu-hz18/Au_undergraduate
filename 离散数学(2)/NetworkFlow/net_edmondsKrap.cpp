
#include "util.h"
#include "network.h"

//基于BFS(先标号先检查)寻找增广路，如果到达t点，一定是含边数量最短的增广路
bool network::EdmondsKrap(int s, int t){
	assert(0 <= s && s < n && 0 <= t && t < n);
	reset();
	queue<int> Q;
	vertex[s].state = DISCOVERED;
	vertex[s].prev = 0;
	vertex[s].addflow = INT_MAX;
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v = 0; v < n; v++){
			//存在正向边(u, v)或反向边(u, v)
			Edge e1 = edgeMat[u][v];
			if(e1.flow > INT_MIN){
				if(vertex[v].state == UNDISCOVERED && e1.cap > e1.flow){
					vertex[v].state = DISCOVERED;
					vertex[v].prev = u;
					vertex[v].addflow = min(vertex[u].addflow, e1.cap - e1.flow);
					Q.push(v);
				}
			}
		}
		vertex[u].state = VISITED;
		if(vertex[t].state != UNDISCOVERED)break;//直到找到增流路径
	}
	if(vertex[t].state == UNDISCOVERED || vertex[t].addflow <= 0)return false;
	return true;
}


//Ford-Fulkerson策略的最大流标号算法,底层使用EdmondsKrap算法,O(ne^2)
//同时可用于求最小割
int network::maxflow(int s, int t){
	int maxflow = 0;
	//标号和增流过程
	while(EdmondsKrap(s, t)){//标号过程，直到没有找到增流路径
		//增流过程
		int v = t, alpha = vertex[t].addflow;//汇点可改进量
		maxflow += alpha;
		//为保证每边的查找是O(1)的，应该使用邻接矩阵
		while(1){
			int u = vertex[v].prev;
			edgeMat[u][v].flow += alpha;
			edgeMat[v][u].flow -= alpha;
			if(u == s)break;//直到源点s
			v = u;
		}
	}
	return maxflow;
}

