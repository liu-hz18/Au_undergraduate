
//获得介数中心度
#include "Graph.h"

//递归得到 from 到 to 的最短路,O(n)
//pathlist[i][j]用栈存储，和递归保持对应
void Graph::getPath(int from, int to, int**path, int i, int j){
	if(path[from][to] == from){
		pathlist[i][j].push(to); pathlist[i][j].push(from); 
		//vertex[from].betweenCentrality ++;//如果介数中心度也算自己的话
		return;
	}
	vertex[path[from][to]].betweenCentrality ++;//介数中心度++;
	//vertex[to].betweenCentrality ++;//如果介数中心度也算自己的话,本句替换上一句
	pathlist[i][j].push(to);
	getPath(from, path[from][to], path, i, j);
}

//得到介数中心度,O(n^2)*O(n) = O(n^3)
void Graph::getBetweenCent(int** distMatrix, int** path){
	for(int i = 0; i < n; i++)vertex[i].betweenCentrality = -1;
	//有向图要遍历所有i,j;
	if(isDirected){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j && distMatrix[i][j] < INT_MAX){//节点之间存在通路
					getPath(i, j, path, i, j);
				}
			}
		}
	}else{//无向图只需要遍历上三角
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(distMatrix[i][j] < INT_MAX){//节点之间存在通路
					getPath(i, j, path, i, j);
				}
			}
		}
	}
}

