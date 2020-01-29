
#include "Graph.h"

//��ӡ��from ��to �����·
void Graph::printPath(int from, int to){
	assert(0 <= from && from < n && 0 <= to && to < n && from != to);
	printf("min path from (%d) to (%d): ", from+1, to+1);
	stack<int> temp = pathlist[from][to];//���渱��
	while(!temp.empty()){ printf("%d ", temp.top()+1); temp.pop(); }
	putchar(10);
}

//��ӡ���е��֮������·
void Graph::printAllminPath(){
	if(isDirected){//����ͼ
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j)printPath(i, j);
			}
		}
	}else{//����ͼ
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				printPath(i, j);
			}
		}
	}
}