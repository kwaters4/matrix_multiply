import numpy as np
import time

# Matrix size (adjust for your machine)

def matrix_multiply(A, B, data_type, N):
    # Warm-up
    C = A @ B

    start = time.perf_counter()
    i = 0
    trials = 5
    while i < trials:
        C = A @ B
        i += 1
    end = time.perf_counter()
    total_time = (end - start)/5.0
    print(f"{N}, {data_type}, {total_time:.6f}")
    return

# Initialize matrices

sizes = [256, 512, 1024, 2048]
print(f"n, type, time (s)")
for N in sizes:
#    A = np.random.randint(low=-5, high=5, size=(N, N), dtype=np.int32)
#    B = np.random.randint(low=-5, high=5, size=(N, N), dtype=np.int32)
#    matrix_multiply(A, B, "Int32", N)

    A = np.random.randint(low=-5, high=5, size=(N, N), dtype=np.int64)
    B = np.random.randint(low=-5, high=5, size=(N, N), dtype=np.int64)
    matrix_multiply(A, B, "Int64", N)
#
#    A = np.random.rand(N,N).astype('f')
#    B = np.random.rand(N,N).astype('f')
#    matrix_multiply(A, B, "Float")
#
#    A = np.random.rand(N,N)
#    B = np.random.rand(N,N)
#    matrix_multiply(A, B,"Double")
