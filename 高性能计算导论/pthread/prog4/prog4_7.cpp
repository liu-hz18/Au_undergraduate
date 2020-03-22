
#include <pthread.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX_LENGTH = 100;
pthread_mutex_t mu;
char msg[MAX_LENGTH];
bool ok;

void* run(void* rank){
    long my_rank = (long)rank;
    while(1){
        pthread_mutex_lock(&mu);
        if(my_rank % 2 == 1){
            if(ok){
                printf("message received by %ld: %s\n", my_rank, msg);
                ok = 0;
                pthread_mutex_unlock(&mu);
                break;
            }
        }else{
            if(!ok){
                sprintf(msg, "Hello from thread %ld", my_rank);
                ok = 1;
                pthread_mutex_unlock(&mu);
                break;
            }
        }
        pthread_mutex_unlock(&mu);
    }
    return nullptr;
}

int main(int argc, const char* argv[]){
    int threadnum;
    if(argc < 2 || (threadnum = atoi(argv[1])) == 0 || threadnum % 2 == 1){
        printf("error! format: %s [threadnum]\n", argv[0]);
        exit(1);
    }
    ok = 0;
    
    pthread_t* threadpool = new pthread_t[threadnum];
    printf("create %d threads...\n", threadnum);

    for(size_t i = 0; i < threadnum; i++){
        pthread_create(&threadpool[i], nullptr, ::run, (void*)i);
    }

    for(size_t i = 0; i < threadnum; i++){
        pthread_join(threadpool[i], nullptr);
    }

    delete[] threadpool;
    return 0;
}
