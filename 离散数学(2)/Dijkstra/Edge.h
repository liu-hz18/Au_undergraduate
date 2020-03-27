#pragma once

struct Edge{
	int to, weight;
	Edge(int t, int w = 1): to(t), weight(w){}
	bool operator<(Edge const& e){
		return weight < e.weight;
	}
	bool operator==(Edge const& e){
		return weight < e.weight;
	}
};