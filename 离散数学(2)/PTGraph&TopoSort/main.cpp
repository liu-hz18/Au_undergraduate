// PTͼ��ؼ�·������������ʱ��
//    2018011446   ������
//ע�⺯������˳�����������

#include <cstdio>
#include "Graph.h"

int main(){
	int n;
	std::cin >> n;
	Graph G(n);
	G.construct();//��stdin�������ݣ���ͼ
	G.topoSortDFS(0);//��Դ��DFS������������
	G.earlistStartTime();//����������ʱ��
	G.latestStartTime();//����������ʱ��
	printf("%d\n", G.totalTime());//�����ʱ��
	G.printKeyPath();//DFS����ؼ�·��
	G.printTime();//����ڵ���������ʱ��
	return 0;
}
