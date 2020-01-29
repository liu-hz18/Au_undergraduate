
#include <stdio.h>
#include <string.h>
#include "Graph.h"

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	//无向图
	//Graph* G = new Graph(n, /*isDirect =*/ false);
	//有向图
	Graph* G = new Graph(n, /*isDirect =*/ true);
	int f, t, w;
	
	//手动加边
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &f, &t, &w);
		f--, t--;//如果序从1开始
		G->insertEdge(f, t, w);
	}
	
	//生成随机图
	//G->randomGraph(m, /*edge =*/ 10);
	
	//bfs测试
	//G->bfs(/*s =*/0);//可以任选一个[0, n)的点进行bfs
	
	//dfs测试
	//G->dfs(/*s =*/0);
	
	//拓扑排序测试
	//G->topoSortDFS(/*s =*/ 0, /* print =*/ true);
	//G->earlistStartTime();
	//G->latestStartTime();
	//G->printVetex();
	//G->topoSortKahn(/* print =*/ true);
	
	//dijktra测试
	//G->dijkstraBrute(/*s =*/ 0);
	//G->printVetex();
	//G->dijkstraHeap(/*s =*/ 0);
	//G->printVetex();
	//获得紧密中心度
	//G->getCloseCet(/*hasNegEdge =*/ false);

	//prim 测试
	//list<Edge>* treeList = new list<Edge>;
	//printf("%d\n", G->primBrute(/*root =*/ 0, treeList));
	//G->printVetex();

	//treeList->clear();
	//printf("%d\n", G->primHeap(/*root =*/ 0, treeList));
	//G->printVetex();

	//kruskal测试
	//printf("%d\n", G->kruskal(treeList));
	//G->printVetex();

	//bellman-Ford测试
	//G->bellmanFord(/*s =*/0);
	//G->printVetex();

	//warshall测试
	//G->warshall(/* print =*/ true);

	//floyd测试，同时获得介数中心度
	//G->floyd(/*print =*/ true);
	//G->printVetex();//获得介数中心度
	//G->printAllminPath();//打印所有点对之间的最短路径

	//树计数测试
	//printf("spanning tree number:%d\n", G->countSpanningTree());
	//有向图的根数，序从1开始
	//printf("%d\n", G->spanningTreeFromRoot(/* root=*/1));

	delete G;
	return 0;
}
