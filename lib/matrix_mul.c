#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>

/**
 * @brief Allocates square 2x2 integer matrix
 *
 * @return void
 */
int* malloc_matrix_int(int const n){
//  int *matrix = malloc((n*n) * sizeof(int));
  int *matrix = aligned_alloc((size_t) 32, (size_t)(n*n) * sizeof(int));
  if (matrix == NULL){
    printf("ERROR: Failed to allocate matrix of size %dx%d\n", n, n);
    printf("Exiting...\n");
    exit(1);
  }
  return matrix;
}

/**
 * @brief Free integer matrix
 *
 * @return void
 */
void free_matrix_int(int *matrix){
  free(matrix);
}

/**
 * @brief Generates nxn zero matrix
 *
 * @return void
 */
void generate_zero_matrix(int *matrix, const int n){
    // Initialize the result matrix with 0s
  for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = 0;
        }
    }
}

/**
 * @brief Generates nxn identity matrix
 *
 * @return void
 */
void generate_identity_matrix(int *matrix, const int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
          matrix[i * n + j] = 1;
      } else {
          matrix[i * n + j] = 1;
      }
    }
  }
}

/**
 * @brief Compares two matrices to see if they are the same
 *
 * @return Returns -1 if they do not match, 0 if they do (int)
 */
int compare_matrices(const int *matrix1, const int *matrix2, const int n){
  for (int i = 0; i < n*n; i++) {
    if (matrix1[i] != matrix2[i])
      return -1;
    }
  return 0;
}

/**
 * @brief Populates a nxn random matrix with random between -MIN and MAX
 *
 * @return void)
 */
void populate_matrix(int *matrix, const int n) {
  for (int i = 0; i < n*n; i++) {
    matrix[i] = (rand() % (MAX - MIN + 1)) + MIN;
  }
}

/**
 * @brief Prints nxn matrix
 *
 * @return Returns 0 if successful (int)
 */
int print_matrix(const int *matrix, const int n) {
  printf("Printed matrix (%dx%d):\n",n, n);
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          printf("%d ", matrix[i * n + j]);
      }
      printf("\n");
  }
  return 0;
}

/**
 * @brief Multiplies two matrices together and puts the result in a third
 *
 * @return void 0
 */
void multiply_matrices(const int *matrix1, const int *matrix2, int *result, const int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i * n + j] += matrix1[i * n + k] * matrix2[k * n + j];
            }
        }
    }
}

/**
 * @brief Multiplies two matrices together and puts the result in a third
 *
 * @return void 0
 */
void multiply_matrices_sum(const int *matrix1, const int *matrix2, int *result, const int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int sum = 0;
      for (int k = 0; k < n; k++) {
        sum = matrix1[i * n + k] * matrix2[k * n + j] + sum;
      }
    result[i * n + j] = sum;
    }
  }
}

/**
 * @brief Multiplies two matrices together and puts the result in a third
 *
 * @return void 0
 */
void multiply_matrices_strip(const int *matrix1, const int *matrix2, int *result, const int n){
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        result[i * n + j] += matrix1[i * n + k] * matrix2[k * n + j];
      }
    }
  }
}


void multiply_matrices_blocked(const int *matrix1, const int *matrix2, int *result, const int n)
{
    for (int ii = 0; ii < n; ii+= BLOCK_SIZE) {
      for (int kk = 0; kk < n; kk+= BLOCK_SIZE) {
        for (int jj = 0; jj < n; jj+= BLOCK_SIZE) {
          int limit_i = ((ii + BLOCK_SIZE) < n) ? (ii + BLOCK_SIZE) : n;
          int limit_j = ((jj + BLOCK_SIZE) < n) ? (jj + BLOCK_SIZE) : n;
          int limit_k = ((kk + BLOCK_SIZE) < n) ? (kk + BLOCK_SIZE) : n;
          for (int i = ii; i < limit_i; ++i) {
            for (int k = kk; k < limit_k; ++k) {
              int ki = i * n + k;
              for (int j = jj; j < limit_j; j++) {
                result[i * n + j] += matrix1[ki] * matrix2[k * n + j];
              }
            }
          }
        }
      }
    }
}

