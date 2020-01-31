
#include "SplayTree.h"
#include "util.h"
#include <time.h>
#include <math.h>
using namespace std;

//����n���������(���ң����룬ɾ��)��������ݷ�ΧΪ[0, m)
void testSplayRandom(int n, int m){
	SplayTree splay;
	int count = 0;
	while(count++ < n){
		int data = dice(m);
		switch(dice(3)){
			case 0:
				printf("Searching %4d......", data);
				splay.search(data) ? printf("Found done with  %4d ", splay.getroot()->weight) : printf("Data Not Found        ");
				break;
			case 1:
				printf("Inserting %4d......", data);
				splay.insert(data);
				(data == splay.getroot()->weight) ? printf("Insert done with %4d ", splay.getroot()->weight) : printf("Data %d duplicate", data);
				break;
			default:
				printf("Removing  %4d......", data);
				splay.remove(data) ? printf("Remove done with %4d ", data) : printf("Data Not Found        ");
				break;
		}
		printf("...... size:%d\n", splay.size());
	}
}

int main(){
	srand((unsigned)time(NULL));
	int n = 3000, m = 100;
	clock_t start, finish;
	start = clock();
	testSplayRandom(n, m);
	finish = clock();
	//���Կ�����ͳ��������, �ﵽ���ȶ���nlogm���Ӷ�, ����splay���ĳ����Ƚϴ󣡣���
	printf("\n%d operations finished...tot time:%f...nlogm = %.2f\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC, double(n) * log(double(m)) / log(2.0));
	return 0;
}
