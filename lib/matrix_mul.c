#include <stdio.h>
#include <stdlib.h>


void populateMatrix(int *matrix, int n) {

    for (int i = 0; i < n*n; i++) {
      matrix[i] = i;
      matrix[i] = rand() % 10;
      printf("matirx[%d] is %d \n", i, matrix[i]);
    }
}

void printMatrix(int *matrix, int n) {
    printf("Printed matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
//            printf("index %d is: %d \n", i*n*j, matrix[i * n * j]);
            printf("%d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

//void multiplyMatrices(int matrix1[MAX][MAX], int matrix2[MAX][MAX], int result[MAX][MAX], int row1, int col1, int row2, int col2) {
//    // Initialize the result matrix with 0s
//    for (int i = 0; i < row1; i++) {
//        for (int j = 0; j < col2; j++) {
//            result[i][j] = 0;
//        }
//    }
//
//    // Matrix multiplication
//    for (int i = 0; i < row1; i++) {
//        for (int j = 0; j < col2; j++) {
//            for (int k = 0; k < col1; k++) {
//                result[i][j] += matrix1[i][k] * matrix2[k][j];
//            }
//        }
//    }
//}



