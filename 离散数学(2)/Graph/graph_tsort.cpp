
#include "Graph.h"

//零出度算法，DFS
bool Graph::TSortOutdegree(int v, int& clock, stack<int>* S){
	vertex[v].dTime = ++clock;
	vertex[v].state = DISCOVERED;
	for(list<Edge>::iterator iter = edgeList[v].begin(); iter != edgeList[v].end(); iter++){
		int u = iter->to;
		switch(vertex[u].state){
			case UNDISCOVERED:
				vertex[u].parent = v;
				iter->edgeType = TREE;
				if(!TSortOutdegree(u, clock, S))return false;//若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
				break;
			case DISCOVERED:
				iter->edgeType = BACKWARD; //一旦发现后向边（非DAG），则不必深入，故返回并报告
				return false;
			default:
				iter->edgeType = (vertex[v].dTime < vertex[u].dTime) ? FORWARD : CROSS;
				break;
		}
	}
	vertex[v].state = VISITED;
	S->push(v);
	return true;//v及其后代可以拓扑排序
}

//拓扑排序,基于DFS,O(n+e)
stack<int>* Graph::topoSortDFS(int s, bool print){
	assert(0 <= s && s < n && isDirected);
	reset();
	int clock = 0, v = s;
	stack<int>* S = new stack<int>;
	do{
		if(vertex[v].state == UNDISCOVERED && !TSortOutdegree(v, clock, S)){
			while(!S->empty())S->pop();//此时该连通图不是DAG，栈弹空之后直接返回
			break;
		}
		v = (v + 1) % n;
	}while(v != s);
	//如果打印拓扑序, 同时得到拓扑编号
	if(print){
		int rank = 0;
		while(!S->empty()){
			vertex[S->top()].topoIndex = rank++;
			printf("%d ", S->top() + 1);
			S->pop();
		}
		putchar(10);
	}
	return S;//如果是DAG, 则S内顶点自顶向底排序；否则，S空。
}


//零入度算法, Kahn.O(n+e), DAG时返回栈，从栈底到栈顶是topoSort。不是DAG则返回空栈。
stack<int>* Graph::topoSortKahn(bool print){
	assert(isDirected);
	reset();
	queue<int>* Q = new queue<int>;
	stack<int>* S = new stack<int>;
	int* indeg = new int[n];//保存入度的副本
	//遍历所有点，所以非联通部分也可以遍历到
	for(int i = 0; i < n; i++){
		indeg[i] = vertex[i].inDegree;
		if(indeg[i] == 0)Q->push(i);
	}
	while(!Q->empty()){
		int v = Q->front();
		Q->pop();
		S->push(v);
		for(list<Edge>::iterator iter = edgeList[v].begin(); iter != edgeList[v].end(); iter++){
			if(--indeg[iter->to] == 0)Q->push(iter->to);
		}
	}
	stack<int>* revS = new stack<int>;
	//逆序栈revS
	while(!S->empty()){
		revS->push(S->top());
		S->pop();
	}
	delete Q;
	delete S;
	delete[] indeg;
	if(revS->size() == n){
		if(print){//打印，同时得到拓扑编号
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
