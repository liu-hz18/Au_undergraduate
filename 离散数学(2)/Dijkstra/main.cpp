
#include "Graph.h"
#include <cstdio>
using namespace std;

int main(){
	int n, e;
	scanf("%d %d", &n, &e);
	Graph G(n, e);
	G.init();
	G.runDijkstraFull();
	int m, from, to;
	scanf("%d", &m);
	while(m--){
		scanf("%d %d", &from, &to);
		G.query(from, to);
	}
	return 0;
}
