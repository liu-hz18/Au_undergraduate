
#include "bigraph.h"

//最大权匹配或最佳匹配
//可以添加源点和汇点，最大权匹配即为最大费用流，点集之间的费用为边权，容量为1
//完全匹配：霍尔定理:X任意子集的总度数 大于 该子集节点数
	
//初始化点权，随即便有X[i] + Y[i] >= weight[i][j],O(mn)
void biGraph::initVerWeight(){
	//X[i]是矩阵每行最大值
	for(int i = 0; i < n; i ++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			vertex[i].weight = max(vertex[i].weight, it->weight);
		}
	}
	//Y[i]为0
	for(int i = 0; i < m; i ++){
		vertex[i + n].weight = 0;
	}
}

//最大权匹配(KM算法)
//称X[i] + Y[i] == weight[i][j]为可行边，KM算法流程为不断修改点权，直到找出一个全部由可行边组成的二分图的完备匹配
//求最小覆盖的操作由匈牙利算法求出，只需要对求出的最小覆盖数r进一步找到实际的最小覆盖，选择最小的非零元修改界值，再次进行匈牙利即可
//\sum(X[i] + Y[i])即为最大权
//基于dfs实现增广路查找，u总是起始于X点集
bool biGraph::findPath(int u){
	vertex[u].state = DISCOVERED;
	for(list<Edge>::iterator it = edgelist[u].begin(); it != edgelist[u].end(); it++){
		int v = it->to;
		if(vertex[v].state == DISCOVERED)continue;
		//不需要显式存储矩阵，只需要计算即可得到buv,因此不涉及对矩阵的操作
		int buv = vertex[u].weight + vertex[v].weight - it->weight;
		//若X[i] + Y[i] == weight[i][j],则为可行边
		//等价于对B矩阵中0元素进行最小覆盖
		if(!buv){
			vertex[v].state = DISCOVERED;
			//vertex[v].match仍然属于X集合，所以递归始终在X集合中进行
			if(vertex[v].match < 0 || findPath(vertex[v].match)){
				vertex[v].match = u;
				vertex[u].match = v;
				return 1;
			}
		//相当于对第v列的每一个非零元，求其最小值，即delta(第v列非零元最小值随之完成)
		}else if(vertex[v].slack > buv){//松弛
			vertex[v].slack = buv;
		}
	}
	return 0;
}

//Kuhn-Munkres算法,O(n^3)，求完备匹配下的最大权匹配
int biGraph::bestMatchKM(){
	//reset();
	initVerWeight();
	//对每个X进行匹配
	for(int i = 0; i < n; i++){//O(n)
		//其实只有Y点集的slack有用
		for(int j = 0; j < m;j ++){
			vertex[j + n].slack = INT_MAX;
		}
		//尝试增广-修改点权-尝试增广...
		while(1){//O(n)
			//重置搜索状态(删除覆盖标记)
			for(int j = 0; j < m + n; j++){
				vertex[j].state = UNDISCOVERED;
			}
			//使用匈牙利算法，查找路径直至找到匹配策略,即求最小覆盖
			if(findPath(i))break;//O(n)
			//没有找到路径,则更新点权
			//先在未覆盖元素中找到最小非零元
			int delta = INT_MAX;
			//求出全矩阵的非零元最小值，只需要对state == UNDISCOVERED(即t != 0的元素求最小值)
			for(int j = 0; j < m; j++){
				if(vertex[j + n].state == UNDISCOVERED)delta = min(delta, vertex[j + n].slack);
			}
			//更新点权
			//若X[i]行没有覆盖，则减少X点权
			for(int j = 0; j < n; j++){
				if(vertex[j].state == DISCOVERED)vertex[j].weight -= delta;
			}
			//若Y[i]行已覆盖，则增加点权。同时修改slack值(相当于矩阵中没覆盖元素)，使其均减少delta
			for(int j = 0; j < m; j++){
				if(vertex[j + n].state == DISCOVERED)vertex[j + n].weight += delta;
				else vertex[j + n].slack -= delta;//所有的不在交错树中的y顶点的slack值都减去d
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++){
		//边(i, vertex[i].match)的权重，同时也是X[i]+Y[i]
		ans += vertex[i].weight + vertex[vertex[i].match].weight;
	}
	return ans;
}
