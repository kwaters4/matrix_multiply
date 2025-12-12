#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Generates nxn zero matrix
 *
 * @return void
 */
void generate_zero_matrix(int *matrix, int n){
    // Initialize the result matrix with 0s
  for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = 0;
        }
    }
}

void generate_identity_matrix(int *matrix, int n){

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
int compareMatrices(int *matrix1, int *matrix2, int n){

  for (int i = 0; i < n*n; i++) {
    if (matrix1[i] != matrix2[i])
      return -1;
    }
  return 0;
}

/**
 * @brief Populates a nxn random matrix with random values less than 10
 *
 * @return void)
 */
void populateMatrix(int *matrix, int n) {

  for (int i = 0; i < n*n; i++) {
    matrix[i] = i;
    matrix[i] = rand() % 10;
  }
}

/**
 * @brief Prints nxn matrix
 *
 * @return Returns 0 if successful (int)
 */
int printMatrix(int *matrix, int n) {
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
void multiplyMatrices(int *matrix1, int *matrix2, int *result, int n){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i * n + j] += matrix1[i * n + j] * matrix2[j * n + i];
            }
        }
    }
}



