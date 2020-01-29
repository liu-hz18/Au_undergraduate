
#include "matrix.h"
#include "Graph.h"

int Graph::countSpanningTree(){//树计数
	Matrix<int> mat(n - 1, n - 1);//n--1阶方阵
	if(!isDirected){//无向图
		for(int i = 0; i < n - 1; i++){
			for(list<Edge>::iterator it = edgeList[i].begin(); it != edgeList[i].end(); it++){
				if(it->to < n - 1)mat.set(i+1, (it->to)+1, mat.get(i+1, (it->to)+1) - 1);
			}
			mat.set(i+1, i+1, vertex[i].inDegree + vertex[i].outDegree);
		}
	}else{//有向图
		for(int i = 0; i < n - 1; i++){
			for(list<Edge>::iterator it = edgeList[i].begin(); it != edgeList[i].end(); it++){
				if(it->to < n - 1){//加双向边
					mat.set(i+1, (it->to)+1, mat.get(i+1, (it->to)+1) - 1);
					mat.set((it->to)+1, i+1, mat.get((it->to)+1, i+1) - 1);
				}
			}
			mat.set(i+1, i+1, vertex[i].inDegree + vertex[i].outDegree);//任一方向
		}
	}
	mat.print();
	return int(mat.det());
}

//有向图以r为根的叶向树, root的序从1开始
int Graph::spanningTreeFromRoot(int r){
	assert(isDirected && r < n && 0 <= r);
	r --;
	Matrix<int> mat(n - 1, n - 1);//n--1阶方阵
	for(int i = 0; i < n; i++){
		if(i == r)continue;
		if(i < r){
			for(list<Edge>::iterator it = edgeList[i].begin(); it != edgeList[i].end(); it++){
				if(it->to < r)mat.set(i+1, (it->to)+1, mat.get(i+1, (it->to)+1) - 1);
				else if(it->to > r)mat.set(i+1, (it->to), mat.get(i+1, it->to) - 1);
				else if(it->to == r)continue;
			}
			mat.set(i+1, i+1, vertex[i].inDegree);
		}else if(i > r){
			for(list<Edge>::iterator it = edgeList[i].begin(); it != edgeList[i].end(); it++){
				if(it->to < r)mat.set(i, (it->to)+1, mat.get(i, (it->to)+1) - 1);
				else if(it->to > r)mat.set(i, it->to, mat.get(i, it->to) - 1);
				else if(it->to == r)continue;
			}
			mat.set(i, i, vertex[i].inDegree);//叶向
		}
	}
	mat.print();
	return int(mat.det());
}
