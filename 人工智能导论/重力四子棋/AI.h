
#ifndef _AI_H_
#define _AI_H_

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
	double ucb_multier;
	size_t nodeCount;
	Node* nodePool;
	Timer timer;

	inline char nextPlayer(char curPlayer) {
		return COMPUTER + COMPETITOR - curPlayer;
	}
	inline bool isValid(const int x, const int y) const {
		return (x >= 0 && x < m && y >= 0 && y < n);
	}
	inline void reset() {
		memcpy(board, init_board, m * n * sizeof(int));
	}

	Node* addNode(char player);
	bool judgeWin(const int x, const int y) const ;
	bool checkCurPlayerWin(int* setX, int* setY, const int& choice, const char& player);
	void checkNextPlayerWin(int* setX, int* setY,
		const int& choice, const char& player, int* x, int* y);
	Node* selection(Node* root, vector<Node*>& path);
	int simulation(char player);
	void backPropagation(vector<Node*>& path, int result);
	void initSimulationTop();

public:
	AI(const int _m, const int _n, const int* top, int** _board,
		const int lastX, const int lastY, const int noX, const int noY);
	~AI() {
		delete[] board;
		delete[] init_board;
		delete[] nodePool;
		delete[] simulationTop;
		delete[] setX;
		delete[] setY;
	}
	Point* MCST();
};

#endif