#include <stdio.h>
#include <stdlib.h>

#include <matrix_mul.h>

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Usage: %s <min_size> <max_size>\n", argv[0]);
        return 1;
    }

    size_t min_size = atol(argv[1]);
    size_t max_size = atol(argv[2]);

    for(int i = min_size; i<= max_size; i=2*i) {
      int req_memory = 2*i*i*sizeof(int);
      int *matrix1 = malloc((i*i) * sizeof(int));
      int *matrix2 = malloc((i*i) * sizeof(int));

      // Check if the allocation failed.
      if (matrix1 == NULL || matrix2 == NULL){
        printf("Failed to allocated Matricies, mem req: %d \n)", req_memory);
        printf("Exiting...\n");
      }

    // Generate Random initial matrix
      srand(0);
      populateMatrix(matrix1, i); 
      populateMatrix(matrix2, i); 
      printMatrix(matrix1, i); 
      printMatrix(matrix2, i); 

//
//      // Check if matrix multiplication is possible
//      if (col1 != row2) {
//          printf("Matrix multiplication is not possible. Number of columns in Matrix 1 must equal the number of rows in Matrix 2.\n");
//          return -1;
//      }
//    // Input the matrices
//    multiplyMatrices(matrix1, matrix2, result, row1, col1, row2, col2);
//
//    // Print the result
//    printMatrix(result, row1, col2);
    free(matrix1);
    free(matrix2);
    }
} 
