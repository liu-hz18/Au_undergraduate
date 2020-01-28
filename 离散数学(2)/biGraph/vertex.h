
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "util.h"

struct Vertex{
	//�������(d_v, delta_v)
	int match;//��֮ƥ��Ľڵ�
	char state;//����״̬
	int weight;//��Ȩ(��ֵl(xi), l(yj))
	int slack;//�ɳ���
	Vertex():state(UNDISCOVERED), match(-1), slack(INT_MAX){}
	void reset(){
		match = -1;
		state = UNDISCOVERED;
		slack = INT_MAX;
	}
};

#endif
