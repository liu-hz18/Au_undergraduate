
#include "TSP.h"

//初始化邻接矩阵
void comGraph::initEdgeMat(){
	if(edgeMat == NULL){
		edgeMat = new int*[n];
		for(int i = 0; i < n; i++){
			edgeMat[i] = new int[n];
			edgeMat[i][i] = 0;
		}
	}
	for(int i = 0; i < e; i++){
		edgeMat[edge[i].from][edge[i].to] = edge[i].weight;
		edgeMat[edge[i].to][edge[i].from] = edge[i].weight;
	}
}

//释放邻接矩阵
void comGraph::releaseMat(){
	for(int i = 0; i < n; i++){
		delete[] edgeMat[i];
	}
	delete[] edgeMat;
	edgeMat = NULL;	
}
