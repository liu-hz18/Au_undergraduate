
#include "util.h"
#include "Graph.h"

//对n个顶点的图随机插入e条正权边, 无重边和自环, 有正整数权重(默认都取1), 只有空图可以调用
void Graph::randomGraph(int _e, int w_max){
	assert(_e > 0 && _e < (n*(n-1))>>1 && e == 0);
	srand(unsigned(time(NULL)));
	while(e < _e){
		int i = dice(n), j = dice(n);
		while(i == j){i = dice(n);j = dice(n);}//i != j
		if(!existEdge(i, j)){	
			insertEdge(i, j, 1 + dice(w_max));
		}
	}
}
