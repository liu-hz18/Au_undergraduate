
#pragma once  //比宏定义安全！！
#include <list>
//社群类
struct Community{
	int sumIn, sumTot;//社群内部的边权和、社群与其他所有社群连线的边权和
	Community(){
		sumIn = sumTot = 0;
	}
};

//简化的边类
struct reducedEdge{
	int weight, to;
	reducedEdge(int t, int w = 0): to(t){
		weight = w;
	}
};

//简化的节点类
struct reducedNode{
	int community;//属于哪个社群
	list<reducedEdge> neighbor; //连接的边
};
