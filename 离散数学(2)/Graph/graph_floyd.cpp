
#include "util.h"
#include "Graph.h"

//无负权回路，求任意两点间最短路,O(n^3),得到介数中心度O(n^3),返回距离矩阵
int** Graph::floyd(bool print){
	reset();
	int** distMatrix = listToMatrix();//邻接表转邻接矩阵
	//因为任一最短路径的前缀仍为最短路径，所以设置path
	int** path = new int*[n];//道路矩阵，记录最短路径上的终点的前一个点，保证递归得到其前缀
	//初始化
	for(int i = 0; i < n; i++){
		path[i] = new int[n];
		for(int j = 0; j < n; j++)path[i][j] = i;
	}
	//floyd, dp, O(n^3)
	int temp;
	for(int k = 0; k < n; k++){
		for(int u = 0; u < n; u++){
			for(int v = 0; v < n; v++){
				if(distMatrix[u][v] > (temp = add(distMatrix[u][k], distMatrix[k][v]))){//松弛
					distMatrix[u][v] = temp;
					path[u][v] = path[k][v];//记录路径
					if(!isDirected){path[v][u] = path[k][u]; distMatrix[v][u] = temp;}
				}
			}
		}
	}
	//打印结果
	if(print)for(int i = 0; i < n; i++, putchar(10))for(int j = 0; j < n; j++)
		if(distMatrix[i][j] < INT_MAX)printf(" %3d", distMatrix[i][j]);
		else printf("    ");

	//得到介数中心度，同时打印path
	getBetweenCent(distMatrix, path);
	return distMatrix;
}

