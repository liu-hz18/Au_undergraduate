
#include "util.h"
#include "network.h"

//����BFS(�ȱ���ȼ��)Ѱ������·���������t�㣬һ���Ǻ���������̵�����·
bool network::EdmondsKrap(int s, int t){
	assert(0 <= s && s < n && 0 <= t && t < n);
	reset();
	queue<int> Q;
	vertex[s].state = DISCOVERED;
	vertex[s].prev = 0;
	vertex[s].addflow = INT_MAX;
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v = 0; v < n; v++){
			//���������(u, v)�����(u, v)
			Edge e1 = edgeMat[u][v];
			if(e1.flow > INT_MIN){
				if(vertex[v].state == UNDISCOVERED && e1.cap > e1.flow){
					vertex[v].state = DISCOVERED;
					vertex[v].prev = u;
					vertex[v].addflow = min(vertex[u].addflow, e1.cap - e1.flow);
					Q.push(v);
				}
			}
		}
		vertex[u].state = VISITED;
		if(vertex[t].state != UNDISCOVERED)break;//ֱ���ҵ�����·��
	}
	if(vertex[t].state == UNDISCOVERED || vertex[t].addflow <= 0)return false;
	return true;
}


//Ford-Fulkerson���Ե����������㷨,�ײ�ʹ��EdmondsKrap�㷨,O(ne^2)
//ͬʱ����������С��
int network::maxflow(int s, int t){
	int maxflow = 0;
	//��ź���������
	while(EdmondsKrap(s, t)){//��Ź��̣�ֱ��û���ҵ�����·��
		//��������
		int v = t, alpha = vertex[t].addflow;//���ɸĽ���
		maxflow += alpha;
		//Ϊ��֤ÿ�ߵĲ�����O(1)�ģ�Ӧ��ʹ���ڽӾ���
		while(1){
			int u = vertex[v].prev;
			edgeMat[u][v].flow += alpha;
			edgeMat[v][u].flow -= alpha;
			if(u == s)break;//ֱ��Դ��s
			v = u;
		}
	}
	return maxflow;
}

