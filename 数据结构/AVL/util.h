
#ifndef _UNTIL_H_
#define _UNTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int max(int a, int b);
int min(int a, int b);
void swap(int& a, int& b);
int dice(int n);

inline int max(int a, int b){return a > b ? a : b;}
inline int min(int a, int b){return a > b ? b : a;}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}
inline int dice(int n){return rand() % n;}

#endif
