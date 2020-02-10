
#include "Graph.h"

//������㷨��DFS
bool Graph::TSortOutdegree(int v, int& clock, stack<int>* S){
	vertex[v].dTime = ++clock;
	vertex[v].state = DISCOVERED;
	for(auto& iter : edgeList[v]){
		int u = iter.to;
		switch(vertex[u].state){
			case UNDISCOVERED:
				vertex[u].parent = v;
				iter.edgeType = TREE;
				if(!TSortOutdegree(u, clock, S))return false;//��u��������������������ȫͼ�����ˣ����ʷ��ز�����
				break;
			case DISCOVERED:
				iter.edgeType = BACKWARD; //һ�����ֺ���ߣ���DAG�����򲻱����룬�ʷ��ز�����
				return false;
			default:
				iter.edgeType = (vertex[v].dTime < vertex[u].dTime) ? FORWARD : CROSS;
				break;
		}
	}
	vertex[v].state = VISITED;
	S->push(v);
	return true;//v������������������
}

//��������,����DFS,O(n+e)
stack<int>* Graph::topoSortDFS(int s, bool print){
	assert(0 <= s && s < n && isDirected);
	reset();
	int clock = 0, v = s;
	stack<int>* S = new stack<int>;
	do{
		if(vertex[v].state == UNDISCOVERED && !TSortOutdegree(v, clock, S)){
			while(!S->empty())S->pop();//��ʱ����ͨͼ����DAG��ջ����֮��ֱ�ӷ���
			break;
		}
		v = (v + 1) % n;
	}while(v != s);
	//�����ӡ������, ͬʱ�õ����˱��
	if(print){
		int rank = 0;
		while(!S->empty()){
			vertex[S->top()].topoIndex = rank++;
			printf("%d ", S->top() + 1);
			S->pop();
		}
		putchar(10);
	}
	return S;//�����DAG, ��S�ڶ����Զ�������򣻷���S�ա�
}


//������㷨, Kahn.O(n+e), DAGʱ����ջ����ջ�׵�ջ����topoSort������DAG�򷵻ؿ�ջ��
stack<int>* Graph::topoSortKahn(bool print){
	assert(isDirected);
	reset();
	queue<int>* Q = new queue<int>;
	stack<int>* S = new stack<int>;
	int* indeg = new int[n];//������ȵĸ���
	//�������е㣬���Է���ͨ����Ҳ���Ա�����
	for(int i = 0; i < n; i++){
		indeg[i] = vertex[i].inDegree;
		if(indeg[i] == 0)Q->push(i);
	}
	while(!Q->empty()){
		int v = Q->front();
		Q->pop();
		S->push(v);
		for(auto& iter : edgeList[v]){
			if(--indeg[iter.to] == 0)Q->push(iter.to);
		}
	}
	stack<int>* revS = new stack<int>;
	//����ջrevS
	while(!S->empty()){
		revS->push(S->top());
		S->pop();
	}
	delete Q;
	delete S;
	delete[] indeg;
	if(revS->size() == n){
		if(print){//��ӡ��ͬʱ�õ����˱��
			int rank = 0;
			while(!revS->empty()){
				vertex[revS->top()].topoIndex = rank++;
				printf("%d ", revS->top() + 1);
				revS->pop();
			}
			putchar(10);
		}
	}else{//not a DAG
		while(!revS->empty())revS->pop();
	}
	return revS;
}
