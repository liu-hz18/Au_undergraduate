
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include "timer.h"

int total_thread;
int cur_thread_num;
pthread_mutex_t mu;

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

void* fib_para(void* n){
    long my_n = (long)n;
    if(my_n < 15){
        return (void*)fib_serial_fast(my_n);
    }
#   ifdef DEBUG
    printf("thread %d: fib(%ld)\n", (unsigned int)pthread_self(), my_n);
#   endif
    bool can_create = false;
    {
        pthread_mutex_lock(&mu);
        if(++cur_thread_num < total_thread){
            can_create = true;
        }
        pthread_mutex_unlock(&mu);
    }
    if(can_create){
        pthread_t new_thread;
        long firstres, secondres;
        //create a new thread to calculate fib(n-2)
        pthread_create(&new_thread, nullptr, fib_para, (void*)(n-2));
        //this thread to calculate fib(n-1)
        firstres = (long)fib_para((void*)(n-1));
        pthread_join(new_thread, (void**)&secondres);
        {
            pthread_mutex_lock(&mu);
            cur_thread_num--;
            pthread_mutex_unlock(&mu);
        }
        return (void*)(firstres + secondres);
    } else {
        return (void*)( (long)fib_para( (void*)(n-1) ) + (long)fib_para( (void*)(n-2) ) );
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

    pthread_t first_thread;
    void* ans;
    pthread_mutex_init(&mu, nullptr);
    
    GET_TIME(beg_par);
    pthread_create(&first_thread, nullptr, fib_para, (void*)n);    
    pthread_join(first_thread, &ans);
    GET_TIME(end_par);
    
    printf("fib(n) = %ld, time: %lfs\n", (long)ans, end_par - beg_par);

    GET_TIME(beg_ser);
    long ser_ans = fib_serial(n);
    GET_TIME(end_ser);
    printf("fib(n) = %ld, time: %lfs\n", ser_ans, end_ser - beg_ser);

    return 0;
}
