
#include "util.h"
#include "Graph.h"

//�޸�Ȩ��·����������������·,O(n^3),�õ��������Ķ�O(n^3),���ؾ������
int** Graph::floyd(bool print){
	reset();
	int** distMatrix = new int*[n];//��С�������
	//��Ϊ��һ���·����ǰ׺��Ϊ���·������������path
	int** path = new int*[n];//��·���󣬼�¼���·���ϵ��յ��ǰһ���㣬��֤�ݹ�õ���ǰ׺
	//��ʼ��
	for(int i = 0; i < n; i++){
		distMatrix[i] = new int[n];
		for(int j = 0; j < n; j++)distMatrix[i][j] = INT_MAX;
		path[i] = new int[n];
		for(int j = 0; j < n; j++)path[i][j] = i;
	}
	//�ڽӱ�ת�ڽӾ���
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator iter = edgeList[i].begin(); iter != edgeList[i].end(); iter++){
			distMatrix[i][iter->to] = iter->weight;
		}
		distMatrix[i][i] = 0;
	}
	//floyd, dp, O(n^3)
	int temp;
	for(int k = 0; k < n; k++){
		for(int u = 0; u < n; u++){
			for(int v = 0; v < n; v++){
				if(distMatrix[u][v] > (temp = add(distMatrix[u][k], distMatrix[k][v]))){//�ɳ�
					distMatrix[u][v] = temp;
					path[u][v] = path[k][v];//��¼·��
					if(!isDirected){path[v][u] = path[k][u]; distMatrix[v][u] = temp;}
				}
			}
		}
	}
	//��ӡ���
	if(print)for(int i = 0; i < n; i++, putchar(10))for(int j = 0; j < n; j++)
		if(distMatrix[i][j] < INT_MAX)printf(" %3d", distMatrix[i][j]);
		else printf("    ");

	//�õ��������Ķȣ�ͬʱ��ӡpath
	getBetweenCent(distMatrix, path);
	return distMatrix;
}


