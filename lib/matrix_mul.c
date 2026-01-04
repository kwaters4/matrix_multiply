#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <matrix_mul.h>

#include <stdio.h>

/**
 * @brief Allocates square nxn integer matrix
 *
 * @return void
 */
int* malloc_matrix_int32(int const n){
//  int *matrix = malloc((n*n) * sizeof(int));
  int *matrix = aligned_alloc((size_t) 32, (size_t)(n*n) * sizeof(int32_t));
  if (matrix == NULL){
    printf("ERROR: Failed to allocate matrix of size %dx%d\n", n, n);
    printf("Exiting...\n");
    exit(1);
  }
  return matrix;
}

/**
 * @brief Free matrix
 *
 * @return void
 */
#define DEFINE_FREE_MATRIX(TYPE, NAME)                                      \
void free_matrix_##NAME(TYPE *matrix){                                      \
  free(matrix);                                                             \
}
DEFINE_FREE_MATRIX(int8_t, int8)
DEFINE_FREE_MATRIX(int16_t, int16)
DEFINE_FREE_MATRIX(int32_t, int32)
DEFINE_FREE_MATRIX(int64_t, int64)
DEFINE_FREE_MATRIX(uint8_t, uint8)
DEFINE_FREE_MATRIX(uint16_t, uint16)
DEFINE_FREE_MATRIX(uint32_t, uint32)
DEFINE_FREE_MATRIX(uint64_t, uint64)
DEFINE_FREE_MATRIX(float, float)
DEFINE_FREE_MATRIX(double, double)

/**
 * @brief Generates nxn zero matrix
 *
 * @return void
 */
#define DEFINE_ZERO_MATRIX(TYPE, NAME)                                      \
void zero_matrix_##NAME(TYPE *A, const int n){                              \
  memset(A,0, n*n);                                                         \
}

DEFINE_ZERO_MATRIX(int8_t, int8)
DEFINE_ZERO_MATRIX(int16_t, int16)
DEFINE_ZERO_MATRIX(int32_t, int32)
DEFINE_ZERO_MATRIX(int64_t, int64)
DEFINE_ZERO_MATRIX(uint8_t, uint8)
DEFINE_ZERO_MATRIX(uint16_t, uint16)
DEFINE_ZERO_MATRIX(uint32_t, uint32)
DEFINE_ZERO_MATRIX(uint64_t, uint64)
DEFINE_ZERO_MATRIX(float, float)
DEFINE_ZERO_MATRIX(double, double)

/**
 * @brief Generates nxn identity matrix
 *
 * @return void
 */
#define DEFINE_IDENTITY_MATRIX(TYPE, NAME)                                   \
void identity_matrix_##NAME(TYPE *A, const int n){                           \
  for (int i = 0; i < n; i++) {                                              \
    for (int j = 0; j < n; j++) {                                            \
      if (i == j) {                                                          \
          A[i * n + j] = 1;                                                  \
      } else {                                                               \
          A[i * n + j] = 0;                                                  \
      }                                                                      \
    }                                                                        \
  }                                                                          \
}

DEFINE_IDENTITY_MATRIX(int8_t, int8)
DEFINE_IDENTITY_MATRIX(int16_t, int16)
DEFINE_IDENTITY_MATRIX(int32_t, int32)
DEFINE_IDENTITY_MATRIX(int64_t, int64)
DEFINE_IDENTITY_MATRIX(uint8_t, uint8)
DEFINE_IDENTITY_MATRIX(uint16_t, uint16)
DEFINE_IDENTITY_MATRIX(uint32_t, uint32)
DEFINE_IDENTITY_MATRIX(uint64_t, uint64)
DEFINE_IDENTITY_MATRIX(float, float)
DEFINE_IDENTITY_MATRIX(double, double)

/**
 * @brief Compares two matrices to see if they are the same
 *
 * @return Returns -1 if they do not match, 0 if they do (int)
 */
