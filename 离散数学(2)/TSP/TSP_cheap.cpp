
#include "TSP.h"

//旅行商便宜算法O(n^3)——近似算法(误差2:1),但实际上与最优解十分接近
int comGraph::TSPCheap(){
	assert(e == (n*(n-1))>>1);//完全图
	mincost = 0;
	int count = 0;//记录环路中的点个数
	bool* inCircle = new bool[n];//记录某点在不在环路中
	memset(inCircle, false, n * sizeof(bool));
	int* next = new int[n];//环路中的前驱
	int* prev = new int[n];//环路中的后继
	initEdgeMat();
	count++, inCircle[0] = true;//将节点1加入环路
	next[0] = prev[0] = 0;//自环
	//每次循环加入一条边
	while(count < n){//O(n)
		int j, t, minweight = INT_MAX;
		//遍历所有跨边
		for(int i = 0; i < e; i++){//O(e) == O(n^2)
			int u = edge[i].from, v = edge[i].to;
			//如果是跨边，找到最短跨边
			if(inCircle[u] && !inCircle[v] && minweight > edgeMat[u][v]){
				minweight = edgeMat[u][v];
				j = v; t = u;
			}
			if(!inCircle[u] && inCircle[v] && minweight > edgeMat[u][v]){
				minweight = edgeMat[u][v];
				j = u; t = v;
			}
		}
		inCircle[j] = true; count++;
		//做环路插入，O(1)
		if(edgeMat[j][prev[t]] - edgeMat[t][prev[t]] <= edgeMat[j][next[t]] - edgeMat[t][next[t]]){
			mincost += edgeMat[j][prev[t]] + edgeMat[j][t] - edgeMat[t][prev[t]];//修改权值和
			next[prev[t]] = j; prev[j] = prev[t]; next[j] = t; prev[t] = j;//修改前驱后继关系
		}else{
			mincost += edgeMat[j][next[t]] + edgeMat[j][t] - edgeMat[t][next[t]];//修改权值和
			prev[next[t]] = j; next[j] = next[t]; prev[j] = t; next[t] = j;//修改前驱后继关系
		}
		if(count == n)break;	
	}
	releaseMat();
	delete[] next;
	delete[] prev;
	delete[] inCircle;
	return mincost;
}
	
//改进内层循环到O(n)
//旅行商便宜算法O(n^2)——近似算法(误差2:1),但实际上与最优解十分接近
int comGraph::TSPCheapFaster(){
	assert(e == (n*(n-1))>>1);//完全图
	mincost = 0;
	int count = 0;//记录环路中的点个数
	bool* inCircle = new bool[n];//记录某点在不在环路中
	memset(inCircle, false, n * sizeof(bool));
	int* next = new int[n];//环路中的前驱
	int* prev = new int[n];//环路中的后继
	initEdgeMat();
	count++, inCircle[0] = true;//将节点1加入环路
	next[0] = prev[0] = 0;//自环
	int k = 0;//标记注意力点
	//每次循环加入一条边
	while(count < n){//O(n)
		int j, minweight = INT_MAX;
		//遍历所有k连接的跨边,寻找极短跨边
		for(int i = 0; i < n; i++){
			if(!inCircle[i] && minweight > edgeMat[i][k]){
				minweight = edgeMat[i][k]; j = i;
			}
		}
		inCircle[j] = true; count++;
		//做环路插入O(1)
		if(edgeMat[j][prev[k]] - edgeMat[k][prev[k]] <= edgeMat[j][next[k]] - edgeMat[k][next[k]]){
			mincost += edgeMat[j][prev[k]] + edgeMat[j][k] - edgeMat[k][prev[k]];//修改权值和
			next[prev[k]] = j; prev[j] = prev[k]; next[j] = k; prev[k] = j;//修改前驱后继关系
		}else{
			mincost += edgeMat[j][next[k]] + edgeMat[j][k] - edgeMat[k][next[k]];//修改权值和
			prev[next[k]] = j; next[j] = next[k]; prev[j] = k; next[k] = j;//修改前驱后继关系
		}
		if(count == n)break;
		//更新k,O(n)
		int mink = INT_MAX, minj = INT_MAX;
		for(int i = 0; i < n; i++){
			if(!inCircle[i]){
				if(mink > edgeMat[i][k])mink = edgeMat[i][k];
				if(minj > edgeMat[i][j])minj = edgeMat[i][j];
			}
		}
		k = mink < minj ? k : j;
	}
	releaseMat();
	delete[] next;
	delete[] prev;
	delete[] inCircle;
	return mincost;
}
