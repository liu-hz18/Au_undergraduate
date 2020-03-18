/* File:     mpi_vector_add.c
 *
 * Purpose:  Implement parallel vector addition using a block
 *           distribution of the vectors.  
 *           This version also
 *           illustrates the use of MPI_Scatter and MPI_Gather.
 *
 * Compile:  mpicc -g -Wall -o mpi_vector_add mpi_vector_add.c
 * Run:      mpiexec -n <comm_sz> ./vector_add
 *
 * Input:    The order of the vectors, n, and the vectors x and y
 * Output:   The sum vector z = x+y
 *
 * Notes:     
 * 1.  DEBUG compile flag.    
 * 2.  This program does fairly extensive error checking.  When
 *     an error is detected, a message is printed and the processes
 *     quit.  Errors detected are incorrect values of the vector
 *     order (negative or not evenly divisible by comm_sz), and
 *     malloc failures.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

void Check_for_error(int local_ok, char fname[], char message[], 
      MPI_Comm comm);
void Read_n(int* n_p, int* local_n_p, int my_rank, int comm_sz, MPI_Comm comm);
void Allocate_vectors(double** local_x_pp, double** local_y_pp, 
      double** local_z_pp, int local_n, MPI_Comm comm);
void Read_vector(double local_a[], int local_n, int n, char vec_name[], 
      int count[], int disp[], int my_rank, MPI_Comm comm);
void Print_vector(double local_b[], int local_n, int n, char title[],
      int count[], int disp[], int my_rank, MPI_Comm comm);
void Parallel_vector_sum(double local_x[], double local_y[],
      double local_z[], int local_n);
void Allocate_count_disp(int** count, int** disp, int n, 
      int my_rank, int comm_sz, MPI_Comm comm);
void gen(int n, double** vec);

/*-------------------------------------------------------------------*/
int main(void) {
   int n, local_n;
   int comm_sz, my_rank;
   double *local_x, *local_y, *local_z;
   int *count, *disp;
   MPI_Comm comm;

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &comm_sz);
   MPI_Comm_rank(comm, &my_rank);
   srand(my_rank + time(NULL));

   Read_n(&n, &local_n, my_rank, comm_sz, comm);
#  ifdef DEBUG
   printf("Proc %d > n = %d, local_n = %d\n", my_rank, n, local_n);
#  endif
   Allocate_count_disp(&count, &disp, n, my_rank, comm_sz, comm);
   MPI_Bcast(count, comm_sz, MPI_INT, 0, comm);
   MPI_Bcast(disp, comm_sz, MPI_INT, 0, comm);
   Allocate_vectors(&local_x, &local_y, &local_z, local_n, comm);
   
   Read_vector(local_x, local_n, n, "x", count, disp, my_rank, comm);
   Print_vector(local_x, local_n, n, "x is", count, disp, my_rank, comm);
   Read_vector(local_y, local_n, n, "y", count, disp, my_rank, comm);
   Print_vector(local_y, local_n, n, "y is", count, disp, my_rank, comm);
   
   Parallel_vector_sum(local_x, local_y, local_z, local_n);
   Print_vector(local_z, local_n, n, "The sum is", count, disp, my_rank, comm);

   free(local_x);
   free(local_y);
   free(local_z);

   MPI_Finalize();

   return 0;
}  /* main */


void gen(int n, double** vec){
   int i;
   for(i = 0; i < n; i++){
      (*vec)[i] = -1.0 + rand() * 1.0 / RAND_MAX * 2;
   }
}

/*-------------------------------------------------------------------
 * Function:  Allocate_count_disp
 * Purpose:   This function generates count[] and disp[] for MPI_Scatterv() and MPI_Gatherv()
 *            Calculate count[] which keeps the number allocated to each process
 *            and disp[] which is the address offset of each process.
 *            Then broadcast count[] and disp[] to all processes.
 *            
 * In args:   n:          size of global vector
 *            my_rank:    process rank in communicator
 *            comm_sz:    number of processes in communicator
 *            comm:       communicator containing all the processes
 *                        calling Read_n
 *
 * Out args:  count:      keeps the number allocated to each process 
 *            disp:       the address offset of each process
 */
