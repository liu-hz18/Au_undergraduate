
#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <hash_map>
#include <string>
using namespace std;

int max(int& a, int& b){
	return a > b ? a : b;
}

int min(int& a, int& b){
	return a < b ? a : b;
}

template<typename T>
void _swap(T& a, T& b){
	T temp = a; a = b; b = temp;
}

#endif
