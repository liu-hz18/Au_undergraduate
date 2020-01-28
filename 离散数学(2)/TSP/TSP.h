
#ifndef _TSP_H_
#define _TSP_H_

#include "edge.h"
#include "util.h"

//旅行商是完全图，所以可以使用邻接矩阵代表
class comGraph{
	int n, e;//顶点数和边数
	Edge* edge;//边集
	int* count;//标记顶点出现个数
	int mincost;
	int upperVertex;
	int** edgeMat;//邻接矩阵

public:
	comGraph(int _n):n(_n), e(0){
		edge = new Edge[(n*(n-1))>>1];
		count = new int[n];
		mincost = INT_MAX;
		edgeMat = NULL;
	}
	~comGraph(){
		delete[] edge;
		delete[] count;
	}
	void addEdge(int f, int t, int w){
		assert(0 <= f && f < n && 0 <= t && t < n && 0 < w);
		edge[e++].set(f, t, w);
	}
	//分支定界法,dfs策略加边判断回路
	bool findCircle(int edgenum, int rank, int sum);
	//旅行商分支定界法
	int TSPBranchBound();

	//初始化邻接矩阵
	void initEdgeMat();
	//释放邻接矩阵
	void releaseMat();

	//旅行商便宜算法O(n^3)——近似算法(误差2:1),但实际上与最优解十分接近
	int TSPCheap();
	//改进内层循环到O(n)
	//旅行商便宜算法O(n^2)——近似算法(误差2:1),但实际上与最优解十分接近
	int TSPCheapFaster();

	//用两点间最短路算法也可以实现2:1近似

};

#endif