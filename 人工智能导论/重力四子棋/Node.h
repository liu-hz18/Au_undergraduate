
#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <cstdlib>
#include <math.h>
#include "Point.h"
#include "utils.h"
using std::vector;

constexpr char NONE = 0;
constexpr char COMPETITOR = 1;
constexpr char COMPUTER = 2;
constexpr char BARRIER = 3;

typedef unsigned long long u64;

class AI;

class Node {
	friend class AI;
	char player, winner;
	int totaltime, wintime;
	float ucb_a, ucb_b;
	vector<int> top;
	vector<Node*> childlist;

public:
	Node() = default;
	void init(char p, int n) {
		player = p;
		winner = -1;
		totaltime = wintime = 0;
		ucb_a = ucb_b = 0.0f;
		top.resize(n);
		childlist.resize(n, NULL);
	}
	void update() {
		ucb_a = float(wintime) / float(totaltime);
		ucb_b = 2 / sqrtf(totaltime);
		if (player == COMPUTER) {
			ucb_a = 1.0f - ucb_a;
		}
	}
	Point* giveSelection(const float multier) {
		Point* p = new Point(0, 0);
		int i = 0;
		float max = -1.0f;
		for (auto& child : childlist) {
			if (child && max < child->ucb_a) {
				max = child->ucb_a;
				p->x = top[i];
				p->y = i;
			}
			i++;
		}
		return p;
	}
	float calculate(const float multier)const {
		return ucb_a + ucb_b * multier;
	}
	Node* findWinChild() {
		for (auto& child : childlist) {
			if (child && child->winner == player) {
				child->wintime += 2;
				child->totaltime += 2;
				return child;
			}
		}
		return NULL;
	}
	int expand(int n)const {
		vector<int> candidate;
		for (int i = 0; i < n; i++) {
			if (top[i] >= 0 && childlist[i] == NULL) {
				candidate.push_back(i);
			}
		}
		if (!candidate.empty()) {
			return candidate[rand() % candidate.size()];
		}
		return -1;
	}
	int findRoad(const float& multier, Node*& next) {
		float max = -1.0f;
		int road_rank = -1, i = 0;
		for (auto& child: childlist) {
			if (child && max < child->calculate(multier)) {
				max = child->calculate(multier);
				next = &(*child);
				road_rank = i;
			}
			i++;
		}
		return road_rank;
	}
};

#endif