
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "AVL.h"

//进行n次随机操作(查找，插入，删除)，随机数据范围为[0, m)
void testAVLRandom(int n, int m){
	AVLTree avl;
	int count = 0;
	while(count++ < n){
		int data = dice(m);
		switch(dice(3)){
			case 0:
				printf("Searching %4d......", data);
				avl.search(data) ? printf("Found done with  %4d ", avl.getroot()->weight) : printf("Data Not Found        ");
				break;
			case 1:
				printf("Inserting %4d......", data);
				(avl.insert(data)->weight == data) ? printf("Insert done with %4d ", data) : printf("Data %d duplicate", data);
				break;
			default:
				printf("Removing  %4d......", data);
				avl.remove(data) ? printf("Remove done with %4d ", data) : printf("Data Not Found        ");
				break;
		}
		printf("...... size:%d\n", avl.size());
		//avl.traverseIn(avl.getroot()); putchar(10);//输出中序遍历便于调试
	}
}


int main(){
	int n = 5000, m = 10000;
	srand((unsigned)time(NULL));
	clock_t start, finish;
	start = clock();
	testAVLRandom(n, m);
	finish = clock();
	//可以看到在统计意义上, 达到了稳定的nlogm复杂度
	printf("\n%d operations finished...tot time:%f...nlogm = %.2f\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC, double(n) * log(double(m)) / log(2.0));
	return 0;
}
