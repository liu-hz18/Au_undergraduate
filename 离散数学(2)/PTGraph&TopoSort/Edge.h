#pragma once

struct Edge{
	int to, weight;
	Edge(){};
	Edge(int t, int w): to(t), weight(w){}
};