#define DEFINE_COMPARE_MATRICES(TYPE, NAME)                                    \
int compare_matrices_##NAME(const TYPE *A, const TYPE *B, const int n){        \
  for (int i = 0; i < n*n; i++) {                                              \
    if (A[i] != B[i])                                                          \
      return -1;                                                               \
    }                                                                          \
  return 0;                                                                    \
}
DEFINE_COMPARE_MATRICES(int8_t, int8)
DEFINE_COMPARE_MATRICES(int16_t, int16)
DEFINE_COMPARE_MATRICES(int32_t, int32)
DEFINE_COMPARE_MATRICES(int64_t, int64)
DEFINE_COMPARE_MATRICES(uint8_t, uint8)
DEFINE_COMPARE_MATRICES(uint16_t, uint16)
DEFINE_COMPARE_MATRICES(uint32_t, uint32)
DEFINE_COMPARE_MATRICES(uint64_t, uint64)
DEFINE_COMPARE_MATRICES(float, float)
DEFINE_COMPARE_MATRICES(double, double)

/**
 * @brief Populates a nxn random matrix with random between -MIN and MAX
 *
 * @return void)
 */
#define DEFINE_POPULATE_MATRIX(TYPE, NAME)                             \
void populate_matrix_##NAME(TYPE *A, const int n) {                    \
  for (int i = 0; i < n*n; i++) {                                      \
    A[i] = (TYPE)(rand() % (MAX - MIN + 1)) + MIN;                     \
  }                                                                    \
}
DEFINE_POPULATE_MATRIX(int8_t, int8)
DEFINE_POPULATE_MATRIX(int16_t, int16)
DEFINE_POPULATE_MATRIX(int32_t, int32)
DEFINE_POPULATE_MATRIX(int64_t, int64)
DEFINE_POPULATE_MATRIX(uint8_t, uint8)
DEFINE_POPULATE_MATRIX(uint16_t, uint16)
DEFINE_POPULATE_MATRIX(uint32_t, uint32)
DEFINE_POPULATE_MATRIX(uint64_t, uint64)
DEFINE_POPULATE_MATRIX(float, float)
DEFINE_POPULATE_MATRIX(double, double)

/**
 * @brief Prints nxn matrix
 *
 * @return Returns 0 if successful (int)
 */
#define DEFINE_PRINT_MATRIX(TYPE, NAME, FORMAT)                                \
void print_matrix_##NAME(const TYPE *A, const int n){                          \
  printf("Printed matrix (%dx%d):\n", n, n);                                   \
  for (int i = 0; i < n; i++) {                                                \
      for (int j = 0; j < n; j++) {                                            \
          printf(FORMAT, A[i * n + j]);                                        \
      }                                                                        \
      printf("\n");                                                            \
  }                                                                            \
}

DEFINE_PRINT_MATRIX(int8_t, int8, "%hhd ")
DEFINE_PRINT_MATRIX(int16_t, int16, "%hd ")
DEFINE_PRINT_MATRIX(int32_t, int32, "%d ")
DEFINE_PRINT_MATRIX(int64_t, int64, "%ld ")
DEFINE_PRINT_MATRIX(uint8_t, uint8, "%hhu ")
DEFINE_PRINT_MATRIX(uint16_t, uint16, "%hu ")
DEFINE_PRINT_MATRIX(uint32_t, uint32, "%u ")
DEFINE_PRINT_MATRIX(uint64_t, uint64, "%lu ")
DEFINE_PRINT_MATRIX(float, float, "%.2f ")
DEFINE_PRINT_MATRIX(double, double, "%.2lf")

#define DEFINE_MULTIPLY_MATRICES(TYPE, NAME)                                   \
void matmul_##NAME(const TYPE *A, const TYPE *B, TYPE *C,                      \
                   int n)                                                      \
{                                                                              \
    for (int i = 0; i < n; i++) {                                              \
        for (int j = 0; j < n; j++) {                                          \
            for (int k = 0; k < n; k++) {                                      \
                C[i * n + j] += A[i * n + k] * B[k * n + j];                   \
            }                                                                  \
        }                                                                      \
    }                                                                          \
}

