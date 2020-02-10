
#include "Graph.h"

//��ɴ����,O(n^3)
bool** Graph::warshall(bool print){
	reset();
	bool** reachable = new bool*[n];//�ɴ����
	for(int i = 0; i < n; i++){
		reachable[i] = new bool[n];
		memset(reachable[i], false, n * sizeof(bool));
	}
	//���ڽӱ�õ��ڽӾ���, ͬ������������ͼ
	for(int i = 0; i < n; i++){
		for(auto& iter : edgeList[i]){
			reachable[i][iter.to] = true;
		}
		reachable[i][i] = true;
	}
	//ȡ min ����� & ����
	for(int k = 0; k < n; k++){
		for(int u = 0; u < n; u++){
			for(int v = 0; v < n; v++){
				reachable[u][v] = reachable[u][v] | (reachable[u][k] & reachable[k][v]);
			}
		}
	}
	if(print){
		for(int i = 0; i < n; i ++, putchar(10)){
			for(int j = 0; j < n; j++){
				printf("%d ", reachable[i][j]);
			}
		}
	}
	return reachable;
}
