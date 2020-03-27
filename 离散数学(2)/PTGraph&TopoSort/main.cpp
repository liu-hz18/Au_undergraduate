// PT图求关键路径与允许延误时间
//    2018011446   刘泓尊
//注意函数调用顺序不能随意调换

#include <cstdio>
#include "Graph.h"

int main(){
	int n;
	std::cin >> n;
	Graph G(n);
	G.construct();//从stdin读入数据，建图
	G.topoSortDFS(0);//从源点DFS进行拓扑排序
	G.earlistStartTime();//求最早启动时间
	G.latestStartTime();//求最晚启动时间
	printf("%d\n", G.totalTime());//输出总时间
	G.printKeyPath();//DFS输出关键路径
	G.printTime();//输出节点允许延误时间
	return 0;
}
