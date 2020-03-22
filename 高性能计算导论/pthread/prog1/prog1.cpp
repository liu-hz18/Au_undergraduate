#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <omp.h>

void Usage(const char* prog_name[] /* in */) {
   fprintf(stderr, "usage: %s ", prog_name[0]); 
   fprintf(stderr, "<thread_num>\n");
   exit(0);
}  /* Usage */


void Gen_data(
        float   min_meas    /* in  */, 
        float   max_meas    /* in  */, 
        float*  data      /* out */,
        int     data_count  /* in  */) {
   int i;

   srand((unsigned)time(NULL));
   for (i = 0; i < data_count; i++)
      data[i] = min_meas + (max_meas - min_meas) * random() / ((double) RAND_MAX);

#  ifdef DEBUG
   printf("data = ");
   for (i = 0; i < data_count; i++)
      printf("%4.3f ", data[i]);
   printf("\n");
#  endif
}  /* Gen_data */


void Gen_bins(
      float min_meas      /* in  */, 
      float max_meas      /* in  */, 
      float*bin_maxes   /* out */, 
      int*  bin_counts  /* out */, 
      int   bin_count     /* in  */) {
   float bin_width;
   int   i;

   bin_width = (max_meas - min_meas)/bin_count;

   for (i = 0; i < bin_count; i++) {
      bin_maxes[i] = min_meas + (i+1)*bin_width;
      bin_counts[i] = 0;
   }

#  ifdef DEBUG
   printf("bin_maxes = ");
   for (i = 0; i < bin_count; i++)
      printf("%4.3f ", bin_maxes[i]);
   printf("\n");
#  endif
}  /* Gen_bins */


int Which_bin(
      float   data          /* in */, 
      float*  bin_maxes   /* in */, 
      int     bin_count     /* in */, 
      float   min_meas      /* in */) {
   int bottom = 0, top =  bin_count-1;
   int mid;
   float bin_max, bin_min;

   while (bottom <= top) {
      mid = (bottom + top)/2;
      bin_max = bin_maxes[mid];
      bin_min = (mid == 0) ? min_meas: bin_maxes[mid-1];
      if (data >= bin_max) 
         bottom = mid+1;
      else if (data < bin_min)
         top = mid-1;
      else
         return mid;
   }

   /* Whoops! */
   fprintf(stderr, "Data = %f doesn't belong to a bin!\n", data);
   fprintf(stderr, "Quitting\n");
   exit(-1);
}  /* Which_bin */

void Print_histo(
        float*  bin_maxes   /* in */, 
        int*    bin_counts  /* in */, 
        int     bin_count     /* in */, 
        float   min_meas      /* in */) {
   int i, j;
   float bin_max, bin_min;

   for (i = 0; i < bin_count; i++) {
      bin_max = bin_maxes[i];
      bin_min = (i == 0) ? min_meas: bin_maxes[i-1];
      printf("%.3f-%.3f:\t", bin_min, bin_max);
      for (j = 0; j < bin_counts[i]; j++)
         printf("X");
      printf("\n");
   }
}  /* Print_histo */

int main(int argc, const char* argv[]){
    int bin_count, i, bin, data_count, threadnum;
    float min_meas, max_meas;
    float *bin_maxes, *data;
    int *bin_counts, *local_count;

    /* Check and get command line args */
    if (argc != 2) Usage(argv); 
    threadnum = atoi(argv[1]);
    puts("Enter the number of bins");
    scanf("%d", &bin_count);
    puts("Enter the minimum measurement");
    scanf("%f", &min_meas);
    puts("Enter the maximum measurement");
    scanf("%f", &max_meas);
    puts("Enter the number of data");
    scanf("%d", &data_count);
    printf("created %d threads...\n", threadnum);

    /* Allocate arrays needed */
    bin_maxes = new float[bin_count];
    bin_counts = new int[bin_count];
    data = new float[data_count];
    local_count = new int[bin_count * threadnum];
    memset(local_count, 0, bin_count * threadnum * sizeof(int));
    
    /* Generate the data */
    Gen_data(min_meas, max_meas, data, data_count);

    /* Create bins for storing counts */
    Gen_bins(min_meas, max_meas, bin_maxes, bin_counts, bin_count);

    /* Count number of values in each local bin */
#   pragma omp parallel for num_threads(threadnum)
    for (i = 0; i < data_count; i++) {
        int my_rank = omp_get_thread_num();
        bin = Which_bin(data[i], bin_maxes, bin_count, min_meas);
#       ifdef DEBUG
        printf("Thread %d found data %5.2f in bin %d\n", my_rank, data[i], bin);
#       endif
        local_count[my_rank * bin_count + bin]++;
    }

#   pragma omp parallel for num_threads(threadnum)
    for(int i = 0; i < bin_count; i++){
        for(int j = 0; j < threadnum; j++){
            bin_counts[i] += local_count[j * bin_count + i];
        }
    }

#   ifdef DEBUG
    printf("bin_counts = ");
    for (i = 0; i < bin_count; i++)
        printf("%d ", bin_counts[i]);
    printf("\n");
#  endif

    /* Print the histogram */
    Print_histo(bin_maxes, bin_counts, bin_count, min_meas);

    delete[] data;
    delete[] bin_maxes;
    delete[] bin_counts;
    delete[] local_count;
    return 0;
}
