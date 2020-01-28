
#include "TSP.h"

//�����̱����㷨O(n^3)���������㷨(���2:1),��ʵ���������Ž�ʮ�ֽӽ�
int comGraph::TSPCheap(){
	assert(e == (n*(n-1))>>1);//��ȫͼ
	mincost = 0;
	int count = 0;//��¼��·�еĵ����
	bool* inCircle = new bool[n];//��¼ĳ���ڲ��ڻ�·��
	memset(inCircle, false, n * sizeof(bool));
	int* next = new int[n];//��·�е�ǰ��
	int* prev = new int[n];//��·�еĺ��
	initEdgeMat();
	count++, inCircle[0] = true;//���ڵ�1���뻷·
	next[0] = prev[0] = 0;//�Ի�
	//ÿ��ѭ������һ����
	while(count < n){//O(n)
		int j, t, minweight = INT_MAX;
		//�������п��
		for(int i = 0; i < e; i++){//O(e) == O(n^2)
			int u = edge[i].from, v = edge[i].to;
			//����ǿ�ߣ��ҵ���̿��
			if(inCircle[u] && !inCircle[v] && minweight > edgeMat[u][v]){
				minweight = edgeMat[u][v];
				j = v; t = u;
			}
			if(!inCircle[u] && inCircle[v] && minweight > edgeMat[u][v]){
				minweight = edgeMat[u][v];
				j = u; t = v;
			}
		}
		inCircle[j] = true; count++;
		//����·���룬O(1)
		if(edgeMat[j][prev[t]] - edgeMat[t][prev[t]] <= edgeMat[j][next[t]] - edgeMat[t][next[t]]){
			mincost += edgeMat[j][prev[t]] + edgeMat[j][t] - edgeMat[t][prev[t]];//�޸�Ȩֵ��
			next[prev[t]] = j; prev[j] = prev[t]; next[j] = t; prev[t] = j;//�޸�ǰ����̹�ϵ
		}else{
			mincost += edgeMat[j][next[t]] + edgeMat[j][t] - edgeMat[t][next[t]];//�޸�Ȩֵ��
			prev[next[t]] = j; next[j] = next[t]; prev[j] = t; next[t] = j;//�޸�ǰ����̹�ϵ
		}
		if(count == n)break;	
	}
	releaseMat();
	delete[] next;
	delete[] prev;
	delete[] inCircle;
	return mincost;
}
	
//�Ľ��ڲ�ѭ����O(n)
//�����̱����㷨O(n^2)���������㷨(���2:1),��ʵ���������Ž�ʮ�ֽӽ�
int comGraph::TSPCheapFaster(){
	assert(e == (n*(n-1))>>1);//��ȫͼ
	mincost = 0;
	int count = 0;//��¼��·�еĵ����
	bool* inCircle = new bool[n];//��¼ĳ���ڲ��ڻ�·��
	memset(inCircle, false, n * sizeof(bool));
	int* next = new int[n];//��·�е�ǰ��
	int* prev = new int[n];//��·�еĺ��
	initEdgeMat();
	count++, inCircle[0] = true;//���ڵ�1���뻷·
	next[0] = prev[0] = 0;//�Ի�
	int k = 0;//���ע������
	//ÿ��ѭ������һ����
	while(count < n){//O(n)
		int j, minweight = INT_MAX;
		//��������k���ӵĿ��,Ѱ�Ҽ��̿��
		for(int i = 0; i < n; i++){
			if(!inCircle[i] && minweight > edgeMat[i][k]){
				minweight = edgeMat[i][k]; j = i;
			}
		}
		inCircle[j] = true; count++;
		//����·����O(1)
		if(edgeMat[j][prev[k]] - edgeMat[k][prev[k]] <= edgeMat[j][next[k]] - edgeMat[k][next[k]]){
			mincost += edgeMat[j][prev[k]] + edgeMat[j][k] - edgeMat[k][prev[k]];//�޸�Ȩֵ��
			next[prev[k]] = j; prev[j] = prev[k]; next[j] = k; prev[k] = j;//�޸�ǰ����̹�ϵ
		}else{
			mincost += edgeMat[j][next[k]] + edgeMat[j][k] - edgeMat[k][next[k]];//�޸�Ȩֵ��
			prev[next[k]] = j; next[j] = next[k]; prev[j] = k; next[k] = j;//�޸�ǰ����̹�ϵ
		}
		if(count == n)break;
		//����k,O(n)
		int mink = INT_MAX, minj = INT_MAX;
		for(int i = 0; i < n; i++){
			if(!inCircle[i]){
				if(mink > edgeMat[i][k])mink = edgeMat[i][k];
				if(minj > edgeMat[i][j])minj = edgeMat[i][j];
			}
		}
		k = mink < minj ? k : j;
	}
	releaseMat();
	delete[] next;
	delete[] prev;
	delete[] inCircle;
	return mincost;
}
