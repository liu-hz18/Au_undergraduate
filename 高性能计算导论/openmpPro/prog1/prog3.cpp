
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <omp.h>
#include "timer.h"

int total_thread;
int cur_thread_num;
omp_lock_t mu;

long fib_serial_fast(int n){
    long a = 0, b = 1, c;
    for(int i = 1; i < n; i++){
        c = b; b = a + b; a = c;
    }
    return b;
}

long fib_serial(int n){
    if(n <= 2){
        return 1;
    }
    return fib_serial(n - 1) + fib_serial(n - 2);
}

long fib_para(long n){
    if(n < 15){
        return fib_serial_fast(n);
    }
    //if(n <= 2){
    //    return 1;
    //}
#   ifdef DEBUG
    printf("thread %d: fib(%d)\n", omp_get_thread_num(), n);
#   endif
    bool can_create = false;
    {
        omp_set_lock(&mu);
        if(++cur_thread_num < total_thread){
            can_create = true;
        }
        omp_unset_lock(&mu);
    }
    if(can_create){
        long firstres, secondres;
#       pragma omp parallel sections
        {
#           pragma omp section
            firstres = fib_para(n - 1);
#           pragma omp section
            secondres = fib_para(n - 2);
        }
        {
            omp_set_lock(&mu);
            cur_thread_num--;
            omp_unset_lock(&mu);
        }
        return firstres + secondres;
    } else {
        return fib_para(n - 1) + fib_para(n - 2);
    }
}


int main(){
    long n;
    printf("Enter thread_num:\n");
    scanf("%d", &total_thread);
    printf("Enter n of fib(n):\n");
    scanf("%ld", &n);
    cur_thread_num = 1;//main thread take for 1
    double beg_ser, beg_par, end_ser, end_par;
    long ans;

    omp_init_lock(&mu);
    omp_set_dynamic(1);
    //omp_set_nested(1);

    GET_TIME(beg_par);
#   pragma omp parallel num_threads(total_thread)
    ans = fib_para(n);
    GET_TIME(end_par);
    omp_destroy_lock(&mu);

    printf("fib(n) = %ld, time: %lfs\n", ans, end_par - beg_par);

    GET_TIME(beg_ser);
    long ser_ans = fib_serial(n);
    GET_TIME(end_ser);
    printf("fib(n) = %ld, time: %lfs\n", ser_ans, end_ser - beg_ser);

    return 0;
}
