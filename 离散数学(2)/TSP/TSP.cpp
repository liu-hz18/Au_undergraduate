
#include "TSP.h"

int main(){
	int n;
	scanf("%d", &n);
	comGraph G(n);
	int e = (n * (n - 1)) >> 1;
	for(int i = 0; i < e; i++){
		int f, t, w;
		scanf("%d%d%d", &f, &t, &w);
		f--, t--;//如果序从1开始
		G.addEdge(f, t, w);
	}
	printf("%d\n", G.TSPBranchBound());
	printf("%d\n", G.TSPCheap());
	printf("%d\n", G.TSPCheapFaster());
	return 0;
}
