
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <omp.h>
#include "timer.h"

int thread_num;
const int chunksize = 50;
static unsigned long x = 123456789 + unsigned(time(NULL));
static unsigned long y = 362436069 + unsigned(time(NULL));
static unsigned long z = 435891257 + unsigned(time(NULL));

//for fast rand()
inline unsigned long xorshift(void){
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

void generate(int n, double** matrix, double** vector){
    (*matrix) = new double[n * n];
    int off;
    unsigned long rand_max = 9223372036854775807 / 2;
    for(int i = 0; i < n; i++){
        off = i * n;
        for(int j = 0; j < n; j++){
            (*matrix)[off + j] = -1.0 + double(xorshift()) / rand_max;
        }
    }
    (*vector) = new double[n];
    for(int i = 0; i < n; i++){
        (*vector)[i] = -1.0 + double(xorshift()) / rand_max;
    }
}

void print(int n, double* matrix, double* vector){
    printf("vector of size %d:", n);
    for(int i = 0; i < n; i++){
        printf("%4.3lf ", vector[i]);
    }
    puts("\nMatrix:");
    int off;
    for(int i = 0; i < n; i++, putchar('\n')){
        off = i * n;
        for(int j = 0; j < n; j++){
            printf("%4.3lf ", matrix[off + j]);
        }
    }
}

double cal_error(int n, double** ser_vec, double** par_vec){
    double temp = 0.0, err;
    int i;
#   pragma omp parallel for num_threads(thread_num)\
        reduction(+ :temp) private(i, err)
    for(i = 0; i < n; i++){
        err = (*ser_vec)[i] - (*par_vec)[i];
        temp += err * err;
    }
    return sqrtf(temp);
}


void print_res(int n, double** res){
    for(int i = 0; i < n; i++){
        printf("%.10lf ", (*res)[i]);
    }
    putchar('\n');
}

double serial(int n, double** res, double** matrix, double** vector){
    (*res) = new double[n];
    double temp, beg, end;
    int off;
    GET_TIME(beg);
    for(int i = 0; i < n; i++){
        temp = 0.0;
        off = i * n;
        for(int j = 0; j < n; j++){
            temp += (*matrix)[off + j] * (*vector)[j];
        }
        (*res)[i] = temp;
    }
    GET_TIME(end);
    return end - beg;
}


double parallel_static(int n, double** res, double** matrix, double** vector){
    (*res) = new double[n];
    double temp, beg, end;
    int off, i, j;
    GET_TIME(beg);
#   pragma omp parallel for num_threads(thread_num) \
        schedule(static, chunksize) private(temp, off, i, j)
    for(i = 0; i < n; i++){
        temp = 0.0; off = i * n;
        //printf("thread id: %d, row: %d\n", omp_get_thread_num(), i);
        for(j = 0; j < n; j++){
            temp += (*matrix)[off + j] * (*vector)[j];
        }
        (*res)[i] = temp;
    }
    GET_TIME(end);
    return end - beg;
}

double parallel_dynamic(int n, double** res, double** matrix, double** vector){
    (*res) = new double[n];
    double temp, beg, end;
    int off, i, j;
    GET_TIME(beg);
#   pragma omp parallel for num_threads(thread_num) \
        schedule(dynamic, chunksize) private(temp, off, i, j)
    for(i = 0; i < n; i++){
        temp = 0.0; off = i * n;
        //printf("thread id: %d, row: %d\n", omp_get_thread_num(), i);
        for(j = 0; j < n; j++){
            temp += (*matrix)[off + j] * (*vector)[j];
        }
        (*res)[i] = temp;
    }
    GET_TIME(end);
    return end - beg;
}


double parallel_guided(int n, double** res, double** matrix, double** vector){
    (*res) = new double[n];
    double temp, beg, end;
    int off, i, j;
    GET_TIME(beg);
#   pragma omp parallel for num_threads(thread_num) \
        schedule(guided, chunksize) private(temp, off, i, j)
    for(i = 0; i < n; i++){
        temp = 0.0; off = i * n;
        //printf("thread id: %d, row: %d\n", omp_get_thread_num(), i);
        for(j = 0; j < n; j++){
            temp += (*matrix)[off + j] * (*vector)[j];
        }
        (*res)[i] = temp;
    }
    GET_TIME(end);
    return end - beg;
}


double parallel_colomn(int n, double** res, double** matrix, double** vector){
    (*res) = new double[n];
    memset(*res, 0.0, n * sizeof(double));
    double beg, end, temp;
    int off, i, j, left, right, t, tot = ((n % chunksize) ? 1 : 0) + n / chunksize;
    
    GET_TIME(beg);
#   pragma omp for
    for(t = 0; t < tot; t++){
        left = t * chunksize;
        right = (t + 1 == tot) ? n : chunksize + left;
        //printf("thread id: %d, block: %d\n", omp_get_thread_num(), t);
#       pragma omp parallel for num_threads(thread_num)\
            schedule(static) private(i, j, temp, off)
        for(i = 0; i < n; i++){
            temp = 0.0, off = n * i;
            for(j = left; j < right; j++){
                temp += (*matrix)[off + j] * (*vector)[j];
            }
            (*res)[i] += temp;
        }
    }
    GET_TIME(end);
    return end - beg;
}


int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("Usage: %s [thread_num] [n]\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[2]);
    const int ncore = omp_get_num_procs();
    thread_num = std::min(n, atoi(argv[1]));
    thread_num = std::min(thread_num, ncore);
    
    double *matrix, *vector, *ser_vec, *par_vec;
    double mytime, err;

    generate(n, &matrix, &vector);
    printf("dimension of vector: %d, total threads: %d\n", n, thread_num);

#   ifdef DEBUG
    print(n, matrix, vector);
#   endif

    mytime = serial(n, &ser_vec, &matrix, &vector);
    printf("\nserial time:          %.6lf\n", mytime);
    
    mytime = parallel_static(n, &par_vec, &matrix, &vector);
    err = cal_error(n, &ser_vec, &par_vec);
    printf("\nparallel time static  %.6lf\n", mytime);
    printf("error(2 norm)         %.15lf\n", err);
    delete[] par_vec;

    mytime = parallel_dynamic(n, &par_vec, &matrix, &vector);
    err = cal_error(n, &ser_vec, &par_vec);
    printf("\nparallel time dynamic %.6lf\n", mytime);
    printf("error(2 norm)         %.15lf\n", err);
    delete[] par_vec;

    mytime = parallel_guided(n, &par_vec, &matrix, &vector);
    err = cal_error(n, &ser_vec, &par_vec);
    printf("\nparallel time guided  %.6lf\n", mytime);
    printf("error(2 norm)         %.15lf\n", err);
    delete[] par_vec;

    mytime = parallel_colomn(n, &par_vec, &matrix, &vector);
    err = cal_error(n, &ser_vec, &par_vec);
    printf("\nparallel time column  %.6lf\n", mytime);
    printf("error(2 norm):        %.15lf\n", err);
    delete[] par_vec;

    delete[] ser_vec;
    delete[] matrix;
    delete[] vector;
    return 0;
}
