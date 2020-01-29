
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "macro.h"

//顶点类
struct Vertex{
	int data;//数据域
	int dTime, fTime;
	int inDegree, outDegree;
	int priority;//优先级数
	int parent;//遍历树中的父亲
	char state;//访问状态
	int betweenCentrality, closeCentrality;//介数中心度 和 紧密中心度
	int topoIndex;//拓扑排序的rank
	int earStartTime, latStartTime;//最早启动时间和最晚启动时间
	Vertex():inDegree(0), outDegree(0), state(UNDISCOVERED), 
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX),
		betweenCentrality(0), closeCentrality(0), topoIndex(-1){}
	void reset(){
		dTime = fTime = parent = topoIndex = -1;
		state = UNDISCOVERED;
		priority = INT_MAX;
	}
	//优先级比较器
	bool operator<(Vertex const& v){
		return priority < v.priority;
	}
	bool operator==(Vertex const& v){
		return priority == v.priority;
	}
};

#endif