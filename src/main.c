#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <timer.h>

int main(int argc, char **argv) {

  if (argc < 3) {
      printf("Usage: %s <min_size> <max_size>\n", argv[0]);
      return 1;
  }

  size_t min_size = atol(argv[1]);
  size_t max_size = atol(argv[2]);

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

    double matrix_work = (double) (2*i*i*i - i*i);
    printf("Work done: %f \n", matrix_work);

  // Generate Random initial matrix
    srand(0);
    populate_matrix(matrix1, i);
    populate_matrix(matrix2, i);
    generate_zero_matrix(result, i);
    printf("Multiplying %dx%d matrices...\n",i ,i);
    timer_start(&matrix_timer, matrix_work);
    multiply_matrices(matrix1, matrix2, result, i);
    timer_stop(&matrix_timer);
    double ipc = timer_calc_ipc(&matrix_timer);
    printf("Calculated IPC: %f\n", ipc);

    free(matrix1);
    free(matrix2);
    free(result);
    timer_reset(&matrix_timer);
  }
}
