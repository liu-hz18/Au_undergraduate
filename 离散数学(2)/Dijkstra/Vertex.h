#pragma once

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2
#define INTMAX 0x3f3f3f3f

struct Vertex{
	char state;//����״̬
	int priority;//���ȼ���
	int data;//�ڵ���
	Vertex():state(UNDISCOVERED),priority(INTMAX){}
	void reset(){
		state = UNDISCOVERED;
		priority = INTMAX;
	}
	bool operator<(Vertex const& v){
		return priority < v.priority;
	}
	bool operator==(Vertex const& v){
		return priority == v.priority;
	}
};