DEFINE_MULTIPLY_MATRICES(int8_t, int8)
DEFINE_MULTIPLY_MATRICES(int16_t, int16)
DEFINE_MULTIPLY_MATRICES(int32_t, int32)
DEFINE_MULTIPLY_MATRICES(int64_t, int64)
DEFINE_MULTIPLY_MATRICES(uint8_t, uint8)
DEFINE_MULTIPLY_MATRICES(uint16_t, uint16)
DEFINE_MULTIPLY_MATRICES(uint32_t, uint32)
DEFINE_MULTIPLY_MATRICES(uint64_t, uint64)
DEFINE_MULTIPLY_MATRICES(float, float)
DEFINE_MULTIPLY_MATRICES(double, double)

///**
// * @brief Multiplies two matrices together and puts the C in a third
// *
// * @return void 0
// */
//void matmul(const int *A, const int *B, int *C, const int n){
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            for (int k = 0; k < n; k++) {
//                C[i * n + j] += A[i * n + k] * B[k * n + j];
//            }
//        }
//    }
//}

/**
 * @brief Multiplies two matrices together and puts the C in a third
 *
 * @return void 0
 */
void matmul_sum(const int *A, const int *B, int *C, const int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int sum = 0;
      for (int k = 0; k < n; k++) {
        sum = A[i * n + k] * B[k * n + j] + sum;
      }
    C[i * n + j] = sum;
    }
  }
}

/**
 * @brief Multiplies two matrices together and puts the C in a third
 *
 * @return void 0
 */
void matmul_strip(const int *A, const int *B, int *C, const int n){
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}


#define DEFINE_MULTIPLY_MATRICES_BLOCKED(TYPE, NAME)                          \
void matmul_blocked_##NAME(const TYPE *A, const TYPE *B, TYPE *C, const int n)\
{                                                                             \
  for (int ii = 0; ii < n; ii+= BLOCK_SIZE) {                                 \
    for (int kk = 0; kk < n; kk+= BLOCK_SIZE) {                               \
      for (int jj = 0; jj < n; jj+= BLOCK_SIZE) {                             \
        int limit_i = ((ii + BLOCK_SIZE) < n) ? (ii + BLOCK_SIZE) : n;        \
        int limit_j = ((jj + BLOCK_SIZE) < n) ? (jj + BLOCK_SIZE) : n;        \
        int limit_k = ((kk + BLOCK_SIZE) < n) ? (kk + BLOCK_SIZE) : n;        \
        for (int i = ii; i < limit_i; ++i) {                                  \
          for (int k = kk; k < limit_k; ++k) {                                \
            int ki = i * n + k;                                               \
            for (int j = jj; j < limit_j; j++) {                              \
              C[i * n + j] += A[ki] * B[k * n + j];                           \
            }                                                                 \
          }                                                                   \
        }                                                                     \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}

DEFINE_MULTIPLY_MATRICES_BLOCKED(int8_t, int8)
DEFINE_MULTIPLY_MATRICES_BLOCKED(int16_t, int16)
DEFINE_MULTIPLY_MATRICES_BLOCKED(int32_t, int32)
DEFINE_MULTIPLY_MATRICES_BLOCKED(int64_t, int64)
DEFINE_MULTIPLY_MATRICES_BLOCKED(uint8_t, uint8)
DEFINE_MULTIPLY_MATRICES_BLOCKED(uint16_t, uint16)
DEFINE_MULTIPLY_MATRICES_BLOCKED(uint32_t, uint32)
DEFINE_MULTIPLY_MATRICES_BLOCKED(uint64_t, uint64)
DEFINE_MULTIPLY_MATRICES_BLOCKED(float, float)
DEFINE_MULTIPLY_MATRICES_BLOCKED(double, double)
