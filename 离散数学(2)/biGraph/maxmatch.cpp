
#include "bigraph.h"

//dfs (匈牙利算法)求增广路,O(m)
bool biGraph::dfs(int u){
	for(list<Edge>::iterator it = edgelist[u].begin(); it != edgelist[u].end(); it++){
		int v = it->to;
		if(vertex[v].state == UNDISCOVERED){
			vertex[v].state = DISCOVERED;
			//如果v没有匹配或者v的匹配找到了新的匹配，则存在增广路
			if(vertex[v].match < 0 || dfs(vertex[v].match)){
				vertex[v].match = u;
				vertex[u].match = v;
				return 1;
			}
		}
	}
	return 0;
}

//求最大匹配O(mn),事实上，对于绝大部分的二分图，匈牙利算法都跑不够上限。
int biGraph::maxmatch(){
	int ans = 0;
	for(int i = 0; i < n; i++){//对X点集每一个点尝试匹配
		for(int j = 0; j < n + m; j++)vertex[j].state = UNDISCOVERED;
		if(dfs(i))ans++;//增广
	}
	return ans;
}

void biGraph::printMatch(){
	for(int i = 0; i < n; i++){
		if(vertex[i].match >= 0)printf("%d %d\n", i + 1, vertex[i].match - n + 1);
	}
}

