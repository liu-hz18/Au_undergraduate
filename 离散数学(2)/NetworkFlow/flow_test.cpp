
#include <stdio.h>
#include <utility>
#include "network.h"

int main(){
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	//如果序从1开始
	s--;t--;
	network net(n);
	while(m --){
		int from, to, cap, cost;
		//scanf("%d%d%d", &from, &to, &cap);
		//net.addEdge(from, to, cap);
		//注意顺序
		scanf("%d%d%d%d", &from, &to, &cap, &cost);
		from--, to--;
		net.addEdge(from, to, cap, cost);
	}
	//printf("maxflow: %d\n", net.maxflow(s, t));
	pair<int, int> flowcost = net.minCostmaxFlow(s, t);
	//printf("maxflow: %d mincost: %d\n", flowcost.first, flowcost.second);
	printf("%d %d\n", flowcost.first, flowcost.second);
	return 0;
}
