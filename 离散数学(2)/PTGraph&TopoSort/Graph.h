#pragma once
#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "Edge.h"
#include "utils.h"

using namespace std;

int compare(const void* x, const void* y){
	return (*(Vertex*)x).rank - (*(Vertex*)y).rank;
}

int compareId(const void* x, const void* y){
	return (*(Vertex*)x).index - (*(Vertex*)y).index;
}

class Graph{
	int n, e;
	Vertex* vertex;
	Vertex* vertexpt;
	list<Edge>* edgeList;


public:
	Graph(int _n): n(_n+2){
		vertex = new Vertex[n+1];
		edgeList = new list<Edge>[n+1];
		for(int i = 0; i < n; i++)vertex[i].index = i;
	}
	~Graph(){
		delete[] vertex;
		delete[] edgeList;
	}
	void construct(){//��ͼ
		string temp, line;
		stringstream ss;
		list<int>* prevList = new list<int>[n];
		getchar();
		for(int i = 0; i < n-2; i++){//�ӵ�
			getline(cin, line);
			auto strvec = split(line, " ");
			int to = stoi(strvec[0])+1;
			vertex[to].time = stoi(strvec[1]);
			if(strvec.size() == 3){
				ss.clear(); ss.str(strvec[2]);
				while(getline(ss, temp, ',')){
					prevList[to].push_back(stoi(temp)+1);
				}
			}
		}
		for(int i = 1; i < n-1; i++){//�ӱ�
			for(auto& iter: prevList[i]){
				addEdge(iter, i, vertex[iter].time);
				vertex[iter].outDegree ++;
				vertex[i].inDegree ++;
			}
		}
		for(int i = 1; i < n-1; i++){//��Դ��ͻ��
			if(vertex[i].outDegree == 0){
				addEdge(i, n-1, vertex[i].time);
				vertex[i].outDegree ++;
				vertex[n-1].inDegree ++;
			}
			if(vertex[i].inDegree == 0){
				addEdge(0, i, 0);
				vertex[i].inDegree ++;
				vertex[0].outDegree ++;
			}
		}
		delete[] prevList;
	}
	void addEdge(int from, int to, int w){
		edgeList[from].push_back(Edge(to, w));
	}
	//������㷨��DFS
	bool TsortOutDegree(int v, int& clock, stack<int>& S){
		vertex[v].dTime = ++clock;
		vertex[v].state = DISCOVERED;
		for(auto& iter: edgeList[v]){
			int u = iter.to;
			switch (vertex[u].state){
			case UNDISCOVERED:
				vertex[u].parent = v;
				if(!TsortOutDegree(u, clock, S))
					return false;
				break;
			case DISCOVERED:
				return false;
			default:
				break;
			}
		}
		vertex[v].state = VISITED;
		S.push(v);
		return true;
	}
	//�������򣬻���DFS
	stack<int> topoSortDFS(int s){
		int clock = 0, v = s;
		stack<int> S;
		do{
			if(vertex[v].state == UNDISCOVERED && !TsortOutDegree(v, clock, S)){
				while(!S.empty())S.pop();//��ʱͼ������ͨͼ��ջ���շ���
				printf("not a DAG!\n");
				exit(-1);
			}
			v = (v + 1) % n;
		}while(v != s);
		//��¼������
		int r = 0;
		while(!S.empty()){
			vertex[S.top()].rank = r++;
			S.pop();
		}
		return S;//�����DAG, ��S�ڶ����Զ�������򣻷���S�ա�
	}
	void earlistStartTime(){
		qsort(vertex, n, sizeof(Vertex), compare);
		list<Edge>* indeg = new list<Edge>[n+1];
		//�ؽ�����ڽӱ���ȱ���to��from
		for(int i = 0; i < n; i++){
			for(auto& iter: edgeList[i]){
				indeg[iter.to].push_back(Edge(i, iter.weight));
			}
		}
		int* rank = new int[n];
		for(int i = 0; i < n; i++)rank[vertex[i].index] = i;
		//���·���㷨
		vertex[0].earStartTime = 0;
		for(int i = 1; i < n; i++){
			int max = -1;
			for(auto& iter: indeg[vertex[i].index]){
				if(max < vertex[rank[iter.to]].earStartTime + iter.weight)//�ɳ�
					max = vertex[rank[iter.to]].earStartTime + iter.weight;
			}
			vertex[i].earStartTime = max;
		}
		delete[] indeg;
		delete[] rank;
	}
	void latestStartTime(){//������������ʱ��
		int* rank = new int[n];
		for(int i = 0; i < n; i++)rank[vertex[i].index] = i;
		vertex[n-1].latStartTime = vertex[n-1].earStartTime;
		for(int i = n-2; i >= 0; i--){
			int min = INTMAX;
			for(auto& iter: edgeList[vertex[i].index]){
				if(min > vertex[rank[iter.to]].latStartTime - iter.weight){//�ɳ�
					min = vertex[rank[iter.to]].latStartTime - iter.weight;
				}
			}
			vertex[i].latStartTime = min;
		}
		delete[] rank;
	}
	int totalTime(){//������ɵ���ʱ��
		return vertex[n-1].earStartTime;
	}
	void reSort(){//���ݽڵ�������
		qsort(vertex, n, sizeof(Vertex), compareId);
	}
	void printTime(){//�����������ʱ��
		reSort();
		for(int i = 1; i < n-1; i++){
			printf("%d\n", vertex[i].latStartTime - vertex[i].earStartTime);
		}
	}
	//DFS���(���)�ؼ�·��
	void printPath(int s, list<int>& path, int* rank){
		path.push_back(vertex[s].index);
		if(vertex[s].index == n-1){//������
			printf("[");
			int head = path.front(), end = path.back();//ȥ��Դ��ͻ�������
			path.pop_front(); path.pop_back();
			for(auto& v: path){
				printf("%d->", v-1);
			}
			printf("end]\n");
			path.push_front(head); path.push_back(end);
			path.pop_back();
			return;
		}
		for(auto& iter: edgeList[vertex[s].index]){
			int j = iter.to;
			if(vertex[rank[j]].nodelay() && vertex[s].earStartTime + iter.weight == vertex[rank[j]].latStartTime){
				printPath(rank[j], path, rank);
			}
		}
		path.pop_back();
	}
	void printKeyPath(){//����ؼ�·��
		int* rank = new int[n+1];
		for(int i = 0; i < n; i++)rank[vertex[i].index] = i;
		list<int> path;
		printPath(0, path, rank);
		delete[] rank;
	}
	void print(){// for debug
		for(int i = 0; i < n; i++){
			cout << vertex[i].index << ' ' << vertex[i].rank << " " << vertex[i].inDegree << ' ' << vertex[i].outDegree << ' ' << vertex[i].time;
			cout << " " << vertex[i].earStartTime << " " <<vertex[i].latStartTime << endl;
		}
		for(int i = 0; i < n; i++){
			cout << vertex[i].index << ": ";
			for(auto& iter: edgeList[i]){
				cout << "(" << iter.to << ", " << iter.weight << ") ";
			}
			cout << endl;
		}
	}
};
