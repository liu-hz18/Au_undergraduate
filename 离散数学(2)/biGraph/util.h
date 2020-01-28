
#ifndef _UNTIL_H_
#define _UNTIL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <list>
using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

#define DEFAULT_CAPACITY 64

//����״̬
#define UNDISCOVERED 0 //��δ����
#define DISCOVERED 1 //���͵�
#define VISITED 2 //�޷�����ƥ��ĵ�

#endif
