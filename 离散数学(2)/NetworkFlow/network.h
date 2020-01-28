
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "vertex.h"
#include "edge.h"

//这里使用邻接矩阵实现，空间较高
//但网络流一般是稀疏图，但为了更新操作实现O(1)最好使用前向星
class network{
	int n, m;
	Vertex* vertex;//顶点列表
	Edge** edgeMat;
	bool* inqueue;//spfa辅助数组
	int* distance;//最小费用流中的到源点距离
	//顶点标号状态重置
	void reset(){
		for(int i = 0; i < n; i++)
			vertex[i].reset();
	}

public:
	network(int _n):n(_n), vertex(new Vertex[n]), edgeMat(new Edge*[n]), m(0){
		for(int i = 0; i < n; i++){
			edgeMat[i] = new Edge[n];
		}
	}
	~network(){
		delete[] vertex;
		for(int i = 0; i < n; i++){
			delete[] edgeMat[i];
		}
		delete[] edgeMat;
	}

	//并没有自动补充源点和汇点，需要显式输入
	void addEdge(int from, int to, int c, int e = 0){
		edgeMat[from][to].set(c, e);
		edgeMat[to][from].set(0, -e);
		m ++;
	}
	
	//基于BFS(先标号先检查)寻找增广路，如果到达t点，一定是含边数量最短的增广路
	bool EdmondsKrap(int s, int t);
	
	//Ford-Fulkerson策略的最大流标号算法,底层使用EdmondsKrap算法,O(ne^2)
	//同时可用于求最小割
	int maxflow(int s, int t);
	
	//最小费用最大流算法，把费用看做边权，用BFS(SPFA)寻找最短的增流路径
	bool spfaEdmondsKrap(int s, int t);

	//最小费用最大流,使用SPFA,返回pair<maxflow, mincost>
	pair<int, int> minCostmaxFlow(int s, int t);

};

#endif
