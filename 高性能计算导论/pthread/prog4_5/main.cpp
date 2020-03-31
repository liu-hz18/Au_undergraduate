
#include <time.h>
#include <iostream>
#include <cstdio>
#include <atomic>
#include <pthread.h>
#include <queue>
#include <unistd.h>

#include "orderedList.h"
using std::queue;

//定义随机操作的比例
constexpr int findRate = 8;
constexpr int deleteRate = 2;
constexpr int insertRate = 4;
constexpr int printRate = 1;
constexpr int total = findRate + deleteRate + insertRate + printRate;

//任务类
struct Task{
    int op, value;
    Task(int _op, int _value): op(_op), value(_value){}
};

queue<Task> taskQueue;//任务队列
unsigned thread_num;//总线程数
pthread_mutex_t mu;//互斥量
pthread_cond_t cond;//信号量
std::atomic_bool finished;//标志位
orderedList<int> mylist;//共享: 有序链表

//随机调用
void run(const Task& task){
    if (task.op < findRate) {//find for 8/15 [0, 7)
        if(mylist.find(task.value)){
            printf("threadid %u, find value %d success\n", (unsigned int)pthread_self(), task.value);
        } else {
            printf("threadid %u, find value %d failed\n", (unsigned int)pthread_self(), task.value);
        }
    } else if (findRate <= task.op && task.op < findRate + deleteRate) {//delete for 2/15 [7, 9)
        if(mylist.pop(task.value)){
            printf("threadid %u, delete value %d success\n", (unsigned int)pthread_self(), task.value);
        } else {
            printf("threadid %u, delete value %d failed\n", (unsigned int)pthread_self(), task.value);
        }
    } else if (findRate + deleteRate <= task.op && task.op < total - printRate) {//insert for 4/15 [9, 14)
        mylist.push(task.value);
        printf("threadid %u, inserted value %d\n", (unsigned int)pthread_self(), task.value);
    } else { // print for 1/15 [14, 15)
        std::cout << mylist.toString();
    }
    sleep(1);//sleep for 1 sec
}

//线程函数
void* runtask(void* args){
    while(1){
        pthread_mutex_lock(&mu);
        while(taskQueue.empty() && !finished){
            while( pthread_cond_wait(&cond, &mu) != 0)
                ;
        }
        if(taskQueue.empty()){
            pthread_mutex_unlock(&mu);
            break;
        }
        Task t = taskQueue.front();
        taskQueue.pop();
        pthread_mutex_unlock(&mu);
        run(t);
    }
    return nullptr;
}

void Usage(char const* argv){
    printf("usage: %s [thread_num] [task_num]\n", argv);
    exit(1);
}


int main(int argc, char const *argv[]){
    if (argc != 3) Usage(argv[0]);

#   ifdef DEBUG
    printf("Percent: find: %f, insert: %f, delete: %f\n", readPercent, (1.0 - readPercent)/2, (1.0 - readPercent)/2);
#   endif

    int thread_num = atoi(argv[1]), task_num = atoi(argv[2]);
    srand((unsigned)time(0));
    
    //Create Thread Pool
    pthread_t* thread_handles = new pthread_t[thread_num];
    
    /* Initialize mutexes and conditional variables */
    pthread_mutex_init(&mu, nullptr);
    pthread_cond_init(&cond, nullptr);
    finished = false;
    
    /* Start threads */
    for(int i = 0; i < thread_num; i++){
        pthread_create(&thread_handles[i], nullptr, ::runtask, nullptr);
    }

    /* Generate Tasks */
    for(int i = 0; i < task_num; i++){
        pthread_mutex_lock(&mu);
        taskQueue.push( Task( rand() % total, rand() % task_num) );
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mu);
    }
    finished = true;

    /* Wait fot threads to compelete */
    pthread_cond_broadcast(&cond);
    for(int i = 0; i < thread_num; i++){
        pthread_join(thread_handles[i], nullptr);
    }

    /* Destroy mutex and conditional variables */
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mu);
    delete[] thread_handles;

    return 0;
} /* main */
