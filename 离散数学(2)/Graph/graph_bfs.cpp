
#include "Graph.h"

//����ͨ��BFS
void Graph::BFS(int v, int& clock){
	queue<int> Q;//��������
	vertex[v].state = DISCOVERED;
	Q.push(v);
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		vertex[v].dTime = ++clock;
		//�������г���
		for(auto& iter :edgeList[v]){
			int u = iter.to;
			if(vertex[u].state == UNDISCOVERED){
				vertex[u].state = DISCOVERED;
				Q.push(u);
				vertex[u].parent = v;
				iter.edgeType = TREE;
			}else{
				iter.edgeType = CROSS;
			}
		}
		vertex[v].state = VISITED;
	}
}

//���ڹ̶�ͼ���㷨�ӿ�
//ȫͼbfs
void Graph::bfs(int s){//��Դ��s��ʼ����bfs
	assert(0 <= s && s < n);
	reset();
	int clock = 0, v = s;
	do{
		if(vertex[v].state == UNDISCOVERED){
			BFS(v, clock);
		}
		v = (v + 1) % n;
	}while(v != s);
}
