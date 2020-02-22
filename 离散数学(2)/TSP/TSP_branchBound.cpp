
#include "TSP.h"
#include <list>
#include <iostream>
using namespace std;

//用于qsort的compare
int compare(const void* x, const void* y){
	return ((Edge*)x)->weight - ((Edge*)y)->weight;
}

list<Edge> S;

//分支定界法,dfs策略加边判断回路
bool comGraph::findCircle(int edgenum, int rank, int sum){
	//恢复原来状态
	sum += edge[rank].weight;
	if(sum > mincost)return false;//剪枝
	if(count[edge[rank].from] > 1 || count[edge[rank].to] > 1)return false;//没有回路,退栈
	count[edge[rank].from] ++, count[edge[rank].to] ++, S.push_back(edge[rank]);
	//加边入栈
	if(edgenum+1 < n){
		for(int i = rank+1; i <= upperVertex; i++){//upperVertex限制回路边的最大上界，剪枝
			//由递增性质，可以剪枝
			bool flag = findCircle(edgenum+1, i, sum);
			if(flag){
				S.pop_back(), count[edge[rank].from]--, count[edge[rank].to]--;//退栈
				return false;
			}
		}
	}
	//edgenum == n,找到了一个回路
	if(edgenum+1 == n){
		upperVertex = min(upperVertex, rank);
		mincost = min(mincost, sum);
		for(auto& edge : S){
			cout<<'('<<edge.from+1<<','<<edge.to+1<<')'<<' ';//输出可行解
		}
		cout<<mincost<<endl;
		count[edge[rank].from]--, count[edge[rank].to]--, S.pop_back();
		return true;
	}
	count[edge[rank].from]-- ,count[edge[rank].to] --, S.pop_back();
	return false;
}

//旅行商分支定界法
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
