
#include "minHeap.h"
#include "Graph.h"

//����dijkstra(BFS),��Ȩ����, ��Դ��s���·,O(n^2+e)
void Graph::dijkstraBrute(int s){
	assert(0 <= s && s < n);
	reset();
	vertex[s].priority = 0;//priority����������нڵ㵽Դ�����̾���
	int source = s;
	//����n�������n-1����
	for(int i = 0;i < n;i ++){
		vertex[s].state = VISITED;
		for(list<Edge>::iterator iter = edgeList[s].begin(); iter != edgeList[s].end(); iter++){
			int j = iter->to;
			//�ɳڲ���
			if(vertex[j].state == UNDISCOVERED && vertex[j].priority > add(vertex[s].priority, iter->weight)){
				vertex[j].priority = vertex[s].priority + iter->weight;
				vertex[j].parent = s;
			}
		}
		//ѡ����һ�����ٽ��ڵ�
		for(int shortest = INT_MAX, j = 0; j < n; j++){
			if(vertex[j].state == UNDISCOVERED && shortest > vertex[j].priority){
				shortest = vertex[j].priority;
				s = j;
			}
		}
	}
	//�õ�Դ��s�Ľ������Ķ�
	for(int i = 0; i < n; i++){
		if(vertex[i].priority < INT_MAX)
			vertex[source].closeCentrality += vertex[i].priority;
	}
}
//dijkstra���Ż�(BFS),O((n+e)logn),ѡ�����ȼ���͵ĵ�����
void Graph::dijkstraHeap(int s){
	assert(0 <= s && s < n);
	reset();
	MinHeap<Vertex> H(n);
	int source = s;
	vertex[s].priority = 0;//priority����������нڵ㵽Դ�����̾���
	H.push(vertex[s]);
	while(!H.empty()){
		int u = H.pop().data;
		if(vertex[u].state == VISITED)continue;//ע��˴�������u->next�����ʣ�����u������
		vertex[u].state = VISITED;
		for(list<Edge>::iterator iter = edgeList[u].begin(); iter != edgeList[u].end(); iter++){
			int j = iter->to;
			if(vertex[j].priority > add(vertex[u].priority, iter->weight)){//�ɳ�
				vertex[j].priority = vertex[u].priority + iter->weight;
				vertex[j].parent = u;
				H.push(vertex[j]);
			}
		}
	}
	//�õ�Դ��s�Ľ������Ķ�
	for(int i = 0; i < n; i++){
		if(vertex[i].priority < INT_MAX)
			vertex[source].closeCentrality += vertex[i].priority;
	}
}
