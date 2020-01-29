
//��ý������Ķ�
#include "Graph.h"

//�ݹ�õ� from �� to �����·,O(n)
//pathlist[i][j]��ջ�洢���͵ݹ鱣�ֶ�Ӧ
void Graph::getPath(int from, int to, int**path, int i, int j){
	if(path[from][to] == from){
		pathlist[i][j].push(to); pathlist[i][j].push(from); 
		//vertex[from].betweenCentrality ++;//����������Ķ�Ҳ���Լ��Ļ�
		return;
	}
	vertex[path[from][to]].betweenCentrality ++;//�������Ķ�++;
	//vertex[to].betweenCentrality ++;//����������Ķ�Ҳ���Լ��Ļ�,�����滻��һ��
	pathlist[i][j].push(to);
	getPath(from, path[from][to], path, i, j);
}

//�õ��������Ķ�,O(n^2)*O(n) = O(n^3)
void Graph::getBetweenCent(int** distMatrix, int** path){
	for(int i = 0; i < n; i++)vertex[i].betweenCentrality = -1;
	//����ͼҪ��������i,j;
	if(isDirected){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j && distMatrix[i][j] < INT_MAX){//�ڵ�֮�����ͨ·
					getPath(i, j, path, i, j);
				}
			}
		}
	}else{//����ͼֻ��Ҫ����������
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(distMatrix[i][j] < INT_MAX){//�ڵ�֮�����ͨ·
					getPath(i, j, path, i, j);
				}
			}
		}
	}
}

