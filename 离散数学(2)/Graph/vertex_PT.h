
#ifndef _VERTEX_PT_H_
#define _VERTEX_PT_H_

struct vertexPT{
	int index;
	int rank;
	int earStartTime;//��������ʱ��
	int latStartTime;//��������ʱ��
	void set(int id, int ra, int ear, int lat){
		index = id, rank = ra, earStartTime = ear, latStartTime = lat;
	}
};

#endif
