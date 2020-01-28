
#include "util.h"
#include "network.h"

//��С����������㷨���ѷ��ÿ�����Ȩ����BFS(SPFA)Ѱ����̵�����·��
bool network::spfaEdmondsKrap(int s, int t){
	assert(0 <= s && s < n && 0 <= t && t < n);
	reset();
	queue<int> Q;
	memset(inqueue, false, n * sizeof(bool));
	//memset()�������������ָ�����ڴ�����,�����õ����ֽ����.��ֵΪ�����ʹ��memset()
	for(int i = 0; i < n; i++){distance[i] = INT_MAX;}
	vertex[s].state = DISCOVERED;
	vertex[s].prev = 0;
	vertex[s].addflow = INT_MAX;
	Q.push(s);
	inqueue[s] = true;
	distance[s] = 0;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		inqueue[u] = false;
		for(int v = 0; v < n; v++){
			//���������(u, v)
			Edge e1 = edgeMat[u][v];
			if(e1.flow > INT_MIN){
				if(vertex[v].state == UNDISCOVERED && distance[v] > distance[u] + e1.expense && e1.cap > e1.flow){
					vertex[v].state = DISCOVERED;
					vertex[v].prev = u;
					vertex[v].addflow = min(vertex[u].addflow, e1.cap - e1.flow);
					distance[v] = distance[u] + e1.expense;
					if(!inqueue[v]){ Q.push(v); inqueue[v] = true; }
				}
			}
		}
		vertex[u].state = VISITED;
		if(vertex[t].state != UNDISCOVERED)break;//ֱ���ҵ�����·��
	}
	if(vertex[t].state == UNDISCOVERED /*|| vertex[t].addflow <= 0*/)return false;
	return true;
}


//��С���������,ʹ��SPFA,����pair<maxflow, mincost>
pair<int, int> network::minCostmaxFlow(int s, int t){
	inqueue = new bool[n];
	distance = new int[n];
	int mincost = 0, maxflow = 0;
	//��ź���������
	while(spfaEdmondsKrap(s, t)){//��Ź��̣�ֱ��û���ҵ�����·��
		//��������
		int v = t, alpha = vertex[t].addflow;//���ɸĽ���
		maxflow += alpha;
		//Ϊ��֤ÿ�ߵĲ�����O(1)�ģ�Ӧ��ʹ���ڽӾ���
		while(1){
			int u = vertex[v].prev;
			edgeMat[u][v].flow += alpha;
			edgeMat[v][u].flow -= alpha;
			mincost += alpha * edgeMat[u][v].expense;
			if(u == s)break;//ֱ��Դ��s
			v = u;
		}
	}
	delete[] distance;
	delete[] inqueue;
	return pair<int, int>(maxflow, mincost);
}