void Allocate_count_disp(
      int**     count     /* out */, 
      int**     disp      /* out */, 
      int       n         /* in  */,
      int       my_rank   /* in  */, 
      int       comm_sz   /* in  */,
      MPI_Comm  comm      /* in  */){
   int i;
   (*count) = malloc(comm_sz * sizeof(int));
   (*disp) = malloc(comm_sz * sizeof(int));
   if (my_rank == 0) {
      int overflow = n - (n / comm_sz) * comm_sz;
      int base = n / comm_sz;
      for(i = 0; i < comm_sz; i++){
         (*count)[i] = base;
      }
      for(i = 0; i < overflow; i++){
         (*count)[i] += 1;
      }
      for((*disp)[0] = 0, i = 1; i < comm_sz; i++){
         (*disp)[i] = (*disp)[i-1] + (*count)[i-1];
      }
   }
}


/*-------------------------------------------------------------------
 * Function:  Check_for_error
 * Purpose:   Check whether any process has found an error.  If so,
 *            print message and terminate all processes.  Otherwise,
 *            continue execution.
 * In args:   local_ok:  1 if calling process has found an error, 0
 *               otherwise
 *            fname:     name of function calling Check_for_error
 *            message:   message to print if there's an error
 *            comm:      communicator containing processes calling
 *                       Check_for_error:  should be MPI_COMM_WORLD.
 *
 * Note:
 *    The communicator containing the processes calling Check_for_error
 *    should be MPI_COMM_WORLD.
 */
void Check_for_error(
      int       local_ok   /* in */, 
      char      fname[]    /* in */,
      char      message[]  /* in */, 
      MPI_Comm  comm       /* in */) {
   int ok;

   MPI_Allreduce(&local_ok, &ok, 1, MPI_INT, MPI_MIN, comm);
   if (ok == 0) {
      int my_rank;
      MPI_Comm_rank(comm, &my_rank);
      if (my_rank == 0) {
         fprintf(stderr, "Proc %d > In %s, %s\n", my_rank, fname, 
               message);
         fflush(stderr);
      }
      MPI_Finalize();
      exit(-1);
   }
}  /* Check_for_error */


/*-------------------------------------------------------------------
 * Function:  Read_n
 * Purpose:   Get the order of the vectors from stdin on proc 0 and
 *            broadcast to other processes.
 * In args:   my_rank:    process rank in communicator
 *            comm_sz:    number of processes in communicator
 *            comm:       communicator containing all the processes
 *                        calling Read_n
 * Out args:  n_p:        global value of n
 *            local_n_p:  local value of n = n/comm_sz
 */
void Read_n(
      int*      n_p        /* out */, 
      int*      local_n_p  /* out */, 
      int       my_rank    /* in  */, 
      int       comm_sz    /* in  */,
      MPI_Comm  comm       /* in  */) {
   int local_ok = 1;
   char *fname = "Read_n";
   
   if (my_rank == 0) {
      printf("What's the order of the vectors?\n");
      scanf("%d", n_p);
   }
   MPI_Bcast(n_p, 1, MPI_INT, 0, comm);
   if (*n_p <= 0) local_ok = 0;
   Check_for_error(local_ok, fname, "n should be > 0", comm);
   (*local_n_p) = (*n_p) / comm_sz;
   if(my_rank < (*n_p) % comm_sz){
      (*local_n_p) += 1;
   }
}  /* Read_n */


/*-------------------------------------------------------------------
 * Function:  Allocate_vectors
 * Purpose:   Allocate storage for x, y, and z
 * In args:   local_n:  the size of the local vectors
 *            comm:     the communicator containing the calling processes
 * Out args:  local_x_pp, local_y_pp, local_z_pp:  pointers to memory
 *               blocks to be allocated for local vectors
 *
 * Errors:    One or more of the calls to malloc fails
 */
void Allocate_vectors(
      double**   local_x_pp  /* out */, 
      double**   local_y_pp  /* out */,
      double**   local_z_pp  /* out */, 
      int        local_n     /* in  */,
      MPI_Comm   comm        /* in  */) {
   int local_ok = 1;
   char* fname = "Allocate_vectors";

   *local_x_pp = malloc(local_n * sizeof(double));
   *local_y_pp = malloc(local_n * sizeof(double));
   *local_z_pp = malloc(local_n * sizeof(double));

   if (*local_x_pp == NULL || *local_y_pp == NULL || 
       *local_z_pp == NULL) local_ok = 0;
   Check_for_error(local_ok, fname, "Can't allocate local vector(s)", 
         comm);
}  /* Allocate_vectors */


