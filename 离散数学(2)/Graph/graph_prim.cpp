
#include "minHeap.h"
#include "Graph.h"

//��С֧����,����prim(BFS),O(n^2+e)
int Graph::primBrute(int s, list<Edge>* result){
	assert(0 <= s && s < n);
	reset();
	int sum = 0;
	vertex[s].priority = 0;
	int u = s, shortest;
	for(int i = 0; i < n; i++){
		vertex[u].state = VISITED;
		if(u != s){
			Edge e = Edge(u, shortest); e.data = vertex[u].parent;//(v, u) 
			result->push_back(e);
			sum += shortest;
		}
		for(auto& iter :edgeList[u]){
			int j = iter.to;
			//�ɳڲ���
			if(vertex[j].state == UNDISCOVERED && vertex[j].priority > iter.weight){
				vertex[j].priority = iter.weight;
				vertex[j].parent = u;//Ϊ��ԭ���Ľṹ�������¼parent
			}
		}
		//ѡ����һ�����̿��
		shortest = INT_MAX;
		for(int j = 0; j < n; j ++){
			if(vertex[j].state == UNDISCOVERED && shortest > vertex[j].priority){
				shortest = vertex[j].priority;
				u = j;
			}
		}
	}
	return sum;
}

//prim() (BFS)���Ż�,O((n+e)logn),ѡ�� ��̵ı� ������
int Graph::primHeap(int s, list<Edge>* result){
	assert(0 <= s && s < n);
	reset();
	MinHeap<Vertex> H(n);
	int sum = 0;
	vertex[s].priority = 0;
	H.push(vertex[s]);
	//��С֧�����ı� ������TREE����
	while(!H.empty()){
		Vertex ver = H.pop();
		int u = ver.data;
		if(u != s){
			sum += ver.priority;
			Edge e = Edge(u, ver.priority); e.data = vertex[u].parent;//(v, u)
			result->push_back(e);
		}
		if(vertex[u].state == VISITED)continue;
		vertex[u].state = VISITED;
		for(auto& iter : edgeList[u]){
			int j = iter.to;
			if(vertex[j].priority > iter.weight){//�ɳ�
				vertex[j].priority = iter.weight;
				vertex[j].parent = u;//Ϊ��ԭ���Ľṹ�������¼parent
				H.push(vertex[j]);
			}
		}
	}
	return sum;
}
