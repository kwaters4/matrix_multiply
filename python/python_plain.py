import random
import time

N = 1024

# Function for matrix multiplication
def matrix_multiply(A, B, data_type):

    result = [[0 for _ in range(N)] for _ in range(N)]

    start = time.time()
    for i in range(N):
        for j in range(N):
            for k in range(N):
                result[i][j] += A[i][k] * B[k][j]

    # Timing the multiplication
    end = time.time()

    # Printing the time it took for multiplication
    print(f"{data_type:10s} Time: {end - start:.6f} seconds")
    return

# Generate random 1024x1024 matrices
print(f"{N}x{N} matrix multiply...")
A = [[random.randint(-5, 5) for _ in range(N)] for _ in range(N)]
B = [[random.randint(-5, 5) for _ in range(N)] for _ in range(N)]
matrix_multiply(A, B, "Int")

A = [[random.random() for _ in range(N)] for _ in range(N)]
B = [[random.random() for _ in range(N)] for _ in range(N)]
matrix_multiply(A, B, "Float")
