
#include <pthread.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAX_LENGTH = 100;
bool ok;
pthread_mutex_t mu;
char msg[MAX_LENGTH];

void* consumer_func(void* rank){
    long my_rank = (long)rank;
    while(1){
        pthread_mutex_lock(&mu);
        if(ok){
            printf("message: %s\n", msg);
            pthread_mutex_unlock(&mu);
            break;
        }
        pthread_mutex_unlock(&mu);
    }
    return nullptr;
}

void* producer_func(void* rank){
    long my_rank = (long)rank;
    pthread_mutex_lock(&mu);
    sprintf(msg, "Hello from thread %ld!", my_rank);
    ok = 1;
    pthread_mutex_unlock(&mu);
    return nullptr;
}

int main(){
    ok = 0;
    pthread_t consumer, producer;
    pthread_mutex_init(&mu, nullptr);

    pthread_create(&consumer, nullptr, ::consumer_func, (void*)0);
    pthread_create(&producer, nullptr, ::producer_func, (void*)1);

    pthread_join(consumer, nullptr);
    pthread_join(producer, nullptr);

    return 0;
}
