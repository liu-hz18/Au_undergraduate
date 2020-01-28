
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "util.h"

struct Vertex{
	//两个标号(d_v, delta_v)
	int prev;//顶点因为哪个顶点才得到标号，也表示标号方向(正反向)
	int addflow;//增流路径的最大增流量
	char state;//顶点状态
	void reset(){
		prev = addflow = -1;
		state = UNDISCOVERED;
	}
};

#endif
