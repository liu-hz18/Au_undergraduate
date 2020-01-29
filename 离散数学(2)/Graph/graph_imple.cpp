
#include "Graph.h"

//���÷���״̬
void Graph::reset(){
	for(int i = 0;i < n;i ++){
		vertex[i].reset();
		for(list<Edge>::iterator iter = edgeList[i].begin(); iter != edgeList[i].end(); iter++){
			iter->reset();
		}
	}
}

//����ͼ�ӱߣ�ֻ��Ҫ��һ����
void Graph::insertEdge(int from, int to, int w){
	edgeList[from].push_back(Edge(to, w));
	vertex[from].outDegree ++;
	vertex[to].inDegree ++;
	e++;
	//���������ͼ
	if(!isDirected){
		edgeList[to].push_back(Edge(from, w));
	}
	//����ͼ�Ķ���ֻ��ҪinDegree + outDegree����
}

//(f, t)���ڱ�
bool Graph::existEdge(int f, int t){
	for(list<Edge>::iterator iter = edgeList[f].begin(); iter != edgeList[f].end(); iter++){
		if(iter->to == t)return true;
	}
	return false;
}

//��ӡ������Ϣ
void Graph::printVetex(){
	for(int i = 0; i < n; i++){
		printf("data:%d, dTime:%d, fTime:%d, parent:%d, inDegree:%d, outDegree:%d, priority:%d, state:%d, betCet:%d, cloCet:%d, topoRank:%d, earTime:%d, latTime:%d\n", \
			vertex[i].data+1, vertex[i].dTime, vertex[i].fTime, vertex[i].parent+1, vertex[i].inDegree, vertex[i].outDegree, vertex[i].priority,\
			vertex[i].state, vertex[i].betweenCentrality, vertex[i].closeCentrality, vertex[i].topoIndex, vertex[i].earStartTime, vertex[i].latStartTime);
	}
	putchar(10);
}
