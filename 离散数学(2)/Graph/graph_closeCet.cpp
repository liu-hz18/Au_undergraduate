
#include "Graph.h"

//获得紧密中心度cloCet,跑n次dijkstra 或 bellmanFord
void Graph::getCloseCet(bool hasNegEdge){
	for(int i = 0; i < n; i++)vertex[i].closeCentrality = -1;
	if(!hasNegEdge){
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//初始化
			dijkstraHeap(i);//使用dijkstra O(n(n+e)logn)
		}
	}else{
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//初始化
			bellmanFord(i);//使用bellmanFord, O(n^2e)
		}
	}
}
