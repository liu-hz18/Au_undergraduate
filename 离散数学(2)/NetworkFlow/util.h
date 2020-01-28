
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

//����״̬
#define UNDISCOVERED 0//δ��� 
#define DISCOVERED 1//�ѱ��δ���
#define VISITED 2//�ѱ���Ѽ��

inline int min(int& a, int& b){return a > b ? b : a;}

inline int max(int& a, int& b){return a > b ? a : b;}

inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}

inline int add(int a, int b){return (a == INT_MAX || b == INT_MAX) ? INT_MAX : (a + b);}

inline int abs(int a){return a < 0 ? -a : a;}

#endif
