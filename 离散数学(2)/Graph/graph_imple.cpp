
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

//��ӡ����Ϣ(�����������֧�����ṹ)
void Graph::printEdge(){
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator it = edgeList[i].begin(); it != edgeList[i].end(); it++){
			printf("Edge(%d, %d): weight:%d Type:", i, it->to, it->weight);
			if(it->edgeType == UNETERMINED)printf("UNETERMINED\n");
			else if(it->edgeType == TREE)printf("TREE\n");
			else if(it->edgeType == CROSS)printf("FORWARD\n");
			else if(it->edgeType == BACKWARD)printf("BACKWARD\n");
		}
	}
	putchar(10);
}

//�����С֧��������
void Graph::printSpanningTree(){
	for(int i = 0; i < n; i++){
		printf("TREE EDGE:(%d, %d)\n", vertex[i].parent, i);
	}
}
