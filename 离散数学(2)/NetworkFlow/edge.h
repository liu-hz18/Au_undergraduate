
#ifndef _EDGE_H_
#define _EDGE_H_

#include "util.h"

struct Edge{
	int cap, flow, expense;//流量、容量、费用
	Edge(){flow = INT_MIN;}
	void set(int c, int e = 0){
		cap = c;
		flow = 0;
		expense = e;
	}
};

#endif
