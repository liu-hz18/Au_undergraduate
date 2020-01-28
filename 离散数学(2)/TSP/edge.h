
#ifndef _EDGE_H_
#define _EDGE_H_

//±ß
struct Edge{
	int from, to;
	int weight;
	void set(int f, int t, int w){
		from = f;
		to = t;
		weight = w;
	}
};

#endif
