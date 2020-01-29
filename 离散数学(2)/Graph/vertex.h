
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "macro.h"

//������
struct Vertex{
	int data;//������
	int dTime, fTime;
	int inDegree, outDegree;
	int priority;//���ȼ���
	int parent;//�������еĸ���
	char state;//����״̬
	int betweenCentrality, closeCentrality;//�������Ķ� �� �������Ķ�
	int topoIndex;//���������rank
	int earStartTime, latStartTime;//��������ʱ�����������ʱ��
	Vertex():inDegree(0), outDegree(0), state(UNDISCOVERED), 
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX),
		betweenCentrality(0), closeCentrality(0), topoIndex(-1){}
	void reset(){
		dTime = fTime = parent = topoIndex = -1;
		state = UNDISCOVERED;
		priority = INT_MAX;
	}
	//���ȼ��Ƚ���
	bool operator<(Vertex const& v){
		return priority < v.priority;
	}
	bool operator==(Vertex const& v){
		return priority == v.priority;
	}
};

#endif