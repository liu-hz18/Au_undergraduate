
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "vertex.h"
#include "edge.h"
#include "vertex_PT.h"

//有向图类
class Graph{
private:
	int n, e;//顶点数和边数
	Vertex* vertex;//顶点列表
	vertexPT* vertexpt;//PT图用于排序的顶点
	list<Edge>* edgeList;//邻接表
	stack<int>** pathlist;//最短路径的二维矩阵套链表
	bool isDirected;
	
	void reset();//重置访问状态
	
	void BFS(int v, int& clock);//单连通域BFS
	
	void DFS(int v, int& clock);//单连通域DFS
	
	bool TSortOutdegree(int v, int& clock, stack<int>* S);//零出度算法，DFS
	
	void getPath(int from, int to, int**path, int i, int j);//递归得到from到to 的最短路
	
	void getBetweenCent(int** distMatrix, int** path);//得到介数中心度

	void printPath(int from, int to);//打印任意两点间最短路径

public:
	//输入顶点个数 和 是否是有向图
	Graph(int _n, bool directed = true):n(_n), e(0), vertex(new Vertex[_n+1]), edgeList(new list<Edge>[_n+1]), isDirected(directed){
		pathlist = new stack<int>*[n];
		for(int i = 0; i < n; i++){ pathlist[i] = new stack<int>[n]; }//初始化最短路径
		for(int i = 0; i < n; i++){ vertex[i].data = i; }//设置索引
	}
	~Graph(){
		delete[] vertex;
		delete[] edgeList;
		for(int i = 0; i < n; i++){
			delete[] pathlist[i];
		}
		delete[] pathlist;
	}
	
	void insertEdge(int from, int to, int w = 1);//有向图加边，只需要加一个边
	
	bool existEdge(int f, int t);//(f, t)存在边,O(n)

	void printVetex();//打印顶点信息
	
	void printEdge();//打印边信息

	void printSpanningTree();//输出最小支撑树的树边

	void randomGraph(int _e, int w_max = 1);//对n个顶点的图随机插入e条正权边, 无重边和自环, 有正整数权重
	
	void bfs(int s);//全图bfs
	
	void dfs(int s);//全图dfs
	
	stack<int>* topoSortDFS(int s, bool print = false);//拓扑排序,基于DFS,O(n+e)
	
	//零入度算法, Kahn.O(n+e), DAG时返回栈，从栈底到栈顶是topoSort。不是DAG则返回空栈。
	stack<int>* topoSortKahn(bool print = false);

	//求每个顶点(工序)的最早启动时间(同时也是v1 - vi的最长路径，即应等待其之前的所有工序都完成才能开始本工序)
	void earlistStartTime();

	//必须先得到最早启动时间才能调用本函数！！！
	//求每个顶点(工序)的最晚启动时间(同时也是vi - vn的最长路径，即不能再晚，否则最后一道工序会延误)
	void latestStartTime();
	
	int primBrute(int s, list<Edge>* result);//最小支撑树,朴素prim,O(n^2+e)
	
	int primHeap(int s, list<Edge>* result);//prim堆优化,O((n+e)logn)
	
	//最小支撑树，并查集版本 kruskal, O(eloge),返回最小支撑树的边集
	int kruskal(list<Edge>* result);

	//朴素dijkstra,正权矩阵, 单源点s最短路,O(n^2+e)
	void dijkstraBrute(int s);
	
	void dijkstraHeap(int s);//dijkstra堆优化,O((n+e)logn)
	
	bool** warshall(bool print = false);//求可达矩阵,O(n^3)
	
	//无负权回路，求任意两点间最短路,O(n^3),得到介数中心度O(n^3),返回距离矩阵.同时获得介数中心度betCet
	int** floyd(bool print = false);
	
	//边权任意,无负环 单源s最短路, O(e)~O(ne).若存在负环返回false.(可以看作SPFA)基于BFS框架
	bool bellmanFord(int s);

	//获得紧密中心度cloCet,跑n次dijkstra 或 bellmanFord, 默认 没有负权(hasNegEdge = false)
	void getCloseCet(bool hasNegEdge = false);

	void printAllminPath();//打印所有点对之间的最短路

	int countSpanningTree();//树计数

	int spanningTreeFromRoot(int r);//有向图以r为根的叶向树

};

#endif

