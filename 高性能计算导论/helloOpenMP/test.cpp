
#include <stdio.h>
#include <omp.h> //openMP�⣬ע���� "����->����->��������->C/C++->����" �� ѡ�� ֧�� openMP
#include <time.h>
#include <iostream>
using namespace std;

//OpenMP ������һ���򵥵ĺ����⣬����һ����������֧�ֵĿ��
//�����б��룺g++ test.cpp -fopenmp

int main(){
#ifndef _OPENMP
	cerr<<"OpenMP not supported"<<endl;
#endif
	int n = 20;
	clock_t x = clock();
#pragma omp parallel for /*num_threads(2)*///���л�
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
