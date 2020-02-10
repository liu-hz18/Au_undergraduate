
#include "Graph.h"
#include "community.h"
#include "unionSet.h"

reducedNode* Graph::initReduceGraph(){//初始化信息简化的图,O(n+e)
	reducedNode* nodeVec = new reducedNode[n];
	for(int i = 0 ;i < n; i ++){
		nodeVec[i].community = i;
		for(auto& edge : edgeList[i]){
			nodeVec[i].neighbor.push_back(reducedEdge(edge.to, edge.weight));
		}
	}
	return nodeVec;
}

//初始化社群，同时得到所有度的和m,O(e)
Community* initCommunity(reducedNode* nodeVec, int n, int& m){
	Community* com = new Community[n];
	m = 0;
	for(int i = 0; i < n; i++){
		for(auto& edge : nodeVec[i].neighbor){
			com[i].sumTot += edge.weight;
		}
		m += com[i].sumTot;
		nodeVec[i].community = i;
	}
	return com;
}

//用于qsort的compare
int comparereducedNode(const void* x, const void* y){
	return (*(reducedNode*)x).community - (*(reducedNode*)y).community;
}

//缩点重建图O(ne)
reducedNode* newGraph(reducedNode* old, int& lastcount){
	//对community作压缩
	int* rank = new int[lastcount];
	//排序
	qsort(old, lastcount, sizeof(reducedNode), comparereducedNode);
	int r = 0; rank[old[0].community] = 0;
	for(int i = 1; i < lastcount; i++){
		if(old[i].community != old[i-1].community)r++;
		rank[old[i].community] = r;
	}
	reducedNode* newnodeVec = new reducedNode[r+1];
	for(int i = 0; i < lastcount; i++){
		for(auto& edge : old[i].neighbor){
			if(old[i].community != old[edge.to].community){//两者不在同一社群，就将权重增加
				int j = rank[old[i].community], to = rank[old[edge.to].community], loc = -1, count = -1;
				//在新图中看是否有此边
				for(auto& e : newnodeVec[j].neighbor){
					count++;
					if(e.to == to){loc = count; e.weight += edge.weight; break; }
				}
				if(loc == -1){//不在就加新边
					newnodeVec[j].neighbor.push_back(reducedEdge(to, edge.weight));
				}
			}else{//形成自环
				int j = rank[old[i].community], loc = -1, count = -1;
				//在新图中看是否有此边
				for(auto& e : newnodeVec[j].neighbor){
					count++;
					if(e.to == j){loc = count; e.weight += edge.weight; break; }
				}
				if(loc == -1){//不在就加新边
					newnodeVec[j].neighbor.push_back(reducedEdge(j, edge.weight));
				}
			}
		}
	}
	delete[] old;
	lastcount = r+1;
	return newnodeVec;
}

//计算模块度
double modularity(reducedNode* nodeVec, int count, int m){//O(e)
	double modu = 0.0;
	//计算模块度
	for(int i = 0; i < count; i++){
		int sumin = 0, sumtot = 0;
		for(auto& edge : nodeVec[i].neighbor){
			if(i == edge.to)sumin += edge.weight;
			sumtot += edge.weight;
		}
		modu += sumin / double(m) - (sumtot / double(m)) * (sumtot / double(m));
	}
	return modu;
}

//fastUnfolding(或称Louvain算法)社群发现，将节点之间 “较大权重” 的集合进行聚类, 返回模块度
unionSet* Graph::fastUnfolding(double& modu){//社群发现算法
	reducedNode* nodeVec = initReduceGraph();//初始化新图节点
	unionSet* set = new unionSet(n);//为还原原图每个节点所属的社群，使用并查集维护
	int count = n, s = 0, lastcount = n;//社群数量(每次合并减少一个), 图的度和(相当于2m)
	bool flag = true;//判断是否有社群合并情况出现
	while(flag){//每轮O(n^2+e+ne) = O(n(n+e)),n e为新图中的顶点和边
		flag = false;
		Community* com = initCommunity(nodeVec, lastcount, s);//初始化社群
		int* k_i_in = new int[lastcount];
		//遍历每个点
		for(int i = 0; i < lastcount; i ++){
			//对每个点相邻的所有社群,计算 k_i 和 k_i_in
			memset(k_i_in, 0, lastcount * sizeof(int));
			int k_i = 0, num = 0;
			for(auto& edge : nodeVec[i].neighbor){
				k_i += edge.weight;
				if(i != edge.to)k_i_in[nodeVec[edge.to].community] += edge.weight;//不包括自环
			}
			//找到最大的k_i_in
			int max = 0, id = -1;
			for(int j = 0; j < lastcount; j++){
				if(j == i)continue;
				//考虑到数据的局部性，编号相近的节点其成为一个社区的概率也更大，所以这里采用随机化方法，编号越相近的点被接受的概率越大
				if(max < k_i_in[j] || (max == k_i_in[j] && (rand() % ( abs(j-i) )==0))){
					max = k_i_in[j];
					id = j;
				}
			}
			//判断 把节点i从其原有社群中移出，加入社群id之后的 模块度 是否增加,增加就换社群
			//比论文原先只考虑孤立点的情况进行了改进，最优解不变，但极大地增加了获得最优解的概率，减少了iter轮数
			if(id >= 0 && max >= double(k_i_in[nodeVec[i].community]) + (2.0/double(s))*\
					double(k_i*(k_i + com[id].sumTot - com[nodeVec[i].community].sumTot))+0.000001){
				flag = true;
				//printf("move %d from community %d to community %d\n", i, nodeVec[i].community, id);
				com[nodeVec[i].community].sumTot -= k_i;//移出原有社群
				com[nodeVec[i].community].sumIn -= k_i_in[nodeVec[i].community];
				nodeVec[i].community = id;//加入新社群
				com[id].sumTot += k_i;
				com[id].sumIn += max;
				set->isolate(i);
				set->Union(i, id);
			}
		}
		//重建图
		nodeVec = newGraph(nodeVec, lastcount);
		delete[] k_i_in;
		delete[] com;
	}
	modu = modularity(nodeVec, lastcount, s);
	return set;
}

//由于fastUnfloding中最大值是随机选取的，所以进行iter轮，以便选取最优解
double Graph::communityDetecting(int iter){
	double maxModu = -1.0, mo;
	int k = 0;
	srand(unsigned(time(NULL)));
	unionSet* maxset = fastUnfolding(mo);
	while(k++ < iter){
		unionSet* set = fastUnfolding(mo);
		printf("iter:%d, modularity:%f\n", k, mo);
		if(maxModu < mo){
			maxModu = mo;
			delete maxset;
			maxset = set;
		}else delete set;
	}
	//为原图每个节点的社群赋值
	for(int i = 0; i < n; i++){
		vertex[i].community = maxset->find(i) + 1;
	}
	return maxModu;
}
