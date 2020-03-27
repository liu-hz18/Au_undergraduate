#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <stack>
#include "Edge.h"
#include "Vertex.h"
#include "Heap.h"

using namespace std;

class Graph{
	int n, e;
	int* next;//�����:A
	int* rear;//�����:B
	int* weight;//��Ȩ��:C
	Vertex* vertex;
	list<Edge>* edgelist;//ͼ���ڽӱ��ʾ
	int** path;//��¼·��
	int** minPath;//·�����ֵ

public:
	Graph(int _n, int _e): n(_n), e(_e), vertex(new Vertex[_n+1]), edgelist(new list<Edge>[_n+1]){
		next = new int[n+1];
		rear = new int[e];
		weight = new int[e];
		for(int i = 0; i < n; i++){
			vertex[i].data = i;//��ʼ�����
		}
		path = new int*[n];
		for(int i = 0; i < n; i++){
			path[i] = new int[n];
			memset(path[i], -1, n * sizeof(int));
		}
		minPath = new int*[n];
		for(int i = 0; i < n; i++){
			minPath[i] = new int[n];
			memset(minPath[i], -1, n * sizeof(int));
		}
	}
	~Graph(){
		delete[] vertex;
		delete[] edgelist;
		delete[] next;
		delete[] rear;
		delete[] weight;
		for(int i = 0; i < n; i++){
			delete[] path[i];
			delete[] minPath[i];
		}
		delete[] path;
		delete[] minPath;
	}
	void insertEdge(int from, int to, int w = 1){
		edgelist[from].push_back(Edge(to, w));
	}
	void reset(){
		for(int i = 0; i < n; i++){
			vertex[i].reset();
		}
	}
	void init(){//����������ڽ�����
		for(int i = 0; i <= n; i++)
			scanf("%d", &next[i]);
		for(int i = 0; i < e; i++)
			scanf("%d", &rear[i]);
		for(int i = 0; i < e; i++)
			scanf("%d", &weight[i]);
		for(int i = 0; i < n; i++){
			for(int j = next[i]; j < next[i+1]; j++){
				insertEdge(i, rear[j], weight[j]);
			}
		}
	}
	void dijkstraHeap(int s){//��Դ���·�����Ż�����ͬʱ��¼·��
		reset();
		MinHeap<Vertex> H(n);
		int source = s;
		vertex[s].priority = 0;
		H.push(vertex[s]);
		while(!H.empty()){
			int u = H.pop().data;
			if(vertex[u].state == VISITED)continue;
			vertex[u].state = VISITED;
			for(auto& iter: edgelist[u]){
				int j = iter.to;
				if(vertex[j].priority > vertex[u].priority + iter.weight){//�ɳ�
					vertex[j].priority = vertex[u].priority + iter.weight;
					H.push(vertex[j]);
					path[s][j] = u;//��¼���·ǰ���ڵ�
				}
			}
		}
		for(int i = 0; i < n; i++){//��¼���·��ֵ
			minPath[s][i] = vertex[i].priority;
		}
	}
	void runDijkstraFull(){//��n���ڵ���dikjkstra
		for(int i = 0; i < n; i++){
			dijkstraHeap(i);
		}
	}
	void query(int from, int to){//���·�� �� ���·������
		stack<int> s;
		s.push(to);
		int end = to;
		while(from != end){
			s.push(path[from][end]);
			end = path[from][end];
			if(end < 0)break;
		}
		if(s.top() >= 0){
			cout << "[" << s.top();
			s.pop();
			while(!s.empty()){
				cout << "->" << s.top();
				s.pop();
			}
			cout << " " << minPath[from][to] << "]" << endl;
			return;
		}
		cout << "NO PATH" << endl;
	}
	void print(){//DEBUG���
		for(int i = 0; i < n; i++){
			cout << vertex[i].priority <<  " " ;
		}
		putchar('\n');
	}
};
