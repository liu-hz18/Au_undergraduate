
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

int thread_num;

int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("Usage: %s [threadnum] [n]\n", argv[0]);
        exit(1);
    }
    thread_num = atoi(argv[1]);
    int n = atoi(argv[2]);

    int* array = new int[n];
    int* arr1 = new int[n];
    int* arr2 = new int[n];

    memset(array, 5, sizeof(int) * n);

    double t1 = omp_get_wtime();
    memcpy(arr1, array, n*sizeof(int));
    double tot1 = omp_get_wtime() - t1;

    
    double t2 = omp_get_wtime();
    int interval = n / thread_num + 1, i;
#   pragma omp parallel for num_threads(thread_num) schedule(dynamic)
    for(i = 0; i < n; i += interval){
        memcpy(arr2+i, array+i, std::min(n-i, interval) * sizeof(int));
    }
    double tot2 = omp_get_wtime() - t2;

    for(int i = 0; i < n; i++){
        if(arr1[i] != arr2[i]){
            printf("error at %d !!!\n", i);
            break;
        }
    }

    printf("tot1: %.6lfs\t tot2: %.6lfs\t speedup:%.6lf\n", tot1, tot2, tot1/tot2);
    delete[] array;
    delete[] arr2;
    return 0;
}