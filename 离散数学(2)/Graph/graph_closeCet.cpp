
#include "Graph.h"

//��ý������Ķ�cloCet,��n��dijkstra �� bellmanFord
void Graph::getCloseCet(bool hasNegEdge){
	for(int i = 0; i < n; i++)vertex[i].closeCentrality = -1;
	if(!hasNegEdge){
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//��ʼ��
			dijkstraHeap(i);//ʹ��dijkstra O(n(n+e)logn)
		}
	}else{
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//��ʼ��
			bellmanFord(i);//ʹ��bellmanFord, O(n^2e)
		}
	}
}
