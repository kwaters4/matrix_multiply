import random
import time

# Function for matrix multiplication
def matrix_multiply(A, B, data_type, N):

    result = [[0 for _ in range(N)] for _ in range(N)]

    start = time.time()
    for i in range(N):
        for j in range(N):
            for k in range(N):
                result[i][j] += A[i][k] * B[k][j]

    # Timing the multiplication
    end = time.time()

    # Printing the time it took for multiplication
    total_time = (end - start)/5.0
    print(f"{N}, {data_type}, {total_time:.6f}")
    return

sizes = [256, 512, 1024, 2048]
print(f"n, type, time (s)")
for N in sizes:
    A = [[random.randint(-5, 5) for _ in range(N)] for _ in range(N)]
    B = [[random.randint(-5, 5) for _ in range(N)] for _ in range(N)]
    matrix_multiply(A, B, "Int", N)

#A = [[random.random() for _ in range(N)] for _ in range(N)]
#B = [[random.random() for _ in range(N)] for _ in range(N)]
#matrix_multiply(A, B, "Float")
