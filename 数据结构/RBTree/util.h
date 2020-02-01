
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>

#define RED 0
#define BLACK 1

int max(int a, int b);
int min(int a, int b);
void swap(int& a, int& b);
int dice(int n);

inline int max(int a, int b){return a > b ? a : b;}
inline int min(int a, int b){return a > b ? b : a;}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}
inline int dice(int n){return rand() % n;}

#endif
