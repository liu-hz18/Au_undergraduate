
#ifndef _AI_H_
#define _AI_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Node.h"
#include "Timer.h"
#include "Point.h"
using std::vector;

class AI {
	int* board;
	int* init_board;
	int* simulationTop;
	int* setX;
	int* setY;
	int m, n;
	size_t nodeCount;
	float ucb_multier;
	Node* nodePool;
	Timer timer;

	Node* addNode(char player);
	bool isValid(const int x, const int y) const ;
	bool judgeWin(const int x, const int y) const ;
	char nextPlayer(char curPlayer);
	bool checkCurPlayerWin(int* setX, int* setY, const int& choice, const char& player);
	void checkNextPlayerWin(int* setX, int* setY,
		const int& choice, const char& player, int* x, int* y);
	Node* selection(Node* root, vector<Node*>& path);
	int simulation(char player);
	void backPropagation(vector<Node*>& path, int result);
	void reset(); 
	void initSimulationTop();

public:
	AI(const int _m, const int _n, const int* top, int** _board,
		const int lastX, const int lastY, const int noX, const int noY);
	~AI();
	Point* MCST();
};

#endif