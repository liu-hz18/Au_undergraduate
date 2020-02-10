
#include "Graph.h"
#include "community.h"
#include "unionSet.h"

reducedNode* Graph::initReduceGraph(){//��ʼ����Ϣ�򻯵�ͼ,O(n+e)
	reducedNode* nodeVec = new reducedNode[n];
	for(int i = 0 ;i < n; i ++){
		nodeVec[i].community = i;
		for(auto& edge : edgeList[i]){
			nodeVec[i].neighbor.push_back(reducedEdge(edge.to, edge.weight));
		}
	}
	return nodeVec;
}

//��ʼ����Ⱥ��ͬʱ�õ����жȵĺ�m,O(e)
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

//����qsort��compare
int comparereducedNode(const void* x, const void* y){
	return (*(reducedNode*)x).community - (*(reducedNode*)y).community;
}

//�����ؽ�ͼO(ne)
reducedNode* newGraph(reducedNode* old, int& lastcount){
	//��community��ѹ��
	int* rank = new int[lastcount];
	//����
	qsort(old, lastcount, sizeof(reducedNode), comparereducedNode);
	int r = 0; rank[old[0].community] = 0;
	for(int i = 1; i < lastcount; i++){
		if(old[i].community != old[i-1].community)r++;
		rank[old[i].community] = r;
	}
	reducedNode* newnodeVec = new reducedNode[r+1];
	for(int i = 0; i < lastcount; i++){
		for(auto& edge : old[i].neighbor){
			if(old[i].community != old[edge.to].community){//���߲���ͬһ��Ⱥ���ͽ�Ȩ������
				int j = rank[old[i].community], to = rank[old[edge.to].community], loc = -1, count = -1;
				//����ͼ�п��Ƿ��д˱�
				for(auto& e : newnodeVec[j].neighbor){
					count++;
					if(e.to == to){loc = count; e.weight += edge.weight; break; }
				}
				if(loc == -1){//���ھͼ��±�
					newnodeVec[j].neighbor.push_back(reducedEdge(to, edge.weight));
				}
			}else{//�γ��Ի�
				int j = rank[old[i].community], loc = -1, count = -1;
				//����ͼ�п��Ƿ��д˱�
				for(auto& e : newnodeVec[j].neighbor){
					count++;
					if(e.to == j){loc = count; e.weight += edge.weight; break; }
				}
				if(loc == -1){//���ھͼ��±�
					newnodeVec[j].neighbor.push_back(reducedEdge(j, edge.weight));
				}
			}
		}
	}
	delete[] old;
	lastcount = r+1;
	return newnodeVec;
}

//����ģ���
double modularity(reducedNode* nodeVec, int count, int m){//O(e)
	double modu = 0.0;
	//����ģ���
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

//fastUnfolding(���Louvain�㷨)��Ⱥ���֣����ڵ�֮�� ���ϴ�Ȩ�ء� �ļ��Ͻ��о���, ����ģ���
unionSet* Graph::fastUnfolding(double& modu){//��Ⱥ�����㷨
	reducedNode* nodeVec = initReduceGraph();//��ʼ����ͼ�ڵ�
	unionSet* set = new unionSet(n);//Ϊ��ԭԭͼÿ���ڵ���������Ⱥ��ʹ�ò��鼯ά��
	int count = n, s = 0, lastcount = n;//��Ⱥ����(ÿ�κϲ�����һ��), ͼ�ĶȺ�(�൱��2m)
	bool flag = true;//�ж��Ƿ�����Ⱥ�ϲ��������
	while(flag){//ÿ��O(n^2+e+ne) = O(n(n+e)),n eΪ��ͼ�еĶ���ͱ�
		flag = false;
		Community* com = initCommunity(nodeVec, lastcount, s);//��ʼ����Ⱥ
		int* k_i_in = new int[lastcount];
		//����ÿ����
		for(int i = 0; i < lastcount; i ++){
			//��ÿ�������ڵ�������Ⱥ,���� k_i �� k_i_in
			memset(k_i_in, 0, lastcount * sizeof(int));
			int k_i = 0, num = 0;
			for(auto& edge : nodeVec[i].neighbor){
				k_i += edge.weight;
				if(i != edge.to)k_i_in[nodeVec[edge.to].community] += edge.weight;//�������Ի�
			}
			//�ҵ�����k_i_in
			int max = 0, id = -1;
			for(int j = 0; j < lastcount; j++){
				if(j == i)continue;
				//���ǵ����ݵľֲ��ԣ��������Ľڵ����Ϊһ�������ĸ���Ҳ�����������������������������Խ����ĵ㱻���ܵĸ���Խ��
				if(max < k_i_in[j] || (max == k_i_in[j] && (rand() % ( abs(j-i) )==0))){
					max = k_i_in[j];
					id = j;
				}
			}
			//�ж� �ѽڵ�i����ԭ����Ⱥ���Ƴ���������Ⱥid֮��� ģ��� �Ƿ�����,���Ӿͻ���Ⱥ
			//������ԭ��ֻ���ǹ��������������˸Ľ������Žⲻ�䣬������������˻�����Ž�ĸ��ʣ�������iter����
			if(id >= 0 && max >= double(k_i_in[nodeVec[i].community]) + (2.0/double(s))*\
					double(k_i*(k_i + com[id].sumTot - com[nodeVec[i].community].sumTot))+0.000001){
				flag = true;
				//printf("move %d from community %d to community %d\n", i, nodeVec[i].community, id);
				com[nodeVec[i].community].sumTot -= k_i;//�Ƴ�ԭ����Ⱥ
				com[nodeVec[i].community].sumIn -= k_i_in[nodeVec[i].community];
				nodeVec[i].community = id;//��������Ⱥ
				com[id].sumTot += k_i;
				com[id].sumIn += max;
				set->isolate(i);
				set->Union(i, id);
			}
		}
		//�ؽ�ͼ
		nodeVec = newGraph(nodeVec, lastcount);
		delete[] k_i_in;
		delete[] com;
	}
	modu = modularity(nodeVec, lastcount, s);
	return set;
}

//����fastUnfloding�����ֵ�����ѡȡ�ģ����Խ���iter�֣��Ա�ѡȡ���Ž�
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
	//Ϊԭͼÿ���ڵ����Ⱥ��ֵ
	for(int i = 0; i < n; i++){
		vertex[i].community = maxset->find(i) + 1;
	}
	return maxModu;
}
