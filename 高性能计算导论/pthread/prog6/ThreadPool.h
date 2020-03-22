#pragma once

#include <cstdio>
#include <list>
#include <atomic>

#include "Mutex.h"
#include "Locker.h"
#include "Cond.h"
#include "Runnable.h"

using std::list;

class ThreadPool{
    list<Runnable*> taskq;
    unsigned thread_num;
    Mutex mu;
    Cond cond;
    pthread_t* threads;
    std::atomic_bool finished;

public:
    ThreadPool(unsigned _n): thread_num(_n), threads(new pthread_t[thread_num]){
        finished = false;
        for(size_t i = 0; i < thread_num; i++){
            pthread_create(&threads[i], nullptr, ThreadPool::task, this);
        }
    }
    virtual ~ThreadPool(){
        finished = true;
        cond.notify_all();
        for(size_t i = 0; i < thread_num; i++){
            pthread_join(threads[i], nullptr);
        }
        for(auto iter: taskq){
            delete iter;
        }
    }
    void addTask(Runnable* t){
        MutexLocker locker(&mu);
        taskq.push_back(t);
        cond.notify_one();
    }
    static void* task(void* args);
};

void* ThreadPool::task(void* args){
    ThreadPool *thp = static_cast<ThreadPool*>(args);
    while(1){
        Runnable* t;
        {
            MutexLocker locker(&thp->mu);
            while(thp->taskq.empty() && !thp->finished){
                while( thp->cond.wait(&thp->mu) != 0 )
                    ;
            }
            if(thp->taskq.empty()){
                break;
            }
            t = thp->taskq.front();
            thp->taskq.pop_front();
        }
        t->run();
    }
    return nullptr;
}