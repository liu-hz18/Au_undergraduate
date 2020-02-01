
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "rbtree.h"

//进行n次随机操作(查找，插入，删除)，随机数据范围为[0, m)
void testRBTreeRandom(int n, int m){
	RedBlackTree rbtree;
	int count = 0;
	BinNode* t;
	while(count++ < n){
		int data = dice(m);
		switch(dice(3)){
			case 0:
				printf("Searching %4d......", data);
				(t = rbtree.search(data)) ? printf("Found done with  %4d ", t->weight) : printf("Data Not Found        ");
				break;
			case 1:
				printf("Inserting %4d......", data);
				(rbtree.insert(data)->weight == data) ? printf("Insert done with %4d ", data) : printf("Data %d duplicate", data);
				break;
			default:
				printf("Removing  %4d......", data);
				rbtree.remove(data) ? printf("Remove done with %4d ", data) : printf("Data Not Found        ");
				break;
		}
		printf("...... size:%d\n", rbtree.size());
		//rbtree.traverseIn(rbtree.getroot()); putchar(10);//输出中序遍历便于调试
	}
}

int main(){
	int n = 5000, m = 10000;
	srand((unsigned)time(NULL));
	clock_t start, finish;
	start = clock();
	testRBTreeRandom(n, m);
	finish = clock();
	//可以看到在统计意义上, 达到了稳定的nlogm复杂度
	printf("\n%d operations finished...tot time:%f...nlogm = %.2f\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC, double(n) * log(double(n)) / log(2.0));
	return 0;
}
