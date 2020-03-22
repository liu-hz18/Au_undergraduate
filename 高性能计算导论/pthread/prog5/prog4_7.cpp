
#include <pthread.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

const int MAX_LENGTH = 100;
bool ok;
char msg[MAX_LENGTH];
pthread_mutex_t mu;
int recv;
int num;

void* run(void* rank){
    long my_rank = (long)rank;
    bool is_recv = false, is_send = false;
    while(!is_send || !is_recv){
        pthread_mutex_lock(&mu);
        if(ok){
            if(!is_recv && my_rank == recv){
                printf("receiver %ld: %s\n", my_rank, msg);
                ok = false;
                is_recv = true;
            }
        } else if (!is_send){
            sprintf(msg, "Hello from thread %ld", my_rank);
            ok = true;
            is_send = true;
            recv = (my_rank + 1) % num;
        }
        pthread_mutex_unlock(&mu);
    }
    return nullptr;
}



int main(int argc, const char* argv[]){
    ok = false;
    if(argc < 2 || (num = atoi(argv[1])) == 0){
        printf("error! use: %s [thread num]\n", argv[0]);
        exit(-1);
    }
    
    pthread_mutex_init(&mu, nullptr);
    pthread_t* threads = new pthread_t[num];
    printf("created %d threads\n", num);

    for(size_t i = 0; i < num; i++){
        pthread_create(&threads[i], nullptr, ::run, (void*)i);
    }

    for(size_t i = 0; i < num; i++){
        pthread_join(threads[i], nullptr);
    }

    delete[] threads;
    return 0;
}
