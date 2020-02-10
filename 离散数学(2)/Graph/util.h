
#pragma once
#include "macro.h"

int min(int& a, int& b);
int max(int& a, int& b);
int add(int a, int b);
//����0-n�����
int dice(int n);
int dice(int lo, int hi);
void swap(int& a, int& b);

inline int min(int& a, int& b){return a > b ? b : a;}
inline int max(int& a, int& b){return a > b ? a : b;}
inline int add(int a, int b){return (a == INT_MAX || b == INT_MAX) ? INT_MAX : (a + b);}
//����0-n�����
inline int dice(int n){return rand() % n;}
inline int dice(int lo, int hi){return lo + rand() % (hi - lo);}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}

namespace util{
template<typename T>
inline void swap(T&a, T&b){T temp = a; a = b; b = temp;}
}

