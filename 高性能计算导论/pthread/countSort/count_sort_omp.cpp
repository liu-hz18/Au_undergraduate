
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <pthread.h>
#include "timer.h"
#include "Thread.h"

int finish_count;
void Count_sort_para(int a[], int n);

void print(int a[], int n, int id = 0){
    printf("Sorted Vector in thread: %d:\n", id);
    for(int i = 0; i < n; i++){
        printf("%d \n", a[i]);
    }
    putchar('\n');
}

//Merge
class mergeThread: public Thread{
    int* a, left, right;
    bool can_sort;

public:
    mergeThread(int* arr, int l, int r, bool c):a(arr), left(l), right(r), can_sort(c){}
    void set(int l, int r, bool c){
        init();
        left = l;
        right = r;
        can_sort = c;
    }
    void run(){
#       ifdef DEBUG
        printf("in thread %d, sort %d-%d\n", threadid(), left, right);
#       endif  
        if(can_sort){
            Count_sort_para(a + left, right - left);
            finish_count ++;
            return;
        }
        int* b = new int[right - left];
        int mid = (left + right) >> 1;
        for(int p = left, q = mid, i = 0; p < mid || q < right; ){
            b[i++] = (q >= right || (p < mid && a[p] <= a[q])) ? a[p++] : a[q++];
        }
        memcpy(a + left, b, (right - left) * sizeof(int));
        finish_count ++;
        delete[] b;
    }
};

int thread_num;

void Count_sort(int a[], int n){
    int i, j, count ;
    int* temp = new int[n];
    for(i = 0; i < n; i++){
        count = 0;
        for(j = 0; j < n; j++)
            if(a[j] < a[i])
                count ++;
            else if(a[j] == a[i] && j < i)
                count ++;
        temp[count] = a[i];
    }
    memcpy(a, temp, n * sizeof(int));
    delete[] temp;
}

void Count_sort_fast(int a[], int n){
    int i, j, count;
    int* temp = new int[n];
    for(i = 0; i < n; i++){
        count = 0;
        for(j = 0; j < i; j++){
            count += (a[j] <= a[i]);
        }
        for(j = i; j < n; j++){
            count += (a[j] < a[i]);
        }
        temp[count] = a[i];
    }
    memcpy(a, temp, n * sizeof(int));
    delete[] temp;
}

//可以改成四路归并
void Count_sort_para(int a[], int n){
    int i, j, count;
    int* temp = new int[n];
    //shared:  n, a, temp
    //private: i, j, count
#   pragma omp parallel for num_threads(thread_num)\
        private(i, j, count)
    for(i = 0; i < n; i++){
        //printf("thread: %d, n:%d\n", omp_get_thread_num(), n);
        count = 0;
        for(j = 0; j < i; j++){
            count += (a[j] <= a[i]);
        }
        for(j = i; j < n; j++){
            count += (a[j] < a[i]);
        }
        temp[count] = a[i];
    }
    memcpy(a, temp, n * sizeof(int));
    delete[] temp;
}

void Count_sort_para_merge(int* a, int n){
    int m2 = n >> 1;
    int m1 = m2 >> 1;
    int m3 = (m2 + n)>>1;
    //tree-reduction
    mergeThread* t1 = new mergeThread(a, 0, m1, 1);
    mergeThread* t2 = new mergeThread(a, m1, m2, 1);
    mergeThread* t3 = new mergeThread(a, m2, m3, 1);
    mergeThread* t4 = new mergeThread(a, m3, n, 1);

    finish_count = 0;
    t1->start(); t2->start(); t3->start(); t4->start();
    t1->join(); t2->join(); t3->join(); t4->join();
    while(finish_count < 4)//busy-wait
        ;
    if(finish_count == 4){
        finish_count = 0;
        t1->set(0, m2, 0);//reuse t1 and t2
        t2->set(m2, n, 0);
        t1->start(); t2->start();
        t1->join(); t2->join();
    }
    while(finish_count < 2)//busy-wait
        ;
    if(finish_count == 2){
        finish_count = 0;
        t1->set(0, n, 0);//reuse t1
        t1->start();
        t1->join();
    }
    while(finish_count < 1)//busy-wait
        ;
    delete t1; delete t2; delete t3; delete t4;
}

int cmpfunc(const void * a, const void * b){
   return (*(int*)a - *(int*)b);
}


int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("Usage: %s [threadnum] [n]\n", argv[0]);
        exit(1);
    }
    thread_num = atoi(argv[1]);
    int n = atoi(argv[2]);
    int* a = new int[n];
    int* b = new int[n];
    int* c = new int[n];
    int* d = new int[n];
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; i++){
        a[i] = rand();
    }

    memcpy(b, a, n * sizeof(int));
    memcpy(c, a, n * sizeof(int));
    memcpy(d, a, n * sizeof(int));
    double beg_par, end_par, beg_ser, end_ser, beg_qs, end_qs, beg_mer, end_mer;
    
    //serial count sort
    GET_TIME(beg_ser);
    Count_sort_fast(a, n);
    //Count_sort(a, n);//too slow...
    GET_TIME(end_ser);
#   ifdef DEBUG
    print(a, n);
#   endif
    
    //parallel count sort
    GET_TIME(beg_par);
    Count_sort_para(b, n);
    GET_TIME(end_par);
#   ifdef DEBUG
    print(b, n);
#   endif

    //qsort in stdlib
    GET_TIME(beg_qs);
    qsort(c, n, sizeof(int), cmpfunc);
    GET_TIME(end_qs);
#   ifdef DEBUG
    print(c, n);
#   endif

    //parallel count sort in merge
    GET_TIME(beg_mer);
    Count_sort_para_merge(d, n);
    GET_TIME(end_mer);
#   ifdef DEBUG
    print(d, n);
#   endif

    printf("serial count:                %.6lfs\n", end_ser - beg_ser);
    printf("parallel count:              %.6lfs\n", end_par - beg_par);
    printf("parallel count+merge:        %.6lfs\n", end_mer - beg_mer);
    printf("qsort() time:                %.6lfs\n", end_qs - beg_qs);
    printf("Speedup Ratio(count):        %.6lf\n", (end_ser - beg_ser) / (end_par - beg_par));
    printf("Speedup Ratio(count+merge):  %.6lf\n", (end_ser - beg_ser) / (end_mer - beg_mer));
    
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    return 0;
}
