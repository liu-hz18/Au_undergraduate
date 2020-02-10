
#include "Graph.h"

//重置访问状态
void Graph::reset(){
	for(int i = 0;i < n;i ++){
		vertex[i].reset();
		for(auto& iter : edgeList[i]){
			iter.reset();
		}
	}
}

//有向图加边，只需要加一个边
void Graph::insertEdge(int from, int to, int w){
	edgeList[from].push_back(Edge(to, w));
	vertex[from].outDegree ++;
	vertex[to].inDegree ++;
	e++;
	//如果是无向图
	if(!isDirected){
		edgeList[to].push_back(Edge(from, w));
	}
	//无向图的度数只需要inDegree + outDegree即可
}

//(f, t)存在边
bool Graph::existEdge(int f, int t){
	for(auto& iter:edgeList[f]){
		if(iter.to == t)return true;
	}
	return false;
}

//打印顶点信息(字典形式输出，便于python解析，对每行的字符串使用eval()函数即可，返回字典)
void Graph::printVetex(){
	for(int i = 0; i < n; i++){
		printf("{'data':%d, 'dTime':%d, 'fTime':%d, 'parent':%d, 'inDegree':%d, 'outDegree':%d, 'priority':%d, 'state':%d, 'betCet':%d, 'cloCet':%d, 'topoRank':%d, 'earTime':%d, 'latTime':%d, 'community':%d}\n", \
			vertex[i].data+1, vertex[i].dTime, vertex[i].fTime, vertex[i].parent+1, vertex[i].inDegree, vertex[i].outDegree, vertex[i].priority,\
			vertex[i].state, vertex[i].betweenCentrality, vertex[i].closeCentrality, vertex[i].topoIndex, vertex[i].earStartTime, vertex[i].latStartTime, vertex[i].community);
	}
	putchar(10);
}

//打印边信息(可以用于输出支撑树结构)
void Graph::printEdge(){
	for(int i = 0; i < n; i++){
		for(auto& it : edgeList[i]){
			printf("Edge(%d, %d): weight:%d Type:", i+1, it.to+1, it.weight);
			if(it.edgeType == UNETERMINED)printf("UNETERMINED\n");
			else if(it.edgeType == TREE)printf("TREE\n");
			else if(it.edgeType == CROSS)printf("FORWARD\n");
			else if(it.edgeType == BACKWARD)printf("BACKWARD\n");
		}
	}
	putchar(10);
}

//输出最小支撑树树边
void Graph::printSpanningTree(){
	for(int i = 0; i < n; i++){
		printf("TREE EDGE:(%d, %d)\n", vertex[i].parent, i);
	}
}

//邻接表转邻接矩阵,没有相连的边则为无穷
int** Graph::listToMatrix(){
	int** distMatrix = new int*[n];//最小距离矩阵
	for(int i = 0; i < n; i++){//初始化
		distMatrix[i] = new int[n];
		for(int j = 0; j < n; j++)distMatrix[i][j] = INT_MAX;
	}
	for(int i = 0; i < n; i++){
		for(auto& iter : edgeList[i]){
			distMatrix[i][iter.to] = iter.weight;
		}
		distMatrix[i][i] = 0;
	}
	return distMatrix;
}
