
#pragma once

struct vertexPT{
	int index;
	int rank;
	int earStartTime;//最早启动时间
	int latStartTime;//最晚启动时间
	void set(int id, int ra, int ear, int lat){
		index = id, rank = ra, earStartTime = ear, latStartTime = lat;
	}
};
