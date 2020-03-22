
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <omp.h>

const int n = 50;

int main(int argc, const char* argv[]){
    int threadnum;
    if(argc < 2 || (threadnum = atoi(argv[1])) == 0){
        printf("error! use: %s [thread num]\n", argv[0]);
        exit(-1);
    }
    printf("created %d threads.\n", threadnum);
    int* a = new int[n];

#   pragma omp parallel for num_threads(n)\
        default(none) private(i) shared(a, n)
    for(size_t i = 0; i < n; i++){
        a[i] = (i * (i + 1)) >> 1;
    }

    //print to stdout
    for(size_t i = 0; i < n ; i++){
        printf("%d ", a[i]);
    }
    putchar(10);

    delete[] a;
    return 0;
}
