#include <mpi.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
/*
 * Modify the "multiply, run" to implement your parallel algorihtm.
 * Compile:
 *      this is a c++ style code
 *      mpiicc -g -Wall -o main prog3_6.cpp
 * Run: mpiexec -n <comm_sz> ./main
 */
using namespace std;
/*
 * It is a serial algorithm to 
 * get the true value of matrix-vector multiplication
 * please calculation the difference between true value and the value you obtain
 *
 */
void serial(int n, double *matrix, double *vector, double **result){
    (*result) = new double[n];
    for (int i = 0; i < n; i++) {
        double temp = 0.0;
        for (int j = 0; j < n; j++) {
            temp += matrix[i * n + j] * vector[j];
        }
        (*result)[i] = temp;
    }
}

/*
 *  generate random matrix and vector,
 *  In order to debug conveniently, you can define a const matrix and vector
 *  but I will check your answer based on random matrix and vector
 */
void gen_matrix(int n, double **matrix) {
    (*matrix) = new double[n * n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            (*matrix)[i * n + j] = -1 + rand() * 1.0 / RAND_MAX * 2;
        }
    }
}

void gen_vector(int n, double** vector){
    (*vector) = new double[n];
    for(int i = 0; i < n; i++){
        (*vector)[i] = -1 + rand() * 1.0 / RAND_MAX * 2;
    }
}

