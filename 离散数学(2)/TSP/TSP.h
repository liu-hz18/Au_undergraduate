
#ifndef _TSP_H_
#define _TSP_H_

#include "edge.h"
#include "util.h"

//����������ȫͼ�����Կ���ʹ���ڽӾ������
class comGraph{
	int n, e;//�������ͱ���
	Edge* edge;//�߼�
	int* count;//��Ƕ�����ָ���
	int mincost;
	int upperVertex;
	int** edgeMat;//�ڽӾ���

public:
	comGraph(int _n):n(_n), e(0){
		edge = new Edge[(n*(n-1))>>1];
		count = new int[n];
		mincost = INT_MAX;
		edgeMat = NULL;
	}
	~comGraph(){
		delete[] edge;
		delete[] count;
	}
	void addEdge(int f, int t, int w){
		assert(0 <= f && f < n && 0 <= t && t < n && 0 < w);
		edge[e++].set(f, t, w);
	}
	//��֧���編,dfs���Լӱ��жϻ�·
	bool findCircle(int edgenum, int rank, int sum);
	//�����̷�֧���編
	int TSPBranchBound();

	//��ʼ���ڽӾ���
	void initEdgeMat();
	//�ͷ��ڽӾ���
	void releaseMat();

	//�����̱����㷨O(n^3)���������㷨(���2:1),��ʵ���������Ž�ʮ�ֽӽ�
	int TSPCheap();
	//�Ľ��ڲ�ѭ����O(n)
	//�����̱����㷨O(n^2)���������㷨(���2:1),��ʵ���������Ž�ʮ�ֽӽ�
	int TSPCheapFaster();

	//����������·�㷨Ҳ����ʵ��2:1����

};

#endif