
#ifndef _BIGRAPH_H_
#define _BIGRAPH_H_

#include "vertex.h"
#include "edge.h"
#include "util.h"

//����ͼ��
class biGraph{
	int n, m, e;//n:X�㼯��m:Y�㼯��
	list<Edge>* edgelist;//�ڽӱ���
	Vertex* vertex;

public:
	biGraph(int _n, int _m):n(_n), m(_m), e(0), edgelist(new list<Edge>[n+m]), vertex(new Vertex[n+m]){

	}
	~biGraph(){
		delete[] edgelist;
		delete[] vertex;
	}
	//����㼯�� 0 <= f < n, 0 <= t < m 
	void addEdge(int f, int t, int w = 0){
		assert(0 <= f && f < n && 0 <= t && t < m);
		edgelist[f].push_back(Edge(n + t, w));
		edgelist[n + t].push_back(Edge(f, w));
		e ++;
	}
	
	//dfs (�������㷨)������·,O(m)
	bool dfs(int u);

	//�����ƥ��O(mn)
	int maxmatch();
	
	//��ӡƥ�����
	void printMatch();

	//���Ȩƥ������ƥ��
	//�������Դ��ͻ�㣬���Ȩƥ�伴Ϊ�����������㼯֮��ķ���Ϊ��Ȩ������Ϊ1
	//��ȫƥ�䣺��������:X�����Ӽ����ܶ��� ���� ���Ӽ��ڵ���
	
	//��ʼ����Ȩ���漴����X[i] + Y[i] >= weight[i][j],O(mn)
	void initVerWeight();

	//����dfsʵ������·���ң�u������ʼ��X�㼯,O(n)
	bool findPath(int u);

	//Kuhn-Munkres(KM)�㷨 O(n^3)
	int bestMatchKM();

	//��СȨƥ�䣬ֱ�ӶԱ�Ȩȡ������,O(n^2)
	int changeWeight();

	//����СȨƥ��
	int minMatch();

};

#endif
