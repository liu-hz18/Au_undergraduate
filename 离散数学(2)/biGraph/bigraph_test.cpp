
#include "bigraph.h"

int main(){
	int n, m, e;
	scanf("%d%d%d", &n, &m, &e);
	
	assert(n == m);//保证可以进行最佳匹配

	//所有算法都要单独跑，没有reset();
	biGraph G(n, m);
	//最佳匹配部分,m==n,应保证存在完全匹配
	for(int i = 0; i < e; i++){
		int f, t, w;
		scanf("%d%d%d",&f, &t, &w);
		if(f > n || t > m)continue;
		f--, t--;//如果序从1开始就要-1
		G.addEdge(f, t, w);
	}
	printf("%d\n", G.bestMatchKM());
	//printf("%d\n", G.minMatch());
	
	/*
	//最大匹配部分 m n可以不等 
	for(int i = 0; i < e; i++){
		int f, t;
		scanf("%d%d", &f, &t);
		if(f > n || t > m)continue;
		f--, t--;//如果序从1开始就要-1
		G.addEdge(f, t);
	}
	printf("%d\n", G.maxmatch());
	*/

	//输出匹配情况
	G.printMatch();
	return 0;
}
