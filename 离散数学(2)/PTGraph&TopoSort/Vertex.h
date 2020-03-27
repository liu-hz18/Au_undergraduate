#pragma once

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

#define INTMAX 0x3f3f3f3f

class Vertex{
public:
	int time;
	int dTime, parent;
	char state;
	int index, rank, earStartTime, latStartTime;
	int outDegree, inDegree;
	Vertex(): state(UNDISCOVERED), earStartTime(-1), latStartTime(-2){
		outDegree = inDegree = time = 0;
	}
	~Vertex(){}
	bool nodelay()const{
		return earStartTime == latStartTime;
	}
	bool operator<(Vertex const& v){
		return rank < v.rank;
	}
	bool operator>(Vertex const& v){
		return rank > v.rank;
	}
	bool operator==(Vertex const& v){
		return rank == v.rank;
	}
};
