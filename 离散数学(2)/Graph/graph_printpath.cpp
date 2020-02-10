
#include "Graph.h"

//��ӡ��from ��to �����·
void Graph::printPath(int from, int to, int** mat){
	assert(0 <= from && from < n && 0 <= to && to < n && from != to);
	printf("min path from (%d) to (%d): ", from+1, to+1);
	stack<int> temp = pathlist[from][to];//���渱��
	int v = from;
	list<int> weight;
	while(!temp.empty()){
		int u = temp.top();
		weight.push_back(mat[v][u]);
		printf("%d ", u+1); temp.pop();
		v = u;//(v,u) ��Ȩ
	}
	//��ӡ���·���ϵı�Ȩ
	printf(", edge weight: ");
	for(auto it = ++weight.begin(); it != weight.end(); it++){
		printf("%d ", *it);
	}
	putchar(10);
}

//��ӡ���е��֮������·
void Graph::printAllminPath(){
	//�����Ҫ���Ȩ�أ���Ҫ�ٴ��ڽӱ�ת�ڽӾ���
	int** mat = listToMatrix();
	if(isDirected){//����ͼ
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j)printPath(i, j, mat);
			}
		}
	}else{//����ͼ
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				printPath(i, j, mat);
			}
		}
	}
}

