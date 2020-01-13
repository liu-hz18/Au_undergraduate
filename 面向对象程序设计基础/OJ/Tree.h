#ifndef TREE_H
#define TREE_H

#include<iostream>
using namespace std;

class Tree{
	int ages;
public:
	Tree();
	Tree(int a);
	void grow(int year);
	int age();
};


#endif