
#ifndef _UNTIL_H_
#define _UNTIL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

inline int min(int& a, int& b){return a > b ? b : a;}

inline int max(int& a, int& b){return a > b ? a : b;}

#endif
