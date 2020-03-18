//prefix sum of vector
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>//for srand(), rand()
#include <time.h>//for time()

#define LOCAL_N 10

int main(){
    int pid, nump, total;
    int local_a[LOCAL_N], local_prefix_sum[LOCAL_N];
    int i, pred;
    //Initialization
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nump);
    srand(pid + time(NULL));//local rand seed
    total = nump * LOCAL_N;
    //generate random vector of LOCAL_N size
    for(i = 0; i < LOCAL_N; i ++){
        local_a[i] = rand() % 10;
    }

#   ifdef DEBUG
    printf("Process %d, vec:\n", pid);
    for(i = 0; i < LOCAL_N; i++){
        printf("%d ", local_a[i]);
    }
    putchar('\n');
#   endif
    
    //compute local prefix sum of local_a
    local_prefix_sum[0] = local_a[0];
    for(i = 1; i < LOCAL_N; i++){
        local_prefix_sum[i] = local_prefix_sum[i-1] + local_a[i];
    }
    //Perform MPI_Scan() get pred_sum
    //local sum == local_prefix_sum[LOCAL_N]
    MPI_Scan(&local_prefix_sum[LOCAL_N-1], &pred, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    pred -= local_prefix_sum[LOCAL_N-1];
    //add pred sum
    for(i = 0; i < LOCAL_N; i++){
        local_prefix_sum[i] += pred;
    }
    //Gather all prefix sums and print
    if(pid == 0){
        int *prefix_sum = malloc(total * sizeof(int));
        MPI_Gather(local_prefix_sum, LOCAL_N, MPI_INT, prefix_sum, LOCAL_N, MPI_INT, 0, MPI_COMM_WORLD);
        //print
        printf("Prefix sum:\n");
        for(i = 0; i < total; i++){
            printf("%d ", prefix_sum[i]);
        }
        putchar('\n');
        free(prefix_sum);
    }else{
        MPI_Gather(local_prefix_sum, LOCAL_N, MPI_INT, NULL, LOCAL_N, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
