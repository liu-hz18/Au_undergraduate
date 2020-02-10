
#include "Graph.h"

//���÷���״̬
void Graph::reset(){
	for(int i = 0;i < n;i ++){
		vertex[i].reset();
		for(auto& iter : edgeList[i]){
			iter.reset();
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
	for(auto& iter:edgeList[f]){
		if(iter.to == t)return true;
	}
	return false;
}

//��ӡ������Ϣ(�ֵ���ʽ���������python��������ÿ�е��ַ���ʹ��eval()�������ɣ������ֵ�)
void Graph::printVetex(){
	for(int i = 0; i < n; i++){
		printf("{'data':%d, 'dTime':%d, 'fTime':%d, 'parent':%d, 'inDegree':%d, 'outDegree':%d, 'priority':%d, 'state':%d, 'betCet':%d, 'cloCet':%d, 'topoRank':%d, 'earTime':%d, 'latTime':%d, 'community':%d}\n", \
			vertex[i].data+1, vertex[i].dTime, vertex[i].fTime, vertex[i].parent+1, vertex[i].inDegree, vertex[i].outDegree, vertex[i].priority,\
			vertex[i].state, vertex[i].betweenCentrality, vertex[i].closeCentrality, vertex[i].topoIndex, vertex[i].earStartTime, vertex[i].latStartTime, vertex[i].community);
	}
	putchar(10);
}

//��ӡ����Ϣ(�����������֧�����ṹ)
void Graph::printEdge(){
	for(int i = 0; i < n; i++){
		for(auto& it : edgeList[i]){
			printf("Edge(%d, %d): weight:%d Type:", i+1, it.to+1, it.weight);
			if(it.edgeType == UNETERMINED)printf("UNETERMINED\n");
			else if(it.edgeType == TREE)printf("TREE\n");
			else if(it.edgeType == CROSS)printf("FORWARD\n");
			else if(it.edgeType == BACKWARD)printf("BACKWARD\n");
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

//�ڽӱ�ת�ڽӾ���,û�������ı���Ϊ����
int** Graph::listToMatrix(){
	int** distMatrix = new int*[n];//��С�������
	for(int i = 0; i < n; i++){//��ʼ��
		distMatrix[i] = new int[n];
		for(int j = 0; j < n; j++)distMatrix[i][j] = INT_MAX;
	}
	for(int i = 0; i < n; i++){
		for(auto& iter : edgeList[i]){
			distMatrix[i][iter.to] = iter.weight;
		}
		distMatrix[i][i] = 0;
	}
	return distMatrix;
}
