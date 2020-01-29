
#include "util.h"
#include "Graph.h"

//��n�������ͼ�������e����Ȩ��, ���رߺ��Ի�, ��������Ȩ��(Ĭ�϶�ȡ1), ֻ�п�ͼ���Ե���
void Graph::randomGraph(int _e, int w_max){
	assert(_e > 0 && _e < (n*(n-1))>>1 && e == 0);
	srand(unsigned(time(NULL)));
	while(e < _e){
		int i = dice(n), j = dice(n);
		while(i == j){i = dice(n);j = dice(n);}//i != j
		if(!existEdge(i, j)){	
			insertEdge(i, j, 1 + dice(w_max));
		}
	}
}
