#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <timer.h>

void print_header(){
printf("n, trials, req. memory (KiB), time/trial (s), work/cycle, Read Bandwidth (GiB/s)\n");
}

void print_stats(struct timer *t, int n, int trials){
  // Matrix memory in KiB
  int req_memory = 3*n*n*sizeof(int)/1024;
  double work_per_cycle = timer_calc_work_per_cycle(t);
  // Read Bandwitdh in GiB/s
  double bandwidth = (double) ((2*n*n * sizeof(int)))/(1024*1024*1024) / t->elapsed;
  printf("%d, %d, %d, %f, %f, %f \n", n, trials, req_memory, t->elapsed/trials, work_per_cycle, bandwidth);
}

int main(int argc, char **argv) {

  if (argc < 3) {
      printf("Usage: %s <min_size> <max_size> <# of trials>\n", argv[0]);
      return 1;
  }

  size_t min_size = atol(argv[1]);
  size_t max_size = atol(argv[2]);
  int num_trials = atol(argv[3]);

  //Set random seed for matrix generation.
  srand(0);
  struct timer matrix_timer;
  print_header();
  for(size_t i = min_size; i<= max_size; i=2*i) {
    int req_memory = 3*i*i*sizeof(int);
    float *A = malloc((i*i) * sizeof(int));
    float *B = malloc((i*i) * sizeof(int));
    float *C = malloc((i*i) * sizeof(int));

    // Check if the allocation failed.
    if (A == NULL || B == NULL){
      printf("Failed to allocated matrices, memory required: %d \n)", req_memory);
      printf("Exiting...\n");
    }

    // Total work done for matrix multiply AxB (2n^3 - n^2)
    double matrix_work = (double) (2*i*i*i - i*i);

  // Generate Random initial matrix
    populate_matrix(A, i);
    populate_matrix(B, i);
    zero_matrix(C, i);
    // Warm up run
//    matmul(A, B, C, i);
//  matmul_sum(A, B, C, i);
//    matmul_strip(A, B, C, i);
    matmul_blocked(A, B, C, i);

    // Benchmarking...
    timer_start(&matrix_timer, num_trials * matrix_work);
    for (int trial = 0; trial < num_trials; trial++){
//      matmul(A, B, C, i);
//      matmul_sum(A, B, C, i);
//      matmul_strip(A, B, C, i);
      matmul_blocked(A, B, C, i);
    }
    timer_stop(&matrix_timer);
    print_stats(&matrix_timer, i, num_trials);

    free(A);
    free(B);
    free(C);
  }
}
