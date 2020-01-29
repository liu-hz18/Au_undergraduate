
#include "Graph.h"

//打印从from 到to 的最短路
void Graph::printPath(int from, int to){
	assert(0 <= from && from < n && 0 <= to && to < n && from != to);
	printf("min path from (%d) to (%d): ", from+1, to+1);
	stack<int> temp = pathlist[from][to];//保存副本
	while(!temp.empty()){ printf("%d ", temp.top()+1); temp.pop(); }
	putchar(10);
}

//打印所有点对之间的最短路
void Graph::printAllminPath(){
	if(isDirected){//有向图
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j)printPath(i, j);
			}
		}
	}else{//无向图
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				printPath(i, j);
			}
		}
	}
}