
#include "bigraph.h"

//���Ȩƥ������ƥ��
//�������Դ��ͻ�㣬���Ȩƥ�伴Ϊ�����������㼯֮��ķ���Ϊ��Ȩ������Ϊ1
//��ȫƥ�䣺��������:X�����Ӽ����ܶ��� ���� ���Ӽ��ڵ���
	
//��ʼ����Ȩ���漴����X[i] + Y[i] >= weight[i][j],O(mn)
void biGraph::initVerWeight(){
	//X[i]�Ǿ���ÿ�����ֵ
	for(int i = 0; i < n; i ++){
		for(list<Edge>::iterator it = edgelist[i].begin(); it != edgelist[i].end(); it++){
			vertex[i].weight = max(vertex[i].weight, it->weight);
		}
	}
	//Y[i]Ϊ0
	for(int i = 0; i < m; i ++){
		vertex[i + n].weight = 0;
	}
}

//���Ȩƥ��(KM�㷨)
//��X[i] + Y[i] == weight[i][j]Ϊ���бߣ�KM�㷨����Ϊ�����޸ĵ�Ȩ��ֱ���ҳ�һ��ȫ���ɿ��б���ɵĶ���ͼ���걸ƥ��
//����С���ǵĲ������������㷨�����ֻ��Ҫ���������С������r��һ���ҵ�ʵ�ʵ���С���ǣ�ѡ����С�ķ���Ԫ�޸Ľ�ֵ���ٴν�������������
//\sum(X[i] + Y[i])��Ϊ���Ȩ
//����dfsʵ������·���ң�u������ʼ��X�㼯
bool biGraph::findPath(int u){
	vertex[u].state = DISCOVERED;
	for(list<Edge>::iterator it = edgelist[u].begin(); it != edgelist[u].end(); it++){
		int v = it->to;
		if(vertex[v].state == DISCOVERED)continue;
		//����Ҫ��ʽ�洢����ֻ��Ҫ���㼴�ɵõ�buv,��˲��漰�Ծ���Ĳ���
		int buv = vertex[u].weight + vertex[v].weight - it->weight;
		//��X[i] + Y[i] == weight[i][j],��Ϊ���б�
		//�ȼ��ڶ�B������0Ԫ�ؽ�����С����
		if(!buv){
			vertex[v].state = DISCOVERED;
			//vertex[v].match��Ȼ����X���ϣ����Եݹ�ʼ����X�����н���
			if(vertex[v].match < 0 || findPath(vertex[v].match)){
				vertex[v].match = u;
				vertex[u].match = v;
				return 1;
			}
		//�൱�ڶԵ�v�е�ÿһ������Ԫ��������Сֵ����delta(��v�з���Ԫ��Сֵ��֮���)
		}else if(vertex[v].slack > buv){//�ɳ�
			vertex[v].slack = buv;
		}
	}
	return 0;
}

//Kuhn-Munkres�㷨,O(n^3)�����걸ƥ���µ����Ȩƥ��
int biGraph::bestMatchKM(){
	//reset();
	initVerWeight();
	//��ÿ��X����ƥ��
	for(int i = 0; i < n; i++){//O(n)
		//��ʵֻ��Y�㼯��slack����
		for(int j = 0; j < m;j ++){
			vertex[j + n].slack = INT_MAX;
		}
		//��������-�޸ĵ�Ȩ-��������...
		while(1){//O(n)
			//��������״̬(ɾ�����Ǳ��)
			for(int j = 0; j < m + n; j++){
				vertex[j].state = UNDISCOVERED;
			}
			//ʹ���������㷨������·��ֱ���ҵ�ƥ�����,������С����
			if(findPath(i))break;//O(n)
			//û���ҵ�·��,����µ�Ȩ
			//����δ����Ԫ�����ҵ���С����Ԫ
			int delta = INT_MAX;
			//���ȫ����ķ���Ԫ��Сֵ��ֻ��Ҫ��state == UNDISCOVERED(��t != 0��Ԫ������Сֵ)
			for(int j = 0; j < m; j++){
				if(vertex[j + n].state == UNDISCOVERED)delta = min(delta, vertex[j + n].slack);
			}
			//���µ�Ȩ
			//��X[i]��û�и��ǣ������X��Ȩ
			for(int j = 0; j < n; j++){
				if(vertex[j].state == DISCOVERED)vertex[j].weight -= delta;
			}
			//��Y[i]���Ѹ��ǣ������ӵ�Ȩ��ͬʱ�޸�slackֵ(�൱�ھ�����û����Ԫ��)��ʹ�������delta
			for(int j = 0; j < m; j++){
				if(vertex[j + n].state == DISCOVERED)vertex[j + n].weight += delta;
				else vertex[j + n].slack -= delta;//���еĲ��ڽ������е�y�����slackֵ����ȥd
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++){
		//��(i, vertex[i].match)��Ȩ�أ�ͬʱҲ��X[i]+Y[i]
		ans += vertex[i].weight + vertex[vertex[i].match].weight;
	}
	return ans;
}
