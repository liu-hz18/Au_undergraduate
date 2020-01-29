
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "vertex.h"
#include "edge.h"
#include "vertex_PT.h"

//����ͼ��
class Graph{
private:
	int n, e;//�������ͱ���
	Vertex* vertex;//�����б�
	vertexPT* vertexpt;//PTͼ��������Ķ���
	list<Edge>* edgeList;//�ڽӱ�
	stack<int>** pathlist;//���·���Ķ�ά����������
	bool isDirected;
	
	void reset();//���÷���״̬
	
	void BFS(int v, int& clock);//����ͨ��BFS
	
	void DFS(int v, int& clock);//����ͨ��DFS
	
	bool TSortOutdegree(int v, int& clock, stack<int>* S);//������㷨��DFS
	
	void getPath(int from, int to, int**path, int i, int j);//�ݹ�õ�from��to �����·
	
	void getBetweenCent(int** distMatrix, int** path);//�õ��������Ķ�

	void printPath(int from, int to);//��ӡ������������·��

public:
	//���붥����� �� �Ƿ�������ͼ
	Graph(int _n, bool directed = true):n(_n), e(0), vertex(new Vertex[_n+1]), edgeList(new list<Edge>[_n+1]), isDirected(directed){
		pathlist = new stack<int>*[n];
		for(int i = 0; i < n; i++){ pathlist[i] = new stack<int>[n]; }//��ʼ�����·��
		for(int i = 0; i < n; i++){ vertex[i].data = i; }//��������
	}
	~Graph(){
		delete[] vertex;
		delete[] edgeList;
		for(int i = 0; i < n; i++){
			delete[] pathlist[i];
		}
		delete[] pathlist;
	}
	
	void insertEdge(int from, int to, int w = 1);//����ͼ�ӱߣ�ֻ��Ҫ��һ����
	
	bool existEdge(int f, int t);//(f, t)���ڱ�,O(n)

	void printVetex();//��ӡ������Ϣ
	
	void printEdge();//��ӡ����Ϣ

	void printSpanningTree();//�����С֧����������

	void randomGraph(int _e, int w_max = 1);//��n�������ͼ�������e����Ȩ��, ���رߺ��Ի�, ��������Ȩ��
	
	void bfs(int s);//ȫͼbfs
	
	void dfs(int s);//ȫͼdfs
	
	stack<int>* topoSortDFS(int s, bool print = false);//��������,����DFS,O(n+e)
	
	//������㷨, Kahn.O(n+e), DAGʱ����ջ����ջ�׵�ջ����topoSort������DAG�򷵻ؿ�ջ��
	stack<int>* topoSortKahn(bool print = false);

	//��ÿ������(����)����������ʱ��(ͬʱҲ��v1 - vi���·������Ӧ�ȴ���֮ǰ�����й�����ɲ��ܿ�ʼ������)
	void earlistStartTime();

	//�����ȵõ���������ʱ����ܵ��ñ�����������
	//��ÿ������(����)����������ʱ��(ͬʱҲ��vi - vn���·���������������������һ�����������)
	void latestStartTime();
	
	int primBrute(int s, list<Edge>* result);//��С֧����,����prim,O(n^2+e)
	
	int primHeap(int s, list<Edge>* result);//prim���Ż�,O((n+e)logn)
	
	//��С֧���������鼯�汾 kruskal, O(eloge),������С֧�����ı߼�
	int kruskal(list<Edge>* result);

	//����dijkstra,��Ȩ����, ��Դ��s���·,O(n^2+e)
	void dijkstraBrute(int s);
	
	void dijkstraHeap(int s);//dijkstra���Ż�,O((n+e)logn)
	
	bool** warshall(bool print = false);//��ɴ����,O(n^3)
	
	//�޸�Ȩ��·����������������·,O(n^3),�õ��������Ķ�O(n^3),���ؾ������.ͬʱ��ý������Ķ�betCet
	int** floyd(bool print = false);
	
	//��Ȩ����,�޸��� ��Դs���·, O(e)~O(ne).�����ڸ�������false.(���Կ���SPFA)����BFS���
	bool bellmanFord(int s);

	//��ý������Ķ�cloCet,��n��dijkstra �� bellmanFord, Ĭ�� û�и�Ȩ(hasNegEdge = false)
	void getCloseCet(bool hasNegEdge = false);

	void printAllminPath();//��ӡ���е��֮������·

	int countSpanningTree();//������

	int spanningTreeFromRoot(int r);//����ͼ��rΪ����Ҷ����

};

#endif

