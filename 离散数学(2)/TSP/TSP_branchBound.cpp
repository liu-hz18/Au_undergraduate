
#include "TSP.h"

//����qsort��compare
int compare(const void* x, const void* y){
    return ((Edge*)x)->weight - ((Edge*)y)->weight;
}

//��֧���編,dfs���Լӱ��жϻ�·
bool comGraph::findCircle(int edgenum, int rank, int sum){
	//�ָ�ԭ��״̬
	sum += edge[rank].weight;
	if(sum > mincost)return false;//��֦
	count[edge[rank].from] ++;
	count[edge[rank].to] ++;
	//��ջ
	if(count[edge[rank].from] > 2 || count[edge[rank].to] > 2)return false;//û�л�·
	//�ӱ���ջ
	if(edgenum+1 < n){
		for(int i = rank+1; i <= upperVertex; i++){//upperVertex���ƻ�·�ߵ�����Ͻ磬��֦
			//�ɵ������ʣ����Լ�֦
		bool flag = findCircle(edgenum+1, i, sum);
			count[edge[i].from] --;//�˻�ԭ��״̬
			count[edge[i].to] --;
			if(flag)return false;
		}
	}
	//edgenum == n,�ҵ���һ����·
	if(edgenum+1 == n){
		upperVertex = min(upperVertex, rank);
		mincost = min(mincost, sum);
		return true;
	}
	return false;
}

//�����̷�֧���編
int comGraph::TSPBranchBound(){
	assert(e == (n*(n-1))>>1);//��ȫͼ
	mincost = INT_MAX;
	upperVertex = e - 1;
	qsort(edge, e, sizeof(Edge), compare);
	//��·�п��ܲ�����ÿһ���ߣ�����Ҫ��ÿһ���߽��еݹ�
	for(int i = 0; i <= e - n; i++){
		memset(count, 0, n * sizeof(int));
		findCircle(0, i, 0);
	}
	return mincost;
}
