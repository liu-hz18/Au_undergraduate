
#ifndef _UNTIL_H_
#define _UNTIL_H_

#include <string.h>
#include <assert.h>

#include <queue>
#include <vector>
#include <utility>
using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

//顶点状态
#define UNDISCOVERED 0//未标号 
#define DISCOVERED 1//已标号未检查
#define VISITED 2//已标号已检查

inline int min(int& a, int& b){return a > b ? b : a;}

inline int max(int& a, int& b){return a > b ? a : b;}

inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}

inline int add(int a, int b){return (a == INT_MAX || b == INT_MAX) ? INT_MAX : (a + b);}

inline int abs(int a){return a < 0 ? -a : a;}

#endif
