#include "Strategy.h"
#include "AI.h"
#include <math.h>

constexpr int direcX[4] = { 1, 1, 1, 0 };
constexpr int direcY[4] = { -1, 0, 1, 1 };

constexpr int MAX_TIME = 500000;//最大模拟次数
constexpr size_t poolSize = 1000000;//内存池大小
constexpr double constant = 0.71;//常数因子

static int M, N;//棋盘大小

AI::AI(const int _m, const int _n, const int* top, int** _board,
	const int lastX, const int lastY, const int noX, const int noY)
	:m(_m), n(_n), nodeCount(0), ucb_multier(0.0) {
	M = m, N = n;
	board = new int[m * n];
	init_board = new int[m * n];
	simulationTop = new int[n];
	setX = new int[n];
	setY = new int[n];
	int i, j, offset;
	for (i = 0; i < m; i++) {
		offset = i * n;
		for (j = 0; j < n; j++) {
			init_board[offset + j] = board[offset + j] = _board[i][j];
		}
	}
	board[noX * n + noY] = init_board[noX * n + noY] = BARRIER;
	nodePool = new Node[poolSize];
}


Node* AI::addNode(char player) {
	Node* anode = &nodePool[nodeCount++];
	anode->init(player, n);
	for (int i = 0; i < n; i++) {
		int x = m - 1;
		while (x >= 0 && board[x * n + i] != NONE) x--;
		anode->top[i] = x;
	}
	return anode;
}


bool AI::judgeWin(const int x, const int y) const{
	int dx, dy, center = board[x * n + y], count, locx, locy;
	for (int i = 0; i < 4; i++) {
		dx = direcX[i]; dy = direcY[i]; count = 1;
		for (locx = x + dx, locy = y + dy; isValid(locx, locy); locx += dx, locy += dy) {
			if (center != board[locx * n + locy]) break;
			count++;
		}
		for (locx = x - dx, locy = y - dy; isValid(locx, locy); locx -= dx, locy -= dy) {
			if (center != board[locx * n + locy]) break;
			count++;
		}
		if (count >= 4)
			return true;
	}
	return false;
}

bool AI::checkCurPlayerWin(int* setX, int* setY, const int& choice, const char& player) {
	for (int i = 0; i < choice; i++) {
		board[setX[i] * n + setY[i]] = player;
		if (judgeWin(setX[i], setY[i])) {
			return true;
		}
		board[setX[i] * n + setY[i]] = NONE;
	}
	return false;
}

void AI::checkNextPlayerWin(int* setX, int* setY, const int& choice, const char& player, int* x, int* y) {
	int nextplayer = nextPlayer(player);
	for (int i = 0; i < choice && (*x) == -1; i++) {
		board[setX[i] * n + setY[i]] = nextplayer;
		if (judgeWin(setX[i], setY[i])) {
			(*x) = setX[i];
			(*y) = setY[i];
		}
		board[setX[i] * n + setY[i]] = NONE;
	}
}

Node* AI::selection(Node* root, vector<Node*>& path) {
	Node* cur = root, *temp;
	while (1) {
		path.push_back(cur);//加入路径
		if (cur->winner > 0) {
			break;
		}
		if ((temp = cur->findWinChild()) != NULL) {
			return temp;
		}
		int expand_rank = cur->expand(n);//扩展
		if (expand_rank != -1) {//可以扩展
			int x = cur->top[expand_rank], y = expand_rank;
			board[x * n + y] = cur->player;//落子
			cur->childlist[expand_rank] = addNode(nextPlayer(cur->player));
			cur->childlist[expand_rank]->totaltime = 2;
			if (judgeWin(x, y)) {//选择过程中遇到胜利，立刻返回
				cur->childlist[expand_rank]->winner = cur->player;
				cur->childlist[expand_rank]->wintime = int(cur->player == COMPUTER) << 1;
			} else {
				cur = cur->childlist[expand_rank];
			}
			break;
		} else { //不可被扩展, 找一条向下的道路
			Node* next = NULL;
			int road_rank = cur->findRoad(ucb_multier, next);
			if (road_rank != -1) {
				int x = cur->top[road_rank];
				int y = road_rank;
				board[x * n + y] = cur->player;
				cur = next;
			} else {
				return NULL;
			}
		}
	}
	return cur;
}

void AI::initSimulationTop() {
	for (int j = 0; j < n; j++) {
		int i = m - 1;
		while (i >= 0 && board[i * n + j] != NONE) i--;
		simulationTop[j] = i;
	}
}

int AI::simulation(char player) {
	int result = 1;
	initSimulationTop();
	while (1) {
		int choice = 0;
		for (int i = 0; i < n; i++) {
			if (simulationTop[i] >= 0) {
				setX[choice] = simulationTop[i];
				setY[choice] = i;
				choice++;
			}
		}
		if (!choice) {
			return result;
		}
		if (checkCurPlayerWin(setX, setY, choice, player)) {
			return int(player == COMPUTER)<<1;
		}
		int x = -1, y = -1;
		//模拟过程中, 如果对方有必胜策略，我方就占据x, y的位置
		checkNextPlayerWin(setX, setY, choice, player, &x, &y);
		if (x == -1) {
			int r = rand() % choice;
			x = setX[r];  y = setY[r];
		}
		board[x * n + y] = player;
		if (judgeWin(x, y)) {
			return int(player == COMPUTER)<<1;
		}
		player = nextPlayer(player);
		x = m - 1;
		while (x >= 0 && board[x * n + y] != NONE)x--;
		simulationTop[y] = x;
	}
	return result;
}

void AI::backPropagation(vector<Node*>& path, int result) {
	size_t size = path.size();
	for (int i = 0; i < size; i++) {
		path[i]->wintime += result;
		path[i]->totaltime += 2;
		path[i]->update();
	}
}

Point* AI::MCST() {
	Node* root = addNode(COMPUTER);
	int t, result = 0;
	srand((unsigned)time(NULL));
	timer.start();
	for (t = 0; t < MAX_TIME; t++) {
		ucb_multier = (root->totaltime <= 1) ? 0.0 : constant * sqrt(log(root->totaltime));
		vector<Node*> path;
		Node* pos = selection(root, path);
		if (pos) {//可以扩展
			if (pos->winner > 0) { //有必胜策略，直接选择
				result = int(pos->winner == COMPUTER) << 1;
			} else if (pos->winner == -1) { //没有必胜策略，使用MC模拟
				result = simulation(pos->player);
				pos->wintime = result;
				pos->totaltime = 2;
			}
			pos->update();
		} else {//无路可走
			result = 0;
		}
		backPropagation(path, result);
		if (timer.duration() > 1.8)
			break;
		reset();
	}
	Point* p = root->giveSelection(ucb_multier);
	//printf("final: x: %d, y: %d\n", p->x, p->y);
	return p;
}
