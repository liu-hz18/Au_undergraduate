
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "util.h"

struct Vertex{
	//�������(d_v, delta_v)
	int prev;//������Ϊ�ĸ�����ŵõ���ţ�Ҳ��ʾ��ŷ���(������)
	int addflow;//����·�������������
	char state;//����״̬
	void reset(){
		prev = addflow = -1;
		state = UNDISCOVERED;
	}
};

#endif
