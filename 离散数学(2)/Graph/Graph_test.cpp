
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

	//生成随机图, 随机图并不具备鲜明的群体性特征，不适合作为输入样例
	//G->randomGraph(m, /*weight_max =*/ 1);
	//G->printEdge();
	
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


	//最短树算法，注意！！使用Prim算法可以找出以v_i为根的最短树，但不一定是总权最短的树，因为可以以其他节点为根
	//prim 测试
	list<Edge>* treeList = new list<Edge>;
	//printf("%d\n", G->primBrute(/*root =*/ 0, treeList));
	//G->printVetex();
	//G->printEdge();
	//G->printSpanningTree(treeList);

	//treeList->clear();
	//printf("%d\n", G->primHeap(/*root =*/ 1-1, treeList));
	//G->printVetex();
	//G->printSpanningTree(treeList);

	//Kruskal可以实现以全局最短树的寻找，因为该算法以边为单位。(不一定只有一个树根！！也就是可以存在反边)
	//kruskal测试
	printf("%d\n", G->kruskal(treeList));
	G->printVetex();
	G->printSpanningTree(treeList);

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

	//社群发现测试, 对于群体性特征不明显的图，可以加大迭代次数
	//printf("modularity:%f \n", G->communityDetecting(/*iter=*/32, /*thread_num=*/4));
	//G->printVetex();

	delete G;
	return 0;
}
