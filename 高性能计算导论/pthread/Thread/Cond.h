#pragma once

#include <pthread.h>
#include "Mutex.h"

class Cond{
    pthread_cond_t m_cond;
public:
    Cond(){ pthread_cond_init(&m_cond, nullptr); }
    virtual ~Cond(){ pthread_cond_destroy(&m_cond); }
    Cond(const Cond&) = delete;
    Cond& operator=(const Cond&) = delete;
    int wait(Mutex *mu){ return pthread_cond_wait(&m_cond, &mu->getpmutex()); }
    void notify_one(){ pthread_cond_signal(&m_cond); }
    void notify_all(){ pthread_cond_broadcast(&m_cond); }
};
