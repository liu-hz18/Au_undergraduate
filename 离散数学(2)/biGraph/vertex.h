
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "util.h"

struct Vertex{
	//两个标号(d_v, delta_v)
	int match;//与之匹配的节点
	char state;//顶点状态
	int weight;//点权(界值l(xi), l(yj))
	int slack;//松弛量
	Vertex():state(UNDISCOVERED), match(-1), slack(INT_MAX){}
	void reset(){
		match = -1;
		state = UNDISCOVERED;
		slack = INT_MAX;
	}
};

#endif
