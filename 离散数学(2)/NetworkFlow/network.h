
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "vertex.h"
#include "edge.h"

//����ʹ���ڽӾ���ʵ�֣��ռ�ϸ�
//��������һ����ϡ��ͼ����Ϊ�˸��²���ʵ��O(1)���ʹ��ǰ����
class network{
	int n, m;
	Vertex* vertex;//�����б�
	Edge** edgeMat;
	bool* inqueue;//spfa��������
	int* distance;//��С�������еĵ�Դ�����
	//������״̬����
	void reset(){
		for(int i = 0; i < n; i++)
			vertex[i].reset();
	}

public:
	network(int _n):n(_n), vertex(new Vertex[n]), edgeMat(new Edge*[n]), m(0){
		for(int i = 0; i < n; i++){
			edgeMat[i] = new Edge[n];
		}
	}
	~network(){
		delete[] vertex;
		for(int i = 0; i < n; i++){
			delete[] edgeMat[i];
		}
		delete[] edgeMat;
	}

	//��û���Զ�����Դ��ͻ�㣬��Ҫ��ʽ����
	void addEdge(int from, int to, int c, int e = 0){
		edgeMat[from][to].set(c, e);
		edgeMat[to][from].set(0, -e);
		m ++;
	}
	
	//����BFS(�ȱ���ȼ��)Ѱ������·���������t�㣬һ���Ǻ���������̵�����·
	bool EdmondsKrap(int s, int t);
	
	//Ford-Fulkerson���Ե����������㷨,�ײ�ʹ��EdmondsKrap�㷨,O(ne^2)
	//ͬʱ����������С��
	int maxflow(int s, int t);
	
	//��С����������㷨���ѷ��ÿ�����Ȩ����BFS(SPFA)Ѱ����̵�����·��
	bool spfaEdmondsKrap(int s, int t);

	//��С���������,ʹ��SPFA,����pair<maxflow, mincost>
	pair<int, int> minCostmaxFlow(int s, int t);

};

#endif
