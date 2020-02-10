
#include "vertex_PT.h"
#include "Graph.h"

//����qsort��compare
int compareNode(const void* x, const void* y){
	return (*(vertexPT*)x).rank - (*(vertexPT*)y).rank;
}

//��ÿ������(����)����������ʱ��(ͬʱҲ��v1 - vi���·������Ӧ�ȴ���֮ǰ�����й�����ɲ��ܿ�ʼ������)
void Graph::earlistStartTime(){
	vertexpt = new vertexPT[n];
	topoSortDFS(0, true);//���������
	for(int i = 0; i < n; i++)vertexpt[i].set(i, vertex[i].topoIndex, -1, -1);
	qsort(vertexpt, n, sizeof(vertexPT), compareNode);//�Զ��㰴����������
	//�ؽ�����ڽӱ� ��ȱ���to��from
	list<Edge>* indeg = new list<Edge>[n];
	for(int i = 0; i < n; i++){
		for(auto& it : edgeList[i]){
			indeg[it.to].push_back(Edge(i, it.weight));
		}
	}
	int* rank = new int[n];
	for(int i = 0; i < n; i++)rank[vertexpt[i].index] = i;
	//���·���㷨
	vertexpt[0].earStartTime = 0;
	for(int i = 1; i < n; i++){
		int max = -1;
		for(auto& it : indeg[vertexpt[i].index]){
			if(max < vertexpt[rank[it.to]].earStartTime + it.weight)max = vertexpt[rank[it.to]].earStartTime + it.weight;
		}
		vertexpt[i].earStartTime = max;
	}
	for(int i = 0; i < n; i++){
		vertex[vertexpt[i].index].earStartTime = vertexpt[i].earStartTime;
	}
	delete[] indeg;
	delete[] rank;
}

//�����ȵõ���������ʱ����ܵ��ñ�����������
//��ÿ������(����)����������ʱ��(ͬʱҲ��vi - vn���·���������������������һ�����������)
void Graph::latestStartTime(){
	int* rank = new int[n];
	for(int i = 0; i < n; i++)rank[vertexpt[i].index] = i;//������ӳ��
	vertexpt[n-1].latStartTime = vertexpt[n-1].earStartTime;
	for(int i = n-2; i >= 0; i--){
		int min = INT_MAX;
		for(auto& it : edgeList[vertexpt[i].index]){
			if(min > vertexpt[rank[it.to]].latStartTime - it.weight)min = vertexpt[rank[it.to]].latStartTime - it.weight;
		}
		vertexpt[i].latStartTime = min;
	}
	for(int i = 0; i < n; i++){
		vertex[vertexpt[i].index].latStartTime = vertexpt[i].latStartTime;
	}
	delete[] rank;
}
