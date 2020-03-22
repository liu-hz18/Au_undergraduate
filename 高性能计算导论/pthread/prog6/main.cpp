
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include "ThreadPool.h"
#include "Runnable.h"
#include "timer.h"

int thread_num, block;
unsigned long seed;

unsigned long xorshift(){
    seed ^= seed << 13;
    seed ^= seed << 17;
    seed ^= seed << 5;
    return seed;
}

double* matrix;
int* vec;

double* res_pth;
double* res_omp_dyn;
double* res_omp_sta;
double* res_omp_gui;

void generate(int n){
    int off;
    for(size_t i = 0; i < n; i++){
        off = i * n;
        for(size_t j = 0; j < n; j++){
            matrix[off + j] = double(xorshift()) / RAND_MAX;
        }
    }
    for(size_t i = 0; i < n; i++){
        vec[i] = xorshift() % n + 1;
    }
}

class myRun: public Runnable{
    int beg, end, n;
public:
    myRun(int b, int e, int _n): beg(b), end(e), n(_n){}
    void run(){
        for(size_t i = beg; i < end; i++){
            double temp = 0.0;
            int k = vec[i], off = i * n;
            for(size_t j = 0; j < k; j++){
                temp += matrix[off + j];
            }
            res_pth[i] = temp / k;
        }
    }
};

void para_omp_dynamic(int n){
    int i, j, k, off;
    double temp;
#   pragma omp parallel for num_threads(thread_num)\
        schedule(dynamic, block) private(k, off, i, j, temp)
    for(i = 0; i < n; i++){
        temp = 0.0;
        k = vec[i], off = i * n;
        for(j = 0; j < k ; j++){
            temp += matrix[off + j];
        }
        res_omp_dyn[i] = temp / k;
    }
}

void para_omp_static(int n){
    int i, j, k, off;
    double temp;
#   pragma omp parallel for num_threads(thread_num)\
        schedule(static, block) private(k, off, i, j, temp)
    for(i = 0; i < n; i++){
        temp = 0.0;
        k = vec[i], off = i * n;
        for(j = 0; j < k ; j++){
            temp += matrix[off + j];
        }
        res_omp_sta[i] = temp / k;
    }
}

void para_omp_guided(int n){
    int i, j, k, off;
    double temp;
#   pragma omp parallel for num_threads(thread_num)\
        schedule(guided, block) private(k, off, i, j, temp)
    for(i = 0; i < n; i++){
        temp = 0.0;
        k = vec[i], off = i * n;
        for(j = 0; j < k; j++){
            temp += matrix[off + j];
        }
        res_omp_gui[i] = temp / k;
    }
}

void print(int n){
    for(int i = 0; i < n; i++, putchar('\n')){
        for(int j = 0; j < n; j++){
            printf("%.2lf ", matrix[i * n + j]);
        }
    }
    for(int i = 0; i < n; i++){
        printf("%d ", vec[i]);
    }
    putchar('\n');
}

int main(int argc, char const *argv[]){
    if(argc != 4){
        printf("Usage: %s [thread_num] [n] [block]\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[2]), i;
    block = atoi(argv[3]);
    thread_num = atoi(argv[1]);
    seed = (unsigned)time(NULL);
    
    matrix = new double[n * n];
    vec = new int[n];
    res_pth = new double[n];
    res_omp_dyn = new double[n];
    res_omp_sta = new double[n];
    res_omp_gui = new double[n];
    generate(n);
    puts("init end..");
#   ifdef DEBUG
    print(n);
#   endif
    double beg_par, end_par, beg_dyn, end_dyn, beg_sta, end_sta, beg_gui, end_gui;
    {
        ThreadPool pool(thread_num);
        GET_TIME(beg_par);
        for(i = 0; i + block <= n; i += block){
            pool.addTask( new myRun(i, i + block, n) );
        }
        if(i != n){
            pool.addTask( new myRun(i, n, n) );
        }
    }
    GET_TIME(end_par);
    
    GET_TIME(beg_dyn);
    para_omp_dynamic(n);
    GET_TIME(end_dyn);

    GET_TIME(beg_sta);
    para_omp_static(n);
    GET_TIME(end_sta);

    GET_TIME(beg_gui);
    para_omp_guided(n);
    GET_TIME(end_gui);

    printf("pthread time:      %.6lf\n", end_par - beg_par);
    printf("omp(dynamic) time: %.6lf\n", end_dyn - beg_dyn);
    printf("omp(static) time:  %.6lf\n", end_sta - beg_sta);
    printf("omp(guided) time:  %.6lf\n", end_gui - beg_gui);

    delete[] matrix;
    delete[] vec;
    delete[] res_pth;
    delete[] res_omp_dyn;
    delete[] res_omp_sta;
    delete[] res_omp_gui;
    return 0;
}
