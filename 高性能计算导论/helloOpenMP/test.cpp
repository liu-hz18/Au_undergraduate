
#include <stdio.h>
#include <omp.h> //openMP库，注意在 "调试->属性->配置属性->C/C++->语言" 中 选择 支持 openMP
#include <time.h>
#include <iostream>
using namespace std;

//OpenMP 并不是一个简单的函数库，而是一个诸多编译器支持的框架
//命令行编译：g++ test.cpp -fopenmp

int main(){
#ifndef _OPENMP
	cerr<<"OpenMP not supported"<<endl;
#endif
	int n = 20;
	clock_t x = clock();
#pragma omp parallel for /*num_threads(2)*///并行化
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			//cout<<i<<' '<<j<<' '<<"threadID:"<<omp_get_thread_num()<<endl;
			printf("%d, %d, threadID:%d\n", i, j, omp_get_thread_num());
		}
	}
	clock_t y = clock();
	cout<<(y - x)<<"ms"<<endl;
	return 0;
}