void print(int n, double *matrix, double *vector, int pid) {
    printf("\nprint info...p:%d \n", pid);
    for(int i = 0; i < n; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double distance(int n, double* serial_res, double* par_res){
    double dis = 0.0;
    for(int i = 0; i < n; i++){
        dis += pow((serial_res[i] - par_res[i]), 2);
    }
    return sqrtf(dis);
}

/*
 * Description: 
 * data partition, communication, calculation based on MPI programming in this function.
 * 
 * 1. call gen() on one process to generate the random matrix and vecotr.
 * 2. distribute the data to other processes.
 * 3. Implement matrix-vector mutiply
 * 4. calculate the diffenence between product vector and the value of serial(), I'll check this answer.
 */ 
void run_submat(int n, double* matrix, double* vector){
    int comm_sz, row_comm_sz, col_comm_sz, diag_comm_sz;
    int my_rank, my_row_rank, my_col_rank, my_diag_rank;
    MPI_Comm comm, row_comm, col_comm, diag_comm;
    comm = MPI_COMM_WORLD;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);
    srand((unsigned)time(NULL) + my_rank);
    int diag = 0;//标记是否为对角通信子
    int grid_n = int(sqrt(comm_sz));
    
    if(comm_sz != grid_n * grid_n || n % grid_n != 0){
        printf("n = %d must be divisible by sqrt(comm_sz) = %d\n", n, grid_n);
        exit(-1);
    }

    //Initialize communicator...
    const int d = 2;//2-dim grid
    int dims[2] = {grid_n, grid_n};
    int periods[2] = {0, 0};
    int coords[2], free_coords[2];
    int reorder = 0;
    //Create a communicator of 2-dim Cart
    MPI_Cart_create(MPI_COMM_WORLD, d, dims, periods, reorder, &comm);
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);//获取当前进程在通信子中的秩

    /* Build a communicator for each process row */
    free_coords[0] = 0, free_coords[1] = 1;
    MPI_Cart_sub(comm, free_coords, &row_comm);
    MPI_Comm_size(row_comm, &row_comm_sz);
    MPI_Comm_rank(row_comm, &my_row_rank);
    /* Build a communicator for each process col */
    free_coords[0] = 1, free_coords[1] = 0;
    MPI_Cart_sub(comm, free_coords, &col_comm);
    MPI_Comm_size(col_comm, &col_comm_sz);
    MPI_Comm_rank(col_comm, &my_col_rank);

    /* Record grid info */
    if(my_col_rank == my_row_rank) {
        diag = 1;
    }
    MPI_Cart_coords(comm, my_rank, d, coords);

    //Initialize diag communicator..
    int p_ranks[row_comm_sz];
    MPI_Group group, diag_group;
    /* Make a list of the processes in comm that are on the diagonal */
    for(int i = 0; i < row_comm_sz; i++){
        p_ranks[i] = i * (row_comm_sz + 1);
    }   
    /* Get the group underlying comm */
    MPI_Comm_group(comm, &group);
    /* Create the new group */
    MPI_Group_incl(group, row_comm_sz, p_ranks, &diag_group);
    /* Create the communicator */
    MPI_Comm_create(comm, diag_group, &diag_comm);
    if(diag) {
        MPI_Comm_size(diag_comm, &diag_comm_sz);
        MPI_Comm_rank(diag_comm, &my_diag_rank);
    } else {
        diag_comm_sz = row_comm_sz;
        my_diag_rank = -1;
    }

    int loc_m = n / col_comm_sz, loc_n = n / row_comm_sz;
    MPI_Datatype vect_mpi_t, submat_mpi_t;
    MPI_Type_vector(loc_m, loc_n, n, MPI_DOUBLE, &vect_mpi_t);
    MPI_Type_create_resized(vect_mpi_t, 0, loc_n * sizeof(double), &submat_mpi_t);
    MPI_Type_commit(&submat_mpi_t);
    MPI_Type_free(&vect_mpi_t);

    int *counts, *disp;
    counts = new int[comm_sz];
    disp = new int[comm_sz];
    for(int i = 0; i < row_comm_sz; i++){
        for(int j = 0; j < col_comm_sz; j++){
            counts[i * row_comm_sz + j] = 1;
        }
    }
    for(int i = 0; i < row_comm_sz; i++){
        for(int j = 0; j < col_comm_sz; j++){
            disp[i * row_comm_sz + j] = i * row_comm_sz * loc_m + j;
        }
    }
    
    double *loc_A, *loc_x, *loc_y, *sub_y, *serial_res, *parallel_res;
    loc_A = new double[loc_m * loc_n];
    loc_x = new double[loc_n];
    loc_y = new double[loc_m];
    sub_y = new double[loc_m];
    double beg_t[2] = {0.0, 0.0}, tot[2] = {0.0, 0.0};
    double ser_tot;
    
    if(my_diag_rank == 0) {
        gen_matrix(n, &matrix);
        gen_vector(n, &vector);
        ser_tot = MPI_Wtime();
        serial(n, matrix, vector, &serial_res);
        ser_tot = MPI_Wtime() - ser_tot;
    }

    MPI_Barrier(comm);
    beg_t[0] = MPI_Wtime();
    MPI_Scatterv(matrix, counts, disp, submat_mpi_t, loc_A, loc_m * loc_n, MPI_DOUBLE, 0, comm);
    if(my_diag_rank == 0){
        MPI_Scatter(vector, loc_n, MPI_DOUBLE, loc_x, loc_n, MPI_DOUBLE, 0, diag_comm);
    } else if (diag) {
        MPI_Scatter(vector, loc_n, MPI_DOUBLE, loc_x, loc_n, MPI_DOUBLE, 0, diag_comm);
    }
    MPI_Bcast(loc_x, loc_n, MPI_DOUBLE, coords[1], col_comm);
    
    beg_t[1] = MPI_Wtime();
    //matirx-vectoe multiply
    for(int i = 0; i < loc_m; i++){
        sub_y[i] = 0.0;
        for(int j = 0; j < loc_n; j++){
            sub_y[i] += loc_A[i * loc_n + j] * loc_x[j];
        }
    }
    beg_t[1] = MPI_Wtime() - beg_t[1];
    
    /* Now add up the partial sums in my process row and
    *  store the result in the diagonal */
    MPI_Reduce(sub_y, loc_y, loc_m, MPI_DOUBLE, MPI_SUM, coords[0], row_comm);
    //Gather data on diag
    if(my_diag_rank == 0){
        parallel_res = new double[n];
        MPI_Gather(loc_y, loc_n, MPI_DOUBLE, parallel_res, loc_n, MPI_DOUBLE, 0, diag_comm);
        beg_t[0] = MPI_Wtime() - beg_t[0];
        MPI_Reduce(beg_t, tot, 2, MPI_DOUBLE, MPI_MAX, 0, diag_comm);
        //calculate arrc
        double dis = distance(n, parallel_res, serial_res);
        printf("error(2 norm):                                %.20lf\n", dis);
        printf("time (Serial)                                 %.6lfs\n", ser_tot);
        printf("time (with MPI_Scatter/MPI_Reduce)            %.6lfs\n", tot[0]);
        printf("time (without MPI_Scatter/MPI_Reduce)         %.6lfs\n", tot[1]);
        printf("time (Scatter&Reduce)                         %.6lfs\n", tot[0] - tot[1]);
        printf("Speedup ratio(with MPI_Scatter/MPI_Reduce)    %.4lf\n", ser_tot / tot[0]);
        printf("Speedup ratio(without MPI_Scatter/MPI_Reduce) %.4lf\n", ser_tot / tot[1]);
        delete[] serial_res;
        delete[] parallel_res;
        delete[] matrix;
        delete[] vector;
    } else if (diag) {
        beg_t[0] = MPI_Wtime() - beg_t[0];
        MPI_Gather(loc_y, loc_n, MPI_DOUBLE, parallel_res, loc_n, MPI_DOUBLE, 0, diag_comm);
        MPI_Reduce(beg_t, tot, 2, MPI_DOUBLE, MPI_MAX, 0, diag_comm);
    }
    delete[] sub_y;
    delete[] loc_A;
    delete[] loc_x;
    delete[] counts;
    delete[] disp;
    MPI_Type_free(&submat_mpi_t);
    MPI_Comm_free(&comm);
    MPI_Comm_free(&row_comm);
    MPI_Comm_free(&col_comm);
    if (diag) MPI_Comm_free(&diag_comm);
    MPI_Finalize();
}   

int main(int argc, char* argv[]) { 
    if (argc < 2) {
        cout << "Usage: "<<argv[0]<<" n" << endl;
        return -1;
    }
    double *matrix;
    double *vector;
    int n = atoi(argv[1]);

    run_submat(n, matrix, vector);
    return 0;
}
