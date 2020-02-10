
#pragma once
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#include <vector>
#include <stack>
#include <queue>
#include <list>

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

#define DEFAULT_CAPACITY 64

//¶¥µã×´Ì¬
#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

//±ß×´Ì¬
#define UNETERMINED 0
#define TREE 1
#define CROSS 2
#define FORWARD 3
#define BACKWARD 4
