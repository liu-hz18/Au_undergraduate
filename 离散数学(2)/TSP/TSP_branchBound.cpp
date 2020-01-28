
#include "TSP.h"

//用于qsort的compare
int compare(const void* x, const void* y){
    return ((Edge*)x)->weight - ((Edge*)y)->weight;
}

//分支定界法,dfs策略加边判断回路
bool comGraph::findCircle(int edgenum, int rank, int sum){
	//恢复原来状态
	sum += edge[rank].weight;
	if(sum > mincost)return false;//剪枝
	count[edge[rank].from] ++;
	count[edge[rank].to] ++;
	//退栈
	if(count[edge[rank].from] > 2 || count[edge[rank].to] > 2)return false;//没有回路
	//加边入栈
	if(edgenum+1 < n){
		for(int i = rank+1; i <= upperVertex; i++){//upperVertex限制回路边的最大上界，剪枝
			//由递增性质，可以剪枝
		bool flag = findCircle(edgenum+1, i, sum);
			count[edge[i].from] --;//退回原有状态
			count[edge[i].to] --;
			if(flag)return false;
		}
	}
	//edgenum == n,找到了一个回路
	if(edgenum+1 == n){
		upperVertex = min(upperVertex, rank);
		mincost = min(mincost, sum);
		return true;
	}
	return false;
}

//旅行商分支定界法,最坏O(n!),但一般远小于该复杂度
int comGraph::TSPBranchBound(){
	assert(e == (n*(n-1))>>1);//完全图
	mincost = INT_MAX;
	upperVertex = e - 1;
	qsort(edge, e, sizeof(Edge), compare);
	//回路有可能不遍历每一条边，所以要对每一条边进行递归
	for(int i = 0; i <= e - n; i++){
		memset(count, 0, n * sizeof(int));
		findCircle(0, i, 0);
	}
	return mincost;
}
