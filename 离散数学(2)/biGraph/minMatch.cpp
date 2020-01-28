
#include "bigraph.h"


//最小权匹配，直接对边权取补即可,O(n^2)
int biGraph::changeWeight(){
	int delta = INT_MAX;
	//找到所有边权的最大值
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			delta = min(delta, it->weight);
		}
	}
	delta ++;
	//对边权求delta的补，转换为最大权匹配
	for(int i = 0; i < n; i++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			it->weight = delta - it->weight;
		}
	}
	return delta;
}

	//求最小权匹配
int biGraph::minMatch(){
	int d = changeWeight();
	int maxmatch = bestMatchKM();
	return n * d - maxmatch;
}
