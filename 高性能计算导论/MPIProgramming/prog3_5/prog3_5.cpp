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
 *      mpic++ -g -Wall -o main prog3_56.cpp
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
	for(int i = 0; i < n; i++) {
		(*result)[i] = 0.0;
	}
	for(int i = 0; i < n; i++) {
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
void gen(int n, double **matrix, double **vector) {
	(*matrix) = new double[n * n];
	srand((unsigned)time(0));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			(*matrix)[i * n + j] = -1 + rand() * 1.0 / RAND_MAX * 2;
		}
	}
	(*vector) = new double[n];
	for(int i = 0; i < n; i++) {
		(*vector)[i] = -1 + rand() * 1.0 / RAND_MAX * 2;
	}
}

void print(int n, double *matrix, double *vector) {
	for(int i = 0; i < n; i++) {
		cout << vector[i] << endl;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << matrix[i * n + j] << " ";
		}
		cout << endl;
	}
}

void free(int n, double *matrix, double *vector) {
	delete[] vector;
	delete[] matrix;
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
void run_col(int n, double* matrix, double* vector) {
    int my_rank, comm_sz;
    MPI_Comm comm;
    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);
    double beg_t[2], tot[2], ser_tot;
    if(n % comm_sz != 0){
        printf("n = %d must be divisible by comm_sz = %d\n", n, comm_sz);
        exit(-1);
    }

    int local_n = n / comm_sz;
    MPI_Datatype vec_t, col_t;
    MPI_Type_vector(n, local_n, n, MPI_DOUBLE, &vec_t);
    MPI_Type_create_resized(vec_t, 0, local_n * sizeof(double), &col_t);
    MPI_Type_commit(&col_t);
    MPI_Type_free(&vec_t);

    double* loc_A, *loc_vec, *loc_res, *serial_res, *result;
    loc_A = new double[n * local_n];
    loc_vec = new double[local_n];
    
    if(my_rank == 0){
        gen(n, &matrix, &vector);
        ser_tot = MPI_Wtime();
        serial(n, matrix, vector, &serial_res);
        ser_tot = MPI_Wtime() - ser_tot;
        result = new double[n];
    }
    loc_res = new double[n];
    
    MPI_Barrier(comm);
    beg_t[0] = MPI_Wtime();
    MPI_Scatter(matrix, 1, col_t, loc_A, n * local_n, MPI_DOUBLE, 0, comm);
    MPI_Scatter(vector, local_n, MPI_DOUBLE, loc_vec, local_n, MPI_DOUBLE, 0, comm);
    
    beg_t[1] = MPI_Wtime();
    for(int i = 0; i < n; i++){
        loc_res[i] = 0.0;
        for(int j = 0; j < local_n; j++){
            loc_res[i] += loc_A[i * local_n + j] * loc_vec[j];
        }
    }
    beg_t[1] = MPI_Wtime() - beg_t[1];
    //Redice to p0
    MPI_Reduce(loc_res, result, n, MPI_DOUBLE, MPI_SUM, 0, comm);
    beg_t[0] = MPI_Wtime() - beg_t[0];
    MPI_Reduce(beg_t, tot, 2, MPI_DOUBLE, MPI_MAX, 0, comm);
    if(my_rank == 0){
        //calculate arrc
        double dis = distance(n, result, serial_res);
        printf("error(2 norm):                                %.20lf\n", dis);
        printf("time (Serial)                                 %.6lfs \n", ser_tot);
        printf("time (with MPI_Scatter/MPI_Reduce)            %.6lfs \n", tot[0]);
        printf("time (without MPI_Scatter/MPI_Reduce)         %.6lfs \n", tot[1]);
        printf("time (Scatter&Reduce)                         %.6lfs \n", tot[0] - tot[1]);
        printf("Speedup ratio(with MPI_Scatter/MPI_Reduce)    %.4lf \n", ser_tot / tot[0]);
        printf("Speedup ratio(without MPI_Scatter/MPI_Reduce) %.4lf \n", ser_tot / tot[1]);
        delete[] serial_res;
        delete[] result;
        free(n, matrix, vector);
    }
    delete[] loc_res;
    delete[] loc_A;
    delete[] loc_vec;
    MPI_Type_free(&col_t);
    MPI_Finalize();
}


int main(int argc, char* argv[]) { 
    if (argc < 2) {
        cout << "Usage: "<< argv[0] <<" n" << endl;
        return -1;
    }
    
    double *matrix;
    double *vector;

    int n = atoi(argv[1]);
    run_col(n, matrix, vector);
    return 0;
}
