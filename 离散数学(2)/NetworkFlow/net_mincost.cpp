
#include "util.h"
#include "network.h"

//最小费用最大流算法，把费用看做边权，用BFS(SPFA)寻找最短的增流路径
bool network::spfaEdmondsKrap(int s, int t){
	assert(0 <= s && s < n && 0 <= t && t < n);
	reset();
	queue<int> Q;
	memset(inqueue, false, n * sizeof(bool));
	//memset()不会用整数填充指定的内存区域,而是用单个字节填充.赋值为最大不能使用memset()
	for(int i = 0; i < n; i++){distance[i] = INT_MAX;}
	vertex[s].state = DISCOVERED;
	vertex[s].prev = 0;
	vertex[s].addflow = INT_MAX;
	Q.push(s);
	inqueue[s] = true;
	distance[s] = 0;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		inqueue[u] = false;
		for(int v = 0; v < n; v++){
			//存在正向边(u, v)
			Edge e1 = edgeMat[u][v];
			if(e1.flow > INT_MIN){
				if(vertex[v].state == UNDISCOVERED && distance[v] > distance[u] + e1.expense && e1.cap > e1.flow){
					vertex[v].state = DISCOVERED;
					vertex[v].prev = u;
					vertex[v].addflow = min(vertex[u].addflow, e1.cap - e1.flow);
					distance[v] = distance[u] + e1.expense;
					if(!inqueue[v]){ Q.push(v); inqueue[v] = true; }
				}
			}
		}
		vertex[u].state = VISITED;
		if(vertex[t].state != UNDISCOVERED)break;//直到找到增流路径
	}
	if(vertex[t].state == UNDISCOVERED /*|| vertex[t].addflow <= 0*/)return false;
	return true;
}


//最小费用最大流,使用SPFA,返回pair<maxflow, mincost>
pair<int, int> network::minCostmaxFlow(int s, int t){
	inqueue = new bool[n];
	distance = new int[n];
	int mincost = 0, maxflow = 0;
	//标号和增流过程
	while(spfaEdmondsKrap(s, t)){//标号过程，直到没有找到增流路径
		//增流过程
		int v = t, alpha = vertex[t].addflow;//汇点可改进量
		maxflow += alpha;
		//为保证每边的查找是O(1)的，应该使用邻接矩阵
		while(1){
			int u = vertex[v].prev;
			edgeMat[u][v].flow += alpha;
			edgeMat[v][u].flow -= alpha;
			mincost += alpha * edgeMat[u][v].expense;
			if(u == s)break;//直到源点s
			v = u;
		}
	}
	delete[] distance;
	delete[] inqueue;
	return pair<int, int>(maxflow, mincost);
}

