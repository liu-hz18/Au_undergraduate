
#include "Graph.h"

//求可达矩阵,O(n^3)
bool** Graph::warshall(bool print){
	reset();
	bool** reachable = new bool*[n];//可达矩阵
	for(int i = 0; i < n; i++){
		reachable[i] = new bool[n];
		memset(reachable[i], false, n * sizeof(bool));
	}
	//从邻接表得到邻接矩阵, 同样适用于无向图
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator iter = edgeList[i].begin(); iter != edgeList[i].end(); iter++){
			reachable[i][iter->to] = true;
		}
		reachable[i][i] = true;
	}
	//取 min 变成了 & 运算
	for(int k = 0; k < n; k++){
		for(int u = 0; u < n; u++){
			for(int v = 0; v < n; v++){
				reachable[u][v] = reachable[u][v] | (reachable[u][k] & reachable[k][v]);
			}
		}
	}
	if(print){
		for(int i = 0; i < n; i ++, putchar(10)){
			for(int j = 0; j < n; j++){
				printf("%d ", reachable[i][j]);
			}
		}
	}
	return reachable;
}
