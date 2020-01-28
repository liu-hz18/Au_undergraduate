
#include "bigraph.h"

//dfs (�������㷨)������·,O(m)
bool biGraph::dfs(int u){
	for(list<Edge>::iterator it = edgelist[u].begin(); it != edgelist[u].end(); it++){
		int v = it->to;
		if(vertex[v].state == UNDISCOVERED){
			vertex[v].state = DISCOVERED;
			//���vû��ƥ�����v��ƥ���ҵ����µ�ƥ�䣬���������·
			if(vertex[v].match < 0 || dfs(vertex[v].match)){
				vertex[v].match = u;
				vertex[u].match = v;
				return 1;
			}
		}
	}
	return 0;
}

//�����ƥ��O(mn),��ʵ�ϣ����ھ��󲿷ֵĶ���ͼ���������㷨���ܲ������ޡ�
int biGraph::maxmatch(){
	int ans = 0;
	for(int i = 0; i < n; i++){//��X�㼯ÿһ���㳢��ƥ��
		for(int j = 0; j < n + m; j++)vertex[j].state = UNDISCOVERED;
		if(dfs(i))ans++;//����
	}
	return ans;
}

void biGraph::printMatch(){
	for(int i = 0; i < n; i++){
		if(vertex[i].match >= 0)printf("%d %d\n", i + 1, vertex[i].match - n + 1);
	}
}

