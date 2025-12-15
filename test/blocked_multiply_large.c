#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <test_library.h>

int main() {
  int *matrix1, *matrix2;
  int *test_result_naive;
  int *test_result_block;
  int ret;

  int min = 32;
  int max = 512;

  for (int n = min; n <= max; n = 2*n){
    matrix1 = malloc_matrix_int(n);
    matrix2 = malloc_matrix_int(n);
    populate_matrix(matrix1, n);
    populate_matrix(matrix2, n);
    test_result_naive = malloc_matrix_int(n);
    multiply_matrices(matrix1, matrix2, test_result_naive, n);

    test_result_block = malloc_matrix_int(n);
    multiply_matrices_blocked(matrix1, matrix2, test_result_block, n);
    ret = compare_matrices(test_result_naive, test_result_block, n);
    printf("%dx%d ret value %d\n", n, n, ret);
    print_matrix(test_result_naive, n);
    print_matrix(test_result_block, n);

    free_matrix_int(test_result_naive);
    free_matrix_int(test_result_block);
    if(ret != 0) {
      printf("ERROR: %dx%d failed %d\n", n, n, ret);
      return -1;
    }
  }
  if(ret == 0) {
      return 0;
  }

}

