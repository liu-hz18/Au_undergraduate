
#include "bigraph.h"


//��СȨƥ�䣬ֱ�ӶԱ�Ȩȡ������,O(n^2)
int biGraph::changeWeight(){
	int delta = INT_MAX;
	//�ҵ����б�Ȩ�����ֵ
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			delta = min(delta, it->weight);
		}
	}
	delta ++;
	//�Ա�Ȩ��delta�Ĳ���ת��Ϊ���Ȩƥ��
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			it->weight = delta - it->weight;
		}
	}
	return delta;
}

	//����СȨƥ��
int biGraph::minMatch(){
	int d = changeWeight();
	int maxmatch = bestMatchKM();
	return n * d - maxmatch;
}
