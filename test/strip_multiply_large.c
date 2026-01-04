#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <test_library.h>

int main() {
  int *A, *B;
  int *test_result_naive;
  int *test_result_strip;
  int ret;

  int min = 2;
  int max = 512;

  for (int n = min; n <= max; n = 2*n){
    A = malloc_matrix_int32(n);
    B = malloc_matrix_int32(n);
    populate_matrix(A, n);
    populate_matrix(B, n);
    test_result_naive = malloc_matrix_int32(n);
    matmul(A, B, test_result_naive, n);

    test_result_strip = malloc_matrix_int32(n);
    matmul_strip(A, B, test_result_strip, n);
    ret = compare_matrices(test_result_naive, test_result_strip, n);
    printf("%dx%d ret value %d\n", n, n, ret);

    free_matrix(test_result_naive);
    free_matrix(test_result_strip);
    if(ret != 0) {
      printf("ERROR: %dx%d failed %d\n", n, n, ret);
      return -1;
    }
  }
  if(ret == 0) {
      return 0;
  }

}

