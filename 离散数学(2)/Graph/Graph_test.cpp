
#include <stdio.h>
#include <string.h>
#include "Graph.h"

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	//����ͼ
	//Graph* G = new Graph(n, /*isDirect =*/ false);
	//����ͼ
	Graph* G = new Graph(n, /*isDirect =*/ true);
	int f, t, w;
	
	//�ֶ��ӱ�
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &f, &t, &w);
		f--, t--;//������1��ʼ
		G->insertEdge(f, t, w);
	}
	
	//�������ͼ
	//G->randomGraph(m, /*edge =*/ 10);
	
	//bfs����
	//G->bfs(/*s =*/0);//������ѡһ��[0, n)�ĵ����bfs
	
	//dfs����
	//G->dfs(/*s =*/0);
	
	//�����������
	//G->topoSortDFS(/*s =*/ 0, /* print =*/ true);
	//G->earlistStartTime();
	//G->latestStartTime();
	//G->printVetex();
	//G->topoSortKahn(/* print =*/ true);
	
	//dijktra����
	//G->dijkstraBrute(/*s =*/ 0);
	//G->printVetex();
	//G->dijkstraHeap(/*s =*/ 0);
	//G->printVetex();
	//��ý������Ķ�
	//G->getCloseCet(/*hasNegEdge =*/ false);

	//prim ����
	//list<Edge>* treeList = new list<Edge>;
	//printf("%d\n", G->primBrute(/*root =*/ 0, treeList));
	//G->printVetex();

	//treeList->clear();
	//printf("%d\n", G->primHeap(/*root =*/ 0, treeList));
	//G->printVetex();

	//kruskal����
	//printf("%d\n", G->kruskal(treeList));
	//G->printVetex();

	//bellman-Ford����
	//G->bellmanFord(/*s =*/0);
	//G->printVetex();

	//warshall����
	//G->warshall(/* print =*/ true);

	//floyd���ԣ�ͬʱ��ý������Ķ�
	//G->floyd(/*print =*/ true);
	//G->printVetex();//��ý������Ķ�
	//G->printAllminPath();//��ӡ���е��֮������·��

	//����������
	//printf("spanning tree number:%d\n", G->countSpanningTree());
	//����ͼ�ĸ��������1��ʼ
	//printf("%d\n", G->spanningTreeFromRoot(/* root=*/1));

	delete G;
	return 0;
}
