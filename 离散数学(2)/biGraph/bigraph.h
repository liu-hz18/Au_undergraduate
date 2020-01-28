
#ifndef _BIGRAPH_H_
#define _BIGRAPH_H_

#include "vertex.h"
#include "edge.h"
#include "util.h"

//二分图类
class biGraph{
	int n, m, e;//n:X点集，m:Y点集，
	list<Edge>* edgelist;//邻接表储存
	Vertex* vertex;

public:
	biGraph(int _n, int _m):n(_n), m(_m), e(0), edgelist(new list<Edge>[n+m]), vertex(new Vertex[n+m]){

	}
	~biGraph(){
		delete[] edgelist;
		delete[] vertex;
	}
	//加入点集是 0 <= f < n, 0 <= t < m 
	void addEdge(int f, int t, int w = 0){
		assert(0 <= f && f < n && 0 <= t && t < m);
		edgelist[f].push_back(Edge(n + t, w));
		edgelist[n + t].push_back(Edge(f, w));
		e ++;
	}
	
	//dfs (匈牙利算法)求增广路,O(m)
	bool dfs(int u);

	//求最大匹配O(mn)
	int maxmatch();
	
	//打印匹配情况
	void printMatch();

	//最大权匹配或最佳匹配
	//可以添加源点和汇点，最大权匹配即为最大费用流，点集之间的费用为边权，容量为1
	//完全匹配：霍尔定理:X任意子集的总度数 大于 该子集节点数
	
	//初始化点权，随即便有X[i] + Y[i] >= weight[i][j],O(mn)
	void initVerWeight();

	//基于dfs实现增广路查找，u总是起始于X点集,O(n)
	bool findPath(int u);

	//Kuhn-Munkres(KM)算法 O(n^3)
	int bestMatchKM();

	//最小权匹配，直接对边权取补即可,O(n^2)
	int changeWeight();

	//求最小权匹配
	int minMatch();

};

#endif
