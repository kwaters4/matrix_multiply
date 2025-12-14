#include <stdio.h>
#include <stdlib.h>

#include <test_library.h>
#include <matrix_mul.h>

/**
 * @brief Generates nxn test matrix
 *
 * Starts at matrix[0][0] with 1 and goes up until 10,
 * then starts over at 1
 *
 * @return void
 */
void test_nxn_A(int *matrix, int n){
  // | 1 2 |
  // | 3 4 |
  int val = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (val == 10) {
         val = 1;
        }
        matrix[i * n + j] = val % 10;
        val++;
    }
  }
}

/**
 * @brief Generates nxn test matrix
 *
 * Starts at matrix[0][0] with 10 and goes down until 1,
 * then starts over at 10
 *
 * @return void
 */
void test_nxn_B(int *matrix, int n){
  // | 9 8 |
  // | 7 6 |
  int val = 9;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (val == 0) {
       val = 9;
      }
      matrix[i * n + j] = val % 10;
      val--;
    }
  }
}
void set_2x2_test_matrix(int *test_result){
  test_result[0] = 23;
  test_result[1] = 20;
  test_result[2] = 55;
  test_result[3] = 48;
}

void set_3x3_test_matrix(int *test_result){
  test_result[0] = 30;
  test_result[1] = 24;
  test_result[2] = 18;
  test_result[3] = 84;
  test_result[4] = 69;
  test_result[5] = 54;
  test_result[6] = 138;
  test_result[7] = 114;
  test_result[8] = 90;
}

void set_4x4_test_matrix(int *test_result){
  test_result[0] = 46;
  test_result[1] = 63;
  test_result[2] = 53;
  test_result[3] = 43;
  test_result[4] = 130;
  test_result[5] = 167;
  test_result[6] = 141;
  test_result[7] = 115;
  test_result[8] = 106;
  test_result[9] = 109;
  test_result[10] = 94;
  test_result[11] = 79;
  test_result[12] = 109;
  test_result[13] = 141;
  test_result[14] = 119;
  test_result[15] = 97;
}

int determined_test_mult(int *test_result, int n, enum Mult_Algo algo){
  int ret;
  int *matrix1 = malloc_matrix_int(n);
  int *matrix2 = malloc_matrix_int(n);
  int *result = malloc_matrix_int(n);

  test_nxn_A(matrix1, n);
  test_nxn_B(matrix2, n);
  generate_zero_matrix(result, n);

  switch(algo) {
    case NAIVE:
      multiply_matrices(matrix1, matrix2, result, n);
      break;
    case SUM:
      multiply_matrices_sum(matrix1, matrix2, result, n);
      break;
    case STRIP:
      multiply_matrices_strip(matrix1, matrix2, result, n);
      break;
    case BLOCKED:
      multiply_matrices_blocked(matrix1, matrix2, result, n);
      break;
    default:
      printf("ERROR: No valid multiplication algorithm selected.\n");
      return -1;
  }

  ret = compare_matrices(result, test_result, n);
  if(ret < 0){
    printf("ERROR: Multiplication failed for %dx%d matrices.\n",n, n);
  }

  free_matrix_int(matrix1);
  free_matrix_int(matrix2);
  free_matrix_int(result);
  return ret;
}

