
#include "matrix.h"
#include "Graph.h"

int Graph::countSpanningTree(){//������
	Matrix<int> mat(n - 1, n - 1);//n--1�׷���
	if(!isDirected){//����ͼ
		for(int i = 0; i < n - 1; i++){
			for(auto& it : edgeList[i]){
				if(it.to < n - 1)mat.set(i+1, (it.to)+1, mat.get(i+1, (it.to)+1) - 1);
			}
			mat.set(i+1, i+1, vertex[i].inDegree + vertex[i].outDegree);
		}
	}else{//����ͼ
		for(int i = 0; i < n - 1; i++){
			for(auto& it : edgeList[i]){
				if(it.to < n - 1){//��˫���
					mat.set(i+1, (it.to)+1, mat.get(i+1, (it.to)+1) - 1);
					mat.set((it.to)+1, i+1, mat.get((it.to)+1, i+1) - 1);
				}
			}
			mat.set(i+1, i+1, vertex[i].inDegree + vertex[i].outDegree);//��һ����
		}
	}
	mat.print();
	return int(mat.det());
}

//����ͼ��rΪ����Ҷ����, root�����1��ʼ
int Graph::spanningTreeFromRoot(int r){
	assert(isDirected && r < n && 0 <= r);
	r --;
	Matrix<int> mat(n - 1, n - 1);//n--1�׷���
	for(int i = 0; i < n; i++){
		if(i == r)continue;
		if(i < r){
			for(auto& it : edgeList[i]){
				if(it.to < r)mat.set(i+1, (it.to)+1, mat.get(i+1, (it.to)+1) - 1);
				else if(it.to > r)mat.set(i+1, (it.to), mat.get(i+1, it.to) - 1);
				else if(it.to == r)continue;
			}
			mat.set(i+1, i+1, vertex[i].inDegree);
		}else if(i > r){
			for(auto& it : edgeList[i]){
				if(it.to < r)mat.set(i, (it.to)+1, mat.get(i, (it.to)+1) - 1);
				else if(it.to > r)mat.set(i, it.to, mat.get(i, it.to) - 1);
				else if(it.to == r)continue;
			}
			mat.set(i, i, vertex[i].inDegree);//Ҷ��
		}
	}
	mat.print();
	return int(mat.det());
}
