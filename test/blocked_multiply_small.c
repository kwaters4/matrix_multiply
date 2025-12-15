#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>
#include <test_library.h>

int main() {
  int n;
  int *test_result;
  int ret1, ret2, ret3;

  enum Mult_Algo algo = BLOCKED;
  // Test pre-calculated 2x2 matrix
  n = 2;
  test_result = malloc_matrix_int(n);
  set_2x2_test_matrix(test_result);
  ret1 = determined_test_mult(test_result, n, algo);
  free_matrix_int(test_result);

  // Test pre-calculated 3x3 matrix
  n = 3;
  test_result = malloc_matrix_int(n);
  set_3x3_test_matrix(test_result);
  ret2 = determined_test_mult(test_result, n, algo);
  free_matrix_int(test_result);

  // Test pre-calculated 4x4 matrix
  n = 4;
  test_result = malloc_matrix_int(n);
  set_4x4_test_matrix(test_result);
  ret3 = determined_test_mult(test_result, n, algo);
  free_matrix_int(test_result);

  if((ret1 + ret2 + ret3) == 0){
      return 0;
  }
  else{
    return -1;
  }

}