/*-------------------------------------------------------------------
 * Function:   Read_vector
 * Purpose:    Read a vector from stdin on process 0 and distribute
 *             among the processes using a block distribution.
 * In args:    local_n:  size of local vectors
 *             n:        size of global vector
 *             vec_name: name of vector being read (e.g., "x")
 *             my_rank:  calling process' rank in comm
 *             comm:     communicator containing calling processes
 * Out arg:    local_a:  local vector read
 *
 * Errors:     if the malloc on process 0 for temporary storage
 *             fails the program terminates
 *
 * Note: 
 *    This function assumes a block distribution and the order
 *   of the vector evenly divisible by comm_sz.
 */
void Read_vector(
      double    local_a[]   /* out */, 
      int       local_n     /* in  */, 
      int       n           /* in  */,
      char      vec_name[]  /* in  */,
      int       count[]     /* in  */, 
      int       disp[]      /* in  */,
      int       my_rank     /* in  */, 
      MPI_Comm  comm        /* in  */) {

   double* a = NULL;
   int i;
   int local_ok = 1;
   char* fname = "Read_vector";
   //read the total vector in process 0, and scatter it to all processes.
   if (my_rank == 0) {
      a = malloc(n * sizeof(double));
      if (a == NULL) local_ok = 0;
      Check_for_error(local_ok, fname, "Can't allocate temporary vector", comm);
      //printf("Enter the vector %s\n", vec_name);
      //for (i = 0; i < n; i++)
      //   scanf("%lf", &a[i]);
      gen(n, &a);
      MPI_Scatterv(a, count, disp, MPI_DOUBLE, local_a, count[my_rank], MPI_DOUBLE, 0,
         comm);
      free(a);
   } else {
      Check_for_error(local_ok, fname, "Can't allocate temporary vector", 
            comm);
      MPI_Scatterv(a, count, disp, MPI_DOUBLE, local_a, count[my_rank], MPI_DOUBLE, 0,
         comm);
   }
}  /* Read_vector */


/*-------------------------------------------------------------------
 * Function:  Print_vector
 * Purpose:   Print a vector that has a block distribution to stdout
 * In args:   local_b:  local storage for vector to be printed
 *            local_n:  order of local vectors
 *            n:        order of global vector (local_n*comm_sz)
 *            title:    title to precede print out
 *            comm:     communicator containing processes calling
 *                      Print_vector
 *
 * Error:     if process 0 can't allocate temporary storage for
 *            the full vector, the program terminates.
 *
 * Note:
 *    Assumes order of vector is evenly divisible by the number of
 *    processes
 */
void Print_vector(
      double    local_b[]  /* in */, 
      int       local_n    /* in */, 
      int       n          /* in */, 
      char      title[]    /* in */,
      int       count[]    /* in */,
      int       disp[]     /* in */, 
      int       my_rank    /* in */,
      MPI_Comm  comm       /* in */) {

   double* b = NULL;
   int i;
   int local_ok = 1;
   char* fname = "Print_vector";

   if (my_rank == 0) {
      b = malloc(n * sizeof(double));
      if (b == NULL) local_ok = 0;
      Check_for_error(local_ok, fname, "Can't allocate temporary vector", 
            comm);
      MPI_Gatherv(local_b, count[my_rank], MPI_DOUBLE, b, count, disp, MPI_DOUBLE,
            0, comm);
      printf("%s\n", title);
      for (i = 0; i < n; i++)
         printf("%f ", b[i]);
      printf("\n");
      free(b);
   } else {
      Check_for_error(local_ok, fname, "Can't allocate temporary vector", 
            comm);
      MPI_Gatherv(local_b, count[my_rank], MPI_DOUBLE, b, count, disp, MPI_DOUBLE,
            0, comm);
   }
}  /* Print_vector */


/*-------------------------------------------------------------------
 * Function:  Parallel_vector_sum
 * Purpose:   Add a vector that's been distributed among the processes
 * In args:   local_x:  local storage of one of the vectors being added
 *            local_y:  local storage for the second vector being added
 *            local_n:  the number of components in local_x, local_y,
 *                      and local_z
 * Out arg:   local_z:  local storage for the sum of the two vectors
 */
void Parallel_vector_sum(
      double  local_x[]  /* in  */, 
      double  local_y[]  /* in  */, 
      double  local_z[]  /* out */, 
      int     local_n    /* in  */) {
   int local_i;

   for (local_i = 0; local_i < local_n; local_i++)
      local_z[local_i] = local_x[local_i] + local_y[local_i];
}  /* Parallel_vector_sum */
