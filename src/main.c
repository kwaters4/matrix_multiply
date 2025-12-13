#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <timer.h>

int main(int argc, char **argv) {

  if (argc < 3) {
      printf("Usage: %s <min_size> <max_size> <# of trials>\n", argv[0]);
      return 1;
  }

  size_t min_size = atol(argv[1]);
  size_t max_size = atol(argv[2]);
  size_t num_trials = atol(argv[3]);

  //Set random seed for matrix generation.
  srand(0);
  struct timer matrix_timer;
  for(size_t i = min_size; i<= max_size; i=2*i) {
    int req_memory = 3*i*i*sizeof(int);
    int *matrix1 = malloc((i*i) * sizeof(int));
    int *matrix2 = malloc((i*i) * sizeof(int));
    int *result = malloc((i*i) * sizeof(int));

    // Check if the allocation failed.
    if (matrix1 == NULL || matrix2 == NULL){
      printf("Failed to allocated matrices, memory required: %d \n)", req_memory);
      printf("Exiting...\n");
    }

    // Total work done for matrix multiply AxB (2n^3 - n^2)
    double matrix_work = (double) (2*i*i*i - i*i);

  // Generate Random initial matrix
    populate_matrix(matrix1, i);
    populate_matrix(matrix2, i);
    generate_zero_matrix(result, i);
    timer_start(&matrix_timer, num_trials * matrix_work);
    printf("Multiplying %ldx%ld matrices... (Trials:%ld)\n",i ,i, num_trials);
    for (int trial = 0; trial < num_trials; trial ++){
//      multiply_matrices(matrix1, matrix2, result, i);
//      multiply_matrices_sum(matrix1, matrix2, result, i);
      multiply_matrices_strip(matrix1, matrix2, result, i);
    }
    timer_stop(&matrix_timer);
    double ipc = timer_calc_ipc(&matrix_timer);
    printf("Mem Req. (KiB) %d \n", req_memory/1024);
    printf("Elasped Time (s.): %f\n", matrix_timer.elapsed);
    printf("Calculated IPC: %f\n", ipc);
    printf("Read Memory Bandwidth (GiB/s): %f\n",(double) ((2*i*i * sizeof(int)))/(1024*1024*1024) / matrix_timer.elapsed);

    free(matrix1);
    free(matrix2);
    free(result);
    timer_reset(&matrix_timer);
  }
}
