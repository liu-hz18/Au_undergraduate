
#include "unionSet.h"
#include "Graph.h"

//����qsort��compare
int compare(const void* x, const void* y){
	return (*(Edge*)x).weight - (*(Edge*)y).weight;
}

//��С֧���������鼯�汾 kruskal, O(eloge),������С֧�����ı߼�
int Graph::kruskal(list<Edge>* result){
	reset();
	//�����߱�
	Edge* edge = new Edge[e];
	unionSet set(n);
	int count = 0, sum = 0;
	//����ͼ������ʽ������ͼ���ڽӱ��б���Ϊ2e������ֻ��Ҫ��һ��
	for(int i = 0; i < n; i++){
		for(auto& iter : edgeList[i]){
			if(!isDirected && iter.to <= i)continue;//��֤����ͼÿ����ֻ��һ��
			edge[count].data = i;
			edge[count].to = iter.to;
			edge[count].weight = iter.weight;
			count++;
		}
	}
	//��С���� ����
	qsort(edge, e, sizeof(Edge), compare);
	//kruskal
	for(int i = 0; i < e; i++){
		int u = edge[i].data;
		int v = edge[i].to;
		if(set.find(u) != set.find(v)){
			set.Union(u, v); //O(1)
			vertex[v].parent = u;
			result->push_back(edge[i]);
			sum += edge[i].weight;
		}
	}
	delete[] edge;
	return sum;
